#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "button.h"

static const auto ColorAmber = wxColor(235, 205, 61);
static const auto ColorGreen = wxColor(36, 163, 34);

MyButton::MyButton(wxWindow *parent, wxWindowID id, const wxPoint &pos,
                   const wxSize &size)
    : wxButton(parent, id, _T(" "), pos, size) {
  Connect(id, wxEVT_COMMAND_BUTTON_CLICKED,
          wxCommandEventHandler(MyButton::ToggleColor));
}

void MyButton::ToggleColor(wxCommandEvent &ev) {
  switch (color_) {
    case ButtonColor::Grey:
      SetColor(ButtonColor::Amber);
      break;
    case ButtonColor::Amber:
      SetColor(ButtonColor::Green);
      break;
    case ButtonColor::Green:
      SetColor(ButtonColor::Grey);
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

void MyButton::SetColor(ButtonColor color) {
  switch (color) {
    case ButtonColor::Amber:
      SetBackgroundColour(ColorAmber);  // Amber
      color_ = ButtonColor::Amber;
      break;
    case ButtonColor::Green:
      SetBackgroundColour(ColorGreen);  // Green
      color_ = ButtonColor::Green;
      break;
    case ButtonColor::Grey:
      SetBackgroundColour(wxNullColour);  // Grey
      color_ = ButtonColor::Grey;
      break;
  }
}

void MyButton::Disable() {
  Enable(false);
  SetForegroundColour(wxColour(0, 0, 0));
}
