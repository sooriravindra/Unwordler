#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/activityindicator.h>

#include <memory>
#include <set>

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
  int curr_row_{-1};
  bool DisableRow(int row);
  bool SetRow(int, std::string);
  std::unique_ptr<WordEngine> wordEngine_;
};

class MyButton : public wxButton {
 public:
  MyButton(wxWindow *parent, wxWindowID id, const wxString &label,
           const wxPoint &pos);
  void ToggleColor(wxCommandEvent &ev);

 private:
  ButtonColor color_ = ButtonColor::Grey;
};

class WordEngine {
 public:
  WordEngine();
  void Reset();
  std::string GetWord(std::vector<char> &, std::vector<char> &);

 private:
  std::vector<std::string> wordBag_;
  std::vector<std::string> possibleWords_;
};
