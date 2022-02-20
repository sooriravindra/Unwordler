#include "app.h"

enum { ID_GO_BUTTON = 999 };

MyGrid::MyGrid(MyFrame* F, uint32_t rows, uint32_t columns)
    : frame_{F},
      rows_{rows},
      columns_{columns},
      wordEngine_{std::make_unique<WordEngine>()} {
  for (auto j = 0; j < rows_; j++) {
    for (auto i = 0; i < columns_; i++) {
      auto btn = new MyButton(frame_, i, _T(" "), wxPoint(80 * i, 40 * j));
      gridButtons_.push_back(btn);
      btn->Enable(false);
    }
  }

  goButton_ = new wxButton(frame_, ID_GO_BUTTON, _T("Go!"),
                           wxPoint(40 * (columns_ - 1), 40 * rows_ + 20));
  goButton_->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
                  wxCommandEventHandler(MyGrid::GoClick), this);
}

MyGrid::~MyGrid() { std::cout << "MyGrid destructor called " << std::endl; }

void MyGrid::GoClick(wxCommandEvent& ev) {
  std::multiset<std::string> m;
  DisableRow(curr_row_++);
  auto ret = SetRow(curr_row_, wordEngine_->GetWord(m, m));
  if (ret && curr_row_ == rows_ - 1) goButton_->Enable(false);
}

bool MyGrid::DisableRow(int row) {
  if (row < 0 || row > rows_) {
    std::cout << "Can't disable row beyond range" << std::endl;
    return false;
  }
  for (auto i = columns_ * row; i < columns_ * (row + 1); i++) {
    auto b = gridButtons_[i];
    b->Enable(false);
  }
  return true;
}

bool MyGrid::SetRow(int srow, std::string s) {
  if (s.length() == 0 && s.length() != columns_) {
    std::cout << "Word length doesn't match with number of columns : " << s
              << std::endl;
    return false;
  }

  if (srow >= rows_ || srow < 0) {
    std::cout << "Trying to set a row beyond the row count" << std::endl;
    return false;
  }

  // Set to uppercase for consistency
  std::transform(s.begin(), s.end(), s.begin(), ::toupper);

  // Set button label and enable button
  for (auto i = 0; i < s.length(); i++) {
    auto b = gridButtons_[i + srow * columns_];
    auto str = std::string(1, s.at(i));
    b->SetLabel(str);
    b->Enable(true);
  }

  return true;
}

void MyGrid::Show(bool show) {
  std::cout << "Show " << show << std::endl;
  for (auto x : gridButtons_) show ? x->Show() : x->Hide();
}
