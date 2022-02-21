#include "app.h"

#include "grid.h"

enum { ID_New = 1 };
const auto WindowWidth = 420;
const auto WindowHeight = 350;
const auto GridRows = 6;
const auto GridColumns = 5;

wxIMPLEMENT_APP(UnwordlerApp);

bool UnwordlerApp::OnInit() {
  wxFrame *frame = new MyFrame();
  frame->Show(true);
  return true;
}

void MyFrame::InitMenubar() {
  // File item
  auto *menuItemFile = new wxMenu;
  menuItemFile->Append(ID_New, "&New...\tCtrl-N", "New Wordle solver");
  menuItemFile->AppendSeparator();
  menuItemFile->Append(wxID_EXIT);

  // Help item
  auto *menuItemHelp = new wxMenu;
  menuItemHelp->Append(wxID_ABOUT);
  auto *menuBar = new wxMenuBar;

  menuBar->Append(menuItemFile, "&File");
  menuBar->Append(menuItemHelp, "&Help");
  SetMenuBar(menuBar);

  Bind(wxEVT_MENU, &MyFrame::OnNew, this, ID_New);
  Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Unwordler", wxDefaultPosition,
              wxSize(WindowWidth, WindowHeight)),
      grid_{std::make_unique<MyGrid>(this, GridRows, GridColumns)},
      spinner_{std::make_unique<wxActivityIndicator>(this)} {
  spinner_->Centre();
  spinner_->Start();
  InitMenubar();
  spinner_->Stop();
  spinner_->Show(false);
  grid_->Show(true);
}

void MyFrame::OnExit(wxCommandEvent &event) { Close(true); }

void MyFrame::OnAbout(wxCommandEvent &event) {
  wxMessageBox("Wordle solver app by Raveendra Soori", "About Unwordler",
               wxOK | wxICON_INFORMATION);
}

void MyFrame::OnNew(wxCommandEvent &event) {
  grid_->Reset();
  grid_->Show(true);
}
