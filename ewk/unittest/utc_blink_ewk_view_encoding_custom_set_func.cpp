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

class utc_blink_ewk_view_encoding_custom_set : public utc_blink_ewk_base
{
public:
  static const char* encoding_;
};

const char* utc_blink_ewk_view_encoding_custom_set::encoding_ = "utf-8";

/**
* @brief Check whether function works well with correct webview as parameter
*/
TEST_F(utc_blink_ewk_view_encoding_custom_set, POS_TEST)
{
  ewk_view_encoding_custom_set(GetEwkWebView(), encoding_);
  SUCCEED();
}

/**
* @brief Checking whether function works properly in case of NULL of a webview.
*/
TEST_F(utc_blink_ewk_view_encoding_custom_set, NEG_TEST)
{
  ewk_view_encoding_custom_set(NULL, encoding_);
  SUCCEED();
}
