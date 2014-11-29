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

class utc_blink_ewk_view_application_name_for_user_agent_get : public utc_blink_ewk_base
{
};

/**
 * @brief Positive test case of ewk_view_user_agent_get()
 */
TEST_F(utc_blink_ewk_view_application_name_for_user_agent_get, POS_TEST)
{
  const char* testString = "TEST_STRING";
  ASSERT_EQ(EINA_TRUE, ewk_view_application_name_for_user_agent_set(GetEwkWebView(), testString));
  const char* userAgent = ewk_view_application_name_for_user_agent_get(GetEwkWebView());
  EXPECT_EQ(strcmp(userAgent, testString), 0);
}

/**
 * @brief Negative test case of ewk_view_user_agent_get()
 */
TEST_F(utc_blink_ewk_view_application_name_for_user_agent_get, NEG_TEST)
{
  const char* userAgent =  ewk_view_application_name_for_user_agent_get(NULL);
  ASSERT_TRUE(userAgent == NULL);
}
