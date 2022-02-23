#include "grid.h"

#include "app.h"
#include "button.h"
#include "word_engine.h"

enum { ID_GO_BUTTON = 999 };
const int ButtonLength = 80;
const int ButtonBuffer = 20;

MyGrid::MyGrid(MyFrame *F, uint32_t rows, uint32_t columns)
    : frame_{F},
      rows_{rows},
      columns_{columns},
      wordEngine_{std::make_unique<WordEngine>()} {
  for (auto j = 0; j < rows_; j++) {
    for (auto i = 0; i < columns_; i++) {
      auto *btn =
          new MyButton(frame_, i, wxPoint(ButtonLength * i, ButtonLength * j),
                       wxSize(ButtonLength, ButtonLength));
      btn->Show(false);
      btn->Disable();
      gridButtons_.push_back(btn);
    }
  }

  goButton_ = new wxButton(frame_, ID_GO_BUTTON, _T("Go!"),
                           wxPoint(ButtonLength / 2 * (columns_ - 1),
                                   ButtonLength * rows_ + ButtonBuffer));
  goButton_->Show(false);
  goButton_->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
                  wxCommandEventHandler(MyGrid::GoClick), this);
}

MyGrid::~MyGrid() { std::cout << "Destroying Grid!" << std::endl; }

void MyGrid::PopulateLetterColors(
    std::vector<char> &grey_letters,
    std::vector<std::pair<char, uint32_t>> &amber_letters,
    std::vector<std::pair<char, uint32_t>> &green_letters) {
  for (int i = 0; i < (curr_row_)*columns_; i++) {
    auto *b = gridButtons_[i];
    switch (b->GetCurrentColor()) {
      case ButtonColor::Amber:
        amber_letters.push_back(
            std::pair<char, uint32_t>(b->GetLabel()[0], i % columns_));
        break;
      case ButtonColor::Green:
        green_letters.push_back(
            std::pair<char, uint32_t>(b->GetLabel()[0], i % columns_));
        break;
      case ButtonColor::Grey:
        grey_letters.push_back(b->GetLabel()[0]);
        break;
      default:
        // do nothing
        break;
    }
  }
}

void MyGrid::GoClick(wxCommandEvent &ev) {
  std::vector<char> grey_letters;
  std::vector<std::pair<char, uint32_t>> amber_letters;
  std::vector<std::pair<char, uint32_t>> green_letters;

  PopulateLetterColors(grey_letters, amber_letters, green_letters);

  if (IsVictorious()) {
    wxMessageBox("Ah! The sweet taste of victory!", "Unwordler",
                 wxOK | wxICON_MASK);
    goButton_->Enable(false);
    return;
  }

  if (curr_row_ != 0) {
    DisableRow(curr_row_ - 1);
  }

  // Get a new word from the engine
  const auto word =
      wordEngine_->GetWord(grey_letters, amber_letters, green_letters);
  if (word.empty()) {
    wxMessageBox("Oops! Out of words :/", "Unwordler", wxOK);
    goButton_->Enable(false);
    return;
  }

  // Set the row to the word that was fetched
  bool ret = SetRow(curr_row_, word, green_letters);
  if (ret) {
    if (curr_row_ < rows_ - 1) {
      curr_row_++;
    } else {
      goButton_->Enable(false);
    }
  }
}

bool MyGrid::DisableRow(int row) {
  if (row < 0 || row >= rows_) {
    std::cout << "Can't disable row beyond range" << std::endl;
    return false;
  }
  for (auto i = columns_ * row; i < columns_ * (row + 1); i++) {
    gridButtons_[i]->Disable();
  }
  return true;
}

void MyGrid::Reset() {
  for (auto *b : gridButtons_) {
    b->Reset();
  }
  goButton_->Enable(true);
  curr_row_ = 0;
  wordEngine_->Reset();
}

bool MyGrid::SetRow(
    int srow, const std::string s,
    const std::vector<std::pair<char, uint32_t>> &green_letters) {
  if (s.length() == 0 || s.length() != columns_) {
    std::cout << "Word length doesn't match with number of columns : " << s
              << std::endl;
    return false;
  }

  if (srow >= rows_ || srow < 0) {
    std::cout << "Trying to set a row beyond the row count" << std::endl;
    return false;
  }

  /* Set to uppercase for consistency?
   * Not needed as the wordlist is in uppercase
   */
  /* std::transform(s.begin(), s.end(), s.begin(), ::toupper); */

  // Set button label and enable button
  for (auto i = 0; i < s.length(); i++) {
    auto *b = gridButtons_[i + srow * columns_];
    auto str = std::string(1, s.at(i));
    b->SetLabel(str);
    b->Enable(true);
    auto columns = columns_;
    auto lambda = [i, columns](const std::pair<char, uint32_t> p) {
      return (p.second % columns == i);
    };
    if (std::find_if(green_letters.begin(), green_letters.end(), lambda) !=
        green_letters.end()) {
      b->SetColor(ButtonColor::Green);
    }
  }

  return true;
}

void MyGrid::Show(bool show) {
  for (auto *x : gridButtons_) {
    x->Show(show);
  }
  goButton_->Show(show);
}

bool MyGrid::IsVictorious() {
  bool is_all_green = true;
  if (curr_row_ == 0) {
    return false;
  }

  // Find if all blocks in the previous row is green
  for (int i = (curr_row_ - 1) * columns_; i < curr_row_ * columns_; i++) {
    if (i < 0 || gridButtons_[i]->GetCurrentColor() != ButtonColor::Green) {
      is_all_green = false;
      break;
    }
  }
  return is_all_green;
}
