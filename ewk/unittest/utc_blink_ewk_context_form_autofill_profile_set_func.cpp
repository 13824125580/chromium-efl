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
#include "utc_blink_ewk_context_form_autofill_profile_utils.h"
#include "utc_blink_ewk_context_form_autofill_profile_utils.cpp"

#include <map>
#include <sstream>

class utc_blink_ewk_context_form_autofill_profile_set : public utc_blink_ewk_base
{
};

TEST_F(utc_blink_ewk_context_form_autofill_profile_set, POS_TEST)
{
  EventLoopWait(3.0);
  Ewk_Autofill_Profile *profile = ewk_context_form_autofill_profile_get(ewk_context_default_get(), TEST_AUTOFILL_PROFILE_ID);
  if (NULL == profile) {
    Ewk_Autofill_Profile *profileToAdd = getTestEwkAutofillProfile();
    ASSERT_TRUE(NULL != profileToAdd);
    Eina_Bool result = ewk_context_form_autofill_profile_add(ewk_context_default_get(), profileToAdd);
    EventLoopWait(3.0);
    ASSERT_TRUE(EINA_FALSE != result);
    profileToAdd = getTestEwkAutofillProfile();
    ASSERT_TRUE(NULL != profileToAdd);
    //change some property
    ewk_autofill_profile_data_set(profileToAdd, EWK_PROFILE_COMPANY, "anotherCompany");
    //set it
    ASSERT_EQ(EINA_TRUE, ewk_context_form_autofill_profile_set(ewk_context_default_get(), TEST_AUTOFILL_PROFILE_ID, profileToAdd));
    //get it and check
    EventLoopWait(3.0);
    profile = ewk_context_form_autofill_profile_get(ewk_context_default_get(), TEST_AUTOFILL_PROFILE_ID);
    ASSERT_TRUE(NULL != profile);
    const char *res = ewk_autofill_profile_data_get(profile, EWK_PROFILE_COMPANY);
    ASSERT_TRUE(NULL != res && 0 == strcmp(res, "anotherCompany"));
  } else {
    profile = getTestEwkAutofillProfile();
    ewk_autofill_profile_data_set(profile, EWK_PROFILE_COMPANY, "anotherCompany");
    //set it
    ASSERT_EQ(EINA_TRUE, ewk_context_form_autofill_profile_set(ewk_context_default_get(), TEST_AUTOFILL_PROFILE_ID, profile));
    //get it and check
    profile = ewk_context_form_autofill_profile_get(ewk_context_default_get(), TEST_AUTOFILL_PROFILE_ID);
    ASSERT_TRUE(NULL != profile);
    const char *res = ewk_autofill_profile_data_get(profile, EWK_PROFILE_COMPANY);
    ASSERT_TRUE(NULL != res && 0 == strcmp(res,"anotherCompany"));
  }
}

TEST_F(utc_blink_ewk_context_form_autofill_profile_set, NEG_TEST)
{
  Ewk_Autofill_Profile *profileToAdd = getTestEwkAutofillProfile();
  Ewk_Context* context = ewk_context_default_get();
  ASSERT_TRUE(NULL != profileToAdd);
  ASSERT_TRUE(NULL != context);
  ASSERT_EQ(NULL, ewk_context_form_autofill_profile_set(NULL, TEST_AUTOFILL_PROFILE_ID, profileToAdd));
  ASSERT_EQ(NULL, ewk_context_form_autofill_profile_set(context, TEST_AUTOFILL_PROFILE_ID, NULL));
}
