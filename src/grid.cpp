#include "app.h"

enum { ID_GO_BUTTON = 999 };

MyGrid::MyGrid(MyFrame* F, int rows, int columns)
    : frame_{F}, rows_{rows}, columns_{columns} {
  for (auto j = 0; j < rows_; j++) {
    for (auto i = 0; i < columns_; i++) {
      gridButtons_.push_back(
          new MyButton(frame_, i, _T("."), wxPoint(80 * i, 40 * j)));
    }
  }

  goButton_ = new wxButton(frame_, ID_GO_BUTTON, _T("Go!"),
                           wxPoint(40 * (columns_ - 1), 40 * rows_ + 20));
}

bool MyGrid::SetRow(int srow, std::string s) {
  if (s.length() == 0 && s.length() != columns_) {
    std::cout << "Word length doesn't match with number of columns"
              << std::endl;
    return false;
  }

  if (srow > rows_) {
    std::cout << "Trying to set a row beyond the row count" << std::endl;
    return false;
  }

  // Set to uppercase for consistency
  std::transform(s.begin(), s.end(), s.begin(), ::toupper);

  for (auto i = 0; i < s.length(); i++) {
    auto b = gridButtons_[i + srow * columns_];
    b->SetLabel(std::string(1, s.at(i)));
  }

  return true;
}

void MyGrid::Show(bool show) {
  std::cout << "Show " << show << std::endl;
  for (auto x : gridButtons_) show ? x->Show() : x->Hide();
}
