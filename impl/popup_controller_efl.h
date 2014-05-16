#ifndef popup_controller_efl_h
#define popup_controller_efl_h

#include <Evas.h>
#include "eweb_view.h"

#ifdef TIZEN_CONTENTS_DETECTION
namespace content {

class PopupControllerEfl {

  enum Content_Type {
    EMAIL,
    PHONE,
    UNKNOWN
  };

 public:
  PopupControllerEfl(EWebView*);
  void openPopup(const char*);
  void closePopup();
  Evas_Object* popup() { return popup_; }
  Content_Type popupContentType() { return content_type_; }
  const std::string& content() { return content_; }

 private:
  EWebView* web_view_;
  Evas_Object* popup_;
  Content_Type content_type_;
  std::string content_;
};

} // namespace
#endif // TIZEN_CONTENTS_DETECTION

#endif // popup_controller_efl_h
