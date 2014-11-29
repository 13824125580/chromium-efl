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

class utc_blink_cb_redo_size : public utc_blink_ewk_base
{
 protected:

  utc_blink_cb_redo_size() : size(0)
  {
  }

  void PostSetUp()
  {
    evas_object_smart_callback_add(GetEwkWebView(), "redo,size", ToSmartCallback(redo_size), this);
  }

  void PreTearDown()
  {
    evas_object_smart_callback_del(GetEwkWebView(), "redo,size", ToSmartCallback(redo_size));
  }

  void LoadFinished(Evas_Object*)
  {
    EventLoopStop(Success);
  }

  static void undo_size(utc_blink_cb_redo_size* owner, Evas_Object*, const unsigned long*)
  {
    ASSERT_TRUE(owner);
    utc_message("[ %s ]", __PRETTY_FUNCTION__);
    owner->EventLoopStop(Success);
  }

  static void redo_size(utc_blink_cb_redo_size* owner, Evas_Object*, const unsigned long* size)
  {
    ASSERT_TRUE(owner);
    utc_message("\e[0;32m[ %s ]\e[0m", __PRETTY_FUNCTION__);
    if (size) owner->size = *size;
    owner->EventLoopStop(Success);
  }

protected:
  unsigned long size;
};

TEST_F(utc_blink_cb_redo_size, POS_TEST)
{
  ASSERT_TRUE(ewk_view_url_set(GetEwkWebView(), GetResourceUrl("ewk_view/undo_redo.html").c_str()));
  // Wait for "redo,size" when initialization a view
  ASSERT_EQ(Success, EventLoopStart());
  // Wait for LoadFinished
  ASSERT_EQ(Success, EventLoopStart());

  {
    evas_object_smart_callback_auto undo(GetEwkWebView(), "undo,size",
                                         ToSmartCallback(undo_size), this);
    for (int i = 3; i > 0; --i) {
      utc_message("edit");
      ewk_view_command_execute(GetEwkWebView(),"SelectAll", NULL);
      ewk_view_command_execute(GetEwkWebView(),"InsertText", ".");
      // Wait for undo_size callback
      ASSERT_EQ(Success, EventLoopStart());
    }
  }
  ASSERT_EQ(0, size);

  for (int i = 2; i > 0; --i) {
    utc_message("undo");
    ewk_view_command_execute(GetEwkWebView(),"undo", NULL);
    // Wait for redo_size callback
    ASSERT_EQ(Success, EventLoopStart());
  }

  ASSERT_EQ(2, size);

  for (int i = 2; i > 0; --i) {
    utc_message("redo");
    ewk_view_command_execute(GetEwkWebView(),"redo", NULL);
    // Wait for redo_size callback
    EXPECT_EQ(Success, EventLoopStart());
  }

  ASSERT_EQ(0, size);
}
