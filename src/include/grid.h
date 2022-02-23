#pragma once

#include <memory>
#include <vector>

#include "app.h"
#include "button.h"
#include "word_engine.h"

extern const int ButtonLength;
extern const int ButtonBuffer;

class MyGrid : public wxEvtHandler {
 public:
  MyGrid(MyFrame *F, uint32_t rows, uint32_t columns);
  ~MyGrid();
  void Show(bool);
  void GoClick(wxCommandEvent &ev);
  void Reset();

 private:
  MyFrame *frame_;
  std::vector<MyButton *> gridButtons_;
  wxButton *goButton_;
  uint32_t rows_;
  uint32_t columns_;
  uint32_t curr_row_{0};
  std::unique_ptr<WordEngine> wordEngine_;
  bool DisableRow(int row);
  bool SetRow(int, std::string, const std::vector<std::pair<char, uint32_t>> &);
  bool IsVictorious();
  void PopulateLetterColors(
      std::vector<char> &grey_letters,
      std::vector<std::pair<char, uint32_t>> &amber_letters,
      std::vector<std::pair<char, uint32_t>> &green_letters);
};
