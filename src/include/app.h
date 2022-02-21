#pragma once
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/activityindicator.h>

#include <algorithm>
#include <list>
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
  void OnNew(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  void InitMenubar();
  std::unique_ptr<MyGrid> grid_;
  std::unique_ptr<wxActivityIndicator> spinner_;
};
