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

class utc_blink_ewk_settings_auto_fitting_set : public utc_blink_ewk_base {
};


/**
 * @brief Positive test case of ewk_settings_auto_fitting_set()
 */
TEST_F(utc_blink_ewk_settings_auto_fitting_set, POS_TEST1)
{
  Ewk_Settings* settings = ewk_view_settings_get(GetEwkWebView());
  if (!settings) {
    FAIL();
  }
  int resultCheck = ewk_settings_auto_fitting_set(settings, EINA_TRUE);
  if (resultCheck == EINA_TRUE) {
    EXPECT_EQ((int)ewk_settings_auto_fitting_get(settings), 1);
  }
  else {
    EXPECT_EQ(resultCheck, 1);
  }
}

/**
 * @brief Positive test case of ewk_settings_auto_fitting_set()
 */
TEST_F(utc_blink_ewk_settings_auto_fitting_set, POS_TEST2)
{
  Ewk_Settings* settings = ewk_view_settings_get(GetEwkWebView());
  if (!settings) {
    FAIL();
  }
  int resultCheck = ewk_settings_auto_fitting_set(settings, EINA_FALSE);
  if (resultCheck == EINA_TRUE) {
    EXPECT_EQ((int)ewk_settings_auto_fitting_get(settings), 0);
  }
  else {
    EXPECT_EQ(resultCheck, 1);
  }
}

/**
 * @brief Negative test case of ewk_settings_auto_fitting_set()
 */
TEST_F(utc_blink_ewk_settings_auto_fitting_set, NEG_TEST)
{
  int check = ewk_settings_auto_fitting_set(NULL, EINA_TRUE);
  EXPECT_EQ(check, 0);
}
