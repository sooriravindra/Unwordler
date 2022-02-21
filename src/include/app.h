#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/activityindicator.h>

#include <algorithm>
#include <list>
#include <memory>

enum class ButtonColor { Green, Amber, Grey };

class MyGrid;
class MyButton;
class WordEngine;

class UnwordlerApp : public wxApp {
 public:
  virtual bool OnInit();
};

class MyFrame : public wxFrame {
 public:
  MyFrame();

 private:
  void OnNew(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  void InitMenubar();
  std::unique_ptr<MyGrid> grid_;
  std::unique_ptr<wxActivityIndicator> spinner_;
};

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
  bool SetRow(int, const std::string,
              const std::vector<std::pair<char, uint32_t>> &);
  bool IsVictorious();
  void PopulateLetterColors(
      std::vector<char> &grey_letters,
      std::vector<std::pair<char, uint32_t>> &amber_letters,
      std::vector<std::pair<char, uint32_t>> &green_letters);
};

class MyButton : public wxButton {
 public:
  MyButton(wxWindow *parent, wxWindowID id, const wxPoint &pos);
  void ToggleColor(wxCommandEvent &ev);
  ButtonColor GetCurrentColor();
  void SetColor(ButtonColor color);
  void Reset();

 private:
  ButtonColor color_ = ButtonColor::Grey;
};

class WordEngine {
 public:
  WordEngine();
  void Reset();
  std::string GetWord(std::vector<char> &,
                      std::vector<std::pair<char, uint32_t>> &,
                      std::vector<std::pair<char, uint32_t>> &);
  std::list<std::string>::iterator GetRandWordIterator();
  std::list<std::string>::iterator GetLikelyWordIterator();
  int GetRandom(uint32_t size);
  void RemoveWord(std::list<std::string>::iterator it, std::string);

 private:
  std::list<std::string> InitWordBag();
  std::list<std::string> wordBag_;
  std::list<std::string> possibleWords_;
};
