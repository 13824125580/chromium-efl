// Copyright 2014 Samsung Electronics. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

/* Define those macros _before_ you include the utc_blink_ewk.h header file. */

#include "utc_blink_ewk_base.h"

class utc_blink_ewk_text_style_font_size_get : public utc_blink_ewk_base {
 protected:
  static void get_text_style(void* data, Evas_Object* webview, void* event_info)
  {
    utc_message("[get_text_style callback] :: ");
    utc_blink_ewk_text_style_font_size_get* owner = NULL;
    if (!data) {
      utc_fail();
    }

    owner = static_cast<utc_blink_ewk_text_style_font_size_get*>(data);

    Ewk_Text_Style* style = (Ewk_Text_Style*)event_info;

    owner->font_size = ewk_text_style_font_size_get(style);
    owner->EventLoopStop(utc_blink_ewk_base::Success);
  }

  virtual void PostSetUp()
  {
    evas_object_smart_callback_add(GetEwkWebView(),"text,style,state", get_text_style, this);

    Ewk_Settings* settings = ewk_view_settings_get(GetEwkWebView());
    ewk_settings_text_style_state_enabled_set(settings, EINA_TRUE);
  }

  virtual void PreTearDown()
  {
    evas_object_smart_callback_del(GetEwkWebView(), "text,style,state", get_text_style);
  }

protected:
  std::string font_size;
};

/**
* @brief Positive test case of ewk_text_style_font_size_get(). To get the Font size.
*/
TEST_F(utc_blink_ewk_text_style_font_size_get, POS_TEST)
{
  const char textStyleHTML[] =
      "<!DOCTYPE html>"
      "<html><head>"
      "</head>"
      "<body  onload='txtarea.focus(); txtarea.select()'>"
      "<textarea id='txtarea' style='text-decoration:underline;font-weight:bold;font-style:italic;background-color:rgb(0,255,0);"
      "font-size:20px;color:rgb(255,0,0)'>select text</textarea>"
      "</body></html>";
  ewk_view_html_string_load(GetEwkWebView(), textStyleHTML, 0, 0);
  // Wait until load finished.
  utc_blink_ewk_base::MainLoopResult result = EventLoopStart(10.0);

  if (result != utc_blink_ewk_base::Success) {
    utc_fail();
  }

  utc_check_eq(std::string("5"), font_size);
}

/**
* @brief Checking whether function works properly in case of NULL of command.
*/
TEST_F(utc_blink_ewk_text_style_font_size_get, NEG_TEST)
{
  utc_check_eq(0, ewk_text_style_font_size_get(NULL));
}



