/*
 * Copyright (C) 2014 Samsung Electronics
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "webview_delegate_ewk.h"
#include <cassert>
#include "public/ewk_view.h"
#include "private/ewk_view_private.h"

// static
const WebViewDelegateEwk& WebViewDelegateEwk::GetInstance() {
  static WebViewDelegateEwk instance;
  return instance;
}

tizen_webview::WebView* WebViewDelegateEwk::GetWebViewFromEvasObject(
    Evas_Object* evas_object) {
  return ::GetWebViewFromEvasObject(evas_object);
}

bool WebViewDelegateEwk::IsWebViewEvasObject(Evas_Object* evas_object) {
  return ::IsWebViewObject(evas_object);
}

Evas_Object* WebViewDelegateEwk::GetContentImageEvasObject(
    Evas_Object* evas_object) {
  if (!WebViewDelegateEwk::IsWebViewEvasObject(evas_object)) {
    return NULL;
  }
  return GetEwkViewSmartDataFromEvasObject(evas_object)->image;
}

Evas_Object_Smart_Clipped_Data* WebViewDelegateEwk::GetSmartClippedData(
    Evas_Object* evas_object) {
  if (!WebViewDelegateEwk::IsWebViewEvasObject(evas_object)) {
    return NULL;
  }
  return &GetEwkViewSmartDataFromEvasObject(evas_object)->base;
}

Eina_Rectangle WebViewDelegateEwk::GetLastUsedViewPortArea(
    Evas_Object* evas_object) {
  Eina_Rectangle result = {-1, -1, -1, -1};
  if (WebViewDelegateEwk::IsWebViewEvasObject(evas_object)) {
    Ewk_View_Smart_Data* sd = GetEwkViewSmartDataFromEvasObject(evas_object);
    assert(sd);
    result.x = sd->view.x;
    result.y = sd->view.y;
    result.w = sd->view.w;
    result.h = sd->view.h;
  }
  return result;
}

bool WebViewDelegateEwk::RequestHandleEvent_FocusIn(WebView* wv) {
  Ewk_View_Smart_Data* sd = GetEwkViewSmartDataFromWebView(wv);
  if (sd && sd->api && sd->api->focus_in) {
    sd->api->focus_in(sd);
    return true;
  }
  return false;
}

bool WebViewDelegateEwk::RequestHandleEvent_FocusOut(WebView* wv) {
  Ewk_View_Smart_Data* sd = GetEwkViewSmartDataFromWebView(wv);
  if (sd && sd->api && sd->api->focus_out) {
    sd->api->focus_out(sd);
    return true;
  }
  return false;
}

bool WebViewDelegateEwk::RequestHandleEvent_MouseUp(WebView* wv,
    Evas_Event_Mouse_Up* event_info) {
  Ewk_View_Smart_Data* sd = GetEwkViewSmartDataFromWebView(wv);
  if (sd && sd->api && sd->api->mouse_up) {
    sd->api->mouse_up(sd, event_info);
    return true;
  }
  return false;
}

bool WebViewDelegateEwk::RequestHandleEvent_MouseDown(WebView* wv,
    Evas_Event_Mouse_Down* event_info) {
  Ewk_View_Smart_Data* sd = GetEwkViewSmartDataFromWebView(wv);
  if (sd && sd->api && sd->api->mouse_down) {
    sd->api->mouse_down(sd, event_info);
    return true;
  }
  return false;
}

bool WebViewDelegateEwk::RequestHandleEvent_MouseMove(WebView* wv,
    Evas_Event_Mouse_Move* event_info) {
  Ewk_View_Smart_Data* sd = GetEwkViewSmartDataFromWebView(wv);
  if (sd && sd->api && sd->api->mouse_move) {
    sd->api->mouse_move(sd, event_info);
    return true;
  }
  return false;
}

bool WebViewDelegateEwk::RequestHandleEvent_MouseWheel(WebView* wv,
    Evas_Event_Mouse_Wheel* event_info) {
  Ewk_View_Smart_Data* sd = GetEwkViewSmartDataFromWebView(wv);
  if (sd && sd->api && sd->api->mouse_wheel) {
    sd->api->mouse_wheel(sd, event_info);
    return true;
  }
  return false;
}

bool WebViewDelegateEwk::RequestHandleEvent_KeyUp(WebView* wv,
    Evas_Event_Key_Up* event_info) {
  Ewk_View_Smart_Data* sd = GetEwkViewSmartDataFromWebView(wv);
  if (sd && sd->api && sd->api->key_up) {
    sd->api->key_up(sd, event_info);
    return true;
  }
  return false;
}

bool WebViewDelegateEwk::RequestHandleEvent_KeyDown(WebView* wv,
    Evas_Event_Key_Down* event_info) {
  Ewk_View_Smart_Data* sd = GetEwkViewSmartDataFromWebView(wv);
  if (sd && sd->api && sd->api->key_down) {
    sd->api->key_down(sd, event_info);
    return true;
  }
  return false;
}
