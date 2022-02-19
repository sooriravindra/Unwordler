#include "app.h"

enum { ID_New = 1 };

wxIMPLEMENT_APP(UnwordlerApp);

bool UnwordlerApp::OnInit() {
  wxFrame *frame = new MyFrame();
  frame->Show(true);
  return true;
}

void MyFrame::InitMenubar() {
  // File item
  wxMenu *menuItemFile = new wxMenu;
  menuItemFile->Append(ID_New, "&New...\tCtrl-N", "New Wordle solver");
  menuItemFile->AppendSeparator();
  menuItemFile->Append(wxID_EXIT);

  // Help item
  wxMenu *menuItemHelp = new wxMenu;
  menuItemHelp->Append(wxID_ABOUT);
  wxMenuBar *menuBar = new wxMenuBar;

  menuBar->Append(menuItemFile, "&File");
  menuBar->Append(menuItemHelp, "&Help");
  SetMenuBar(menuBar);

  Bind(wxEVT_MENU, &MyFrame::OnNew, this, ID_New);
  Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Unwordler", wxDefaultPosition, wxSize(400, 300)),
      grid_{std::make_unique<MyGrid>(this, 5, 5)} {
  MyFrame::InitMenubar();
  grid_->Show(false);
  grid_->Show(true);
  grid_->SetRow(0, "Hello");
  grid_->SetRow(2, "World");
}

void MyFrame::OnExit(wxCommandEvent &event) { Close(true); }

void MyFrame::OnAbout(wxCommandEvent &event) {
  wxMessageBox("This is a Wordle solver app", "About Unwordler",
               wxOK | wxICON_INFORMATION);
}

void MyFrame::OnNew(wxCommandEvent &event) {
  wxLogMessage("Starting new solver");
}
