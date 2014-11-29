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

class utc_blink_ewk_settings_initial_list_style_position_set : public utc_blink_ewk_base {
};

/**
* @brief checking if returns EWK_LIST_STYLE_POSITION_OUTSIDE when initiated with a correct webview and
* initial list style position set to EWK_LIST_STYLE_POSITION_OUTSIDE.
*/
TEST_F(utc_blink_ewk_settings_initial_list_style_position_set, POS_TEST1)
{
  Ewk_Settings *settings = ewk_view_settings_get(GetEwkWebView());
  if (!settings) {
    FAIL();
  }

  Eina_Bool result = ewk_settings_initial_list_style_position_set(settings, EWK_LIST_STYLE_POSITION_OUTSIDE);
  if (!result) {
    FAIL();
  }
  EXPECT_EQ(ewk_settings_initial_list_style_position_get(settings), EWK_LIST_STYLE_POSITION_OUTSIDE);
}

/**
* @brief checking if returns EWK_LIST_STYLE_POSITION_INSIDE when initiated with a correct webview and
* initial list style position set to EWK_LIST_STYLE_POSITION_INSIDE.
*/
TEST_F(utc_blink_ewk_settings_initial_list_style_position_set, POS_TEST2)
{
  Ewk_Settings *settings = ewk_view_settings_get(GetEwkWebView());
  if (!settings) {
    FAIL();
  }

  Eina_Bool result = ewk_settings_initial_list_style_position_set(settings, EWK_LIST_STYLE_POSITION_INSIDE);
  if (!result) {
    FAIL();
  }
  EXPECT_EQ(ewk_settings_initial_list_style_position_get(settings), EWK_LIST_STYLE_POSITION_INSIDE);
}

/**
* @brief checking if returns FALSE when initiated with NULL webview.
*/
TEST_F(utc_blink_ewk_settings_initial_list_style_position_set, NEG_TEST)
{
  Eina_Bool result = ewk_settings_initial_list_style_position_set(NULL, EWK_LIST_STYLE_POSITION_INSIDE);
  EXPECT_EQ(result, EINA_FALSE);
}
