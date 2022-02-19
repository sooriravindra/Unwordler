#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <memory>

class MyGrid;

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
  std::vector<wxButton*> gridButtons_;
  wxButton* goButton_;
  int rows_;
  int columns_;
};
