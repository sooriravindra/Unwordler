#include "app.h"

MyButton::MyButton(wxWindow *parent, wxWindowID id, const wxPoint &pos)
    : wxButton(parent, id, _T(" "), pos) {
  Connect(id, wxEVT_COMMAND_BUTTON_CLICKED,
          wxCommandEventHandler(MyButton::ToggleColor));
}

void MyButton::ToggleColor(wxCommandEvent &ev) {
  switch (color_) {
    case ButtonColor::Grey:
      SetBackgroundColour(wxColor(235, 205, 61));  // Amber
      color_ = ButtonColor::Amber;
      break;
    case ButtonColor::Amber:
      SetBackgroundColour(wxColor(36, 163, 34));  // Green
      color_ = ButtonColor::Green;
      break;
    case ButtonColor::Green:
      SetBackgroundColour(wxNullColour);  // Grey
      color_ = ButtonColor::Grey;
      break;
  }
}

ButtonColor MyButton::GetCurrentColor() { return color_; }

void MyButton::Reset() {
  SetLabel(" ");
  Enable(false);
  SetBackgroundColour(wxNullColour);
  color_ = ButtonColor::Grey;
}
