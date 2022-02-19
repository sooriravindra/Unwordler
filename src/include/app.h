#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>

enum class ButtonColor { Green, Amber, Grey };

class MyGrid;
class MyButton;

class UnwordlerApp : public wxApp {
 public:
  virtual bool OnInit();
};

class MyFrame : public wxFrame {
 public:
  MyFrame();

 private:
  void OnNew(wxCommandEvent& event);
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void InitMenubar();
  std::unique_ptr<MyGrid> grid_;
};

class MyGrid {
 public:
  MyGrid(MyFrame* F, int rows, int columns);
  void Show(bool);
  bool SetRow(int, std::string);

 private:
  MyFrame* frame_;
  std::vector<MyButton*> gridButtons_;
  wxButton* goButton_;
  int rows_;
  int columns_;
};

class MyButton : public wxButton {
 public:
  MyButton(wxWindow* parent, wxWindowID id, const wxString& label,
           const wxPoint& pos);
  void ToggleColor(wxCommandEvent& ev);

 private:
  ButtonColor color_ = ButtonColor::Grey;
};
