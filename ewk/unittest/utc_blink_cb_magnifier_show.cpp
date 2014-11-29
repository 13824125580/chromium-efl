/*
 * chromium EFL
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc., 51
 * Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 */

#include "utc_blink_ewk_base.h"

#define URL  ("http://google.com")

class utc_blink_cb_magnifier_show : public utc_blink_ewk_base
{
public:
    /* Callback for "load,finished" */
    void LoadFinished(Evas_Object* webview)
    {
        EventLoopStop(utc_blink_ewk_base::Success);
    }

    void PostSetUp()
    {
      evas_object_smart_callback_add(GetEwkWebView(), "magnifier,show", magnifier_show_cb, this);
    }

    void PreTearDown()
    {
      evas_object_smart_callback_del(GetEwkWebView(), "magnifier,show", magnifier_show_cb);
    }

    static void magnifier_show_cb(void* data, Evas_Object* webview, void* event_info)
    {
      utc_blink_cb_magnifier_show *owner = NULL;
      OwnerFromVoid(data, &owner);
      owner->EventLoopStop(Success);
    }

    static Eina_Bool do_text_selection_down(void* data)
    {
      utc_blink_cb_magnifier_show *owner = NULL;
      OwnerFromVoid(data, &owner);
      Ewk_View_Smart_Data* ewk_smart_data = static_cast<Ewk_View_Smart_Data*>(evas_object_smart_data_get(owner->GetEwkWebView()));
      ewk_smart_data->api->text_selection_down(ewk_smart_data, 10, 10);
      return ECORE_CALLBACK_CANCEL;
    }
};

/**
 * @brief Tests "magnifier,show" callback
 */
TEST_F(utc_blink_cb_magnifier_show, callback)
{
    utc_message("Loading url: %s", URL);
    ASSERT_EQ(EINA_TRUE, ewk_view_url_set(GetEwkWebView(), URL));

    ASSERT_EQ(Success, EventLoopStart());

    ecore_timer_add(1.0, do_text_selection_down, this);
    ASSERT_EQ(Success, EventLoopStart());
}
