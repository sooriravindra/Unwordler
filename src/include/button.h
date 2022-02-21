#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

enum class ButtonColor { Green, Amber, Grey };

class MyButton : public wxButton {
 public:
  MyButton(wxWindow *parent, wxWindowID id, const wxPoint &pos);
  void ToggleColor(wxCommandEvent &ev);
  ButtonColor GetCurrentColor();
  void SetColor(ButtonColor color);
  void Reset();
  void Disable();

 private:
  ButtonColor color_ = ButtonColor::Grey;
};
