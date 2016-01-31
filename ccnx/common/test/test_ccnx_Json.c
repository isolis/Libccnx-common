/*
 * Copyright (c) 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Patent rights are not granted under this agreement. Patent rights are
 *       available under FRAND terms.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL XEROX or PARC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#include "../ccnx_Json.c"

#include <stdio.h>

#include <LongBow/unit-test.h>
#include <parc/algol/parc_SafeMemory.h>

LONGBOW_TEST_RUNNER(ccnx_Json)
{
    LONGBOW_RUN_TEST_FIXTURE(Global);
}

LONGBOW_TEST_RUNNER_SETUP(ccnx_Json)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_RUNNER_TEARDOWN(ccnx_Json)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

// ===================================================

LONGBOW_TEST_FIXTURE(Global)
{
    LONGBOW_RUN_TEST_CASE(Global, ccnxJson_CreateObject);
    LONGBOW_RUN_TEST_CASE(Global, ccnxJson_CreateArray);
    LONGBOW_RUN_TEST_CASE(Global, ccnxJson_CreateString);
    LONGBOW_RUN_TEST_CASE(Global, ccnxJson_CreateFromText);
    LONGBOW_RUN_TEST_CASE(Global, ccnxJson_Arrays);
    LONGBOW_RUN_TEST_CASE(Global, ccnxJson_Hash);
    LONGBOW_RUN_TEST_CASE(Global, ccnxJson_CreateFromText_Integer);
    LONGBOW_RUN_TEST_CASE(Global, ccnxJson_Duplicate);
    LONGBOW_RUN_TEST_CASE(Global, big_json);

    LONGBOW_RUN_TEST_CASE(Global, ccnxJson_CreateFromText_ReadFile);
    LONGBOW_RUN_TEST_CASE(Global, ccnxJson_CreateFromText_ReadFileToString);
}

LONGBOW_TEST_FIXTURE_SETUP(Global)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Global)
{
    if (parcMemory_Outstanding() != 0) {
        printf("('%s' leaks memory by %d (allocs - frees)) ", longBowTestCase_GetName(testCase), parcMemory_Outstanding());
        parcSafeMemory_ReportAllocation(STDOUT_FILENO);
        return LONGBOW_STATUS_MEMORYLEAK;
    }
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_CASE(Global, ccnxJson_CreateObject)
{
    CCNxJson *json = ccnxJson_CreateObject();
    assertTrue(ccnxJson_GetItemType(json) == CCNX_JSON_OBJECT, "wrong type\n");
    ccnxJson_Destroy(&json);
}

LONGBOW_TEST_CASE(Global, ccnxJson_CreateArray)
{
    CCNxJson *json = ccnxJson_CreateArray();
    assertTrue(ccnxJson_GetItemType(json) == CCNX_JSON_ARRAY, "wrong type\n");
    ccnxJson_Destroy(&json);
}

LONGBOW_TEST_CASE(Global, ccnxJson_CreateString)
{
    const char *truth = "It was a dark and stormy test case...";
    const char *test;

    CCNxJson *json = ccnxJson_CreateString(truth);
    assertTrue(ccnxJson_GetItemType(json) == CCNX_JSON_STRING, "wrong type\n");

    test = ccnxJson_GetItemString(json);

    assertTrue(strncmp(test, truth, strlen(truth) + 1) == 0, "got wrong pointer\n");

    ccnxJson_Destroy(&json);
}

LONGBOW_TEST_CASE(Global, ccnxJson_CreateFromText)
{
    char *truth = "{ \"APPLE\": \"BANANNA\" }";
    const char *test;
    CCNxJson *json;
    CCNxJson *bananna;

    json = ccnxJson_CreateFromText(truth);
    assertTrue(ccnxJson_GetItemType(json) == CCNX_JSON_OBJECT, "%s wrong type\n", __func__);

    bananna = ccnxJson_GetObject(json, "APPLE");
    assertNotNull(bananna, "%s could not find key", __func__);

    assertTrue(ccnxJson_GetItemType(bananna) == CCNX_JSON_STRING, "%s wrong type\n", __func__);

    test = ccnxJson_GetItemString(bananna);

    assertTrue(strncmp(test, "BANANNA", 8) == 0, "%s got wrong bananna\n", __func__);

    ccnxJson_Destroy(&json);
}

LONGBOW_TEST_CASE(Global, ccnxJson_Arrays)
{
    CCNxJson *array = ccnxJson_CreateArray();

    CCNxJson *a = ccnxJson_CreateString("a");
    CCNxJson *b = ccnxJson_CreateString("b");
    CCNxJson *c = ccnxJson_CreateString("c");
    CCNxJson *test;

    ccnxJson_AppendItemToArray(array, a);
    assertTrue(ccnxJson_GetArrayLength(array) == 1, "%s incorrect array length\n", __func__);
    ccnxJson_AppendItemToArray(array, b);
    assertTrue(ccnxJson_GetArrayLength(array) == 2, "%s incorrect array length\n", __func__);
    ccnxJson_AppendItemToArray(array, c);
    assertTrue(ccnxJson_GetArrayLength(array) == 3, "%s incorrect array length\n", __func__);

    test = ccnxJson_GetArrayElement(array, 2);

    assertTrue(ccnxJson_GetItemType(test) == CCNX_JSON_STRING, "%s wrong type\n", __func__);
    ccnxJson_Destroy(&array);
}

LONGBOW_TEST_CASE(Global, ccnxJson_Hash)
{
    CCNxJson *plum = ccnxJson_CreateString("plum");
    CCNxJson *pear = ccnxJson_CreateString("pear");

    assertFalse(ccnxJson_Hash(plum) == ccnxJson_Hash(pear), "%s bad hashes", __func__);

    ccnxJson_Destroy(&plum);
    ccnxJson_Destroy(&pear);
}

LONGBOW_TEST_CASE(Global, ccnxJson_CreateFromText_Integer)
{
    char *src = "{ \"hello\" : \"world\", \"apple\" : { \"hippie\" : 7 } }";

    CCNxJson *a = ccnxJson_CreateFromText(src);

    ccnxJson_Destroy(&a);
}

LONGBOW_TEST_CASE(Global, ccnxJson_Duplicate)
{
    char *src = "{ \"hello\" : \"world\", \"apple\" : { \"hippie\" : 7 } }";

    CCNxJson *a = ccnxJson_CreateFromText(src);
    CCNxJson *b = ccnxJson_Duplicate(a);

    ccnxJson_Destroy(&a);
    ccnxJson_Destroy(&b);
}

LONGBOW_TEST_CASE(Global, big_json)
{
    char *local_name = "/tmp/local";
    char *keystore_name = "alice";
    char *keystore_passwd = "12345";
    char *param_SYSTEM = "SYSTEM";
    char *param_USER = "USER";
    char *param_FWD_LOCAL_NAME = "LOCAL_NAME";
    char *param_COMPONENTS = "COMPONENTS";
    char *param_SET_SIGNING = "SET_SIGNING";
    char *param_KEYSTORE_NAME = "KEYSTORE_NAME";
    char *param_KEYSTORE_PASSWD = "KEYSTORE_PASSWD";
    CCNxJson *params, *system, *user;
    CCNxJson *components;
    CCNxJson *fwd_local_params;
    CCNxJson *user_codec_params;
    CCNxJson *signing_params;
    CCNxJson *copy;

    assertNotNull(local_name, "%s got null keystore name\n", __func__);
    assertNotNull(keystore_name, "%s got null keystore name\n", __func__);
    assertNotNull(keystore_passwd, "%s got null keystore passwd\n", __func__);

    params = ccnxJson_CreateObject();
    ccnxJson_AddItemToObject(params, param_SYSTEM, system = ccnxJson_CreateObject());
    ccnxJson_AddItemToObject(params, param_USER, user = ccnxJson_CreateObject());

    ccnxJson_AddItemToObject(system, param_COMPONENTS, components = ccnxJson_CreateArray());
    ccnxJson_AppendStringToArray(components, "API_CONNECTOR");
    ccnxJson_AppendStringToArray(components, "TESTING_UPPER");
    ccnxJson_AppendStringToArray(components, "FC_VEGAS");
    ccnxJson_AppendStringToArray(components, "TESTING_LOWER");

    ccnxJson_AddItemToObject(system, "FWD_LOCAL", fwd_local_params = ccnxJson_CreateObject());
    ccnxJson_AddStringToObject(fwd_local_params, param_FWD_LOCAL_NAME, local_name);

    ccnxJson_AddItemToObject(user, "CODEC_TLV", user_codec_params = ccnxJson_CreateObject());
    ccnxJson_AddItemToObject(user_codec_params, param_SET_SIGNING, signing_params = ccnxJson_CreateObject());


    ccnxJson_AddStringToObject(signing_params, param_KEYSTORE_NAME, keystore_name);
    ccnxJson_AddStringToObject(signing_params, param_KEYSTORE_PASSWD, keystore_passwd);

    copy = ccnxJson_Duplicate(params);
    ccnxJson_Destroy(&params);
    ccnxJson_Destroy(&copy);
}

LONGBOW_TEST_CASE(Global, ccnxJson_CreateFromText_ReadFile)
{
    char *string = NULL;

    assertTrue(longBowDebug_ReadFile("data.json", &string) != -1, "Could not read '%s'", "data.json");
    CCNxJson *json = ccnxJson_CreateFromText(string);

    ccnxJson_Destroy(&json);
    free(string);
}

LONGBOW_TEST_CASE(Global, ccnxJson_CreateFromText_ReadFileToString)
{
    char *string = NULL;

    assertTrue(longBowDebug_ReadFile("data.json", &string) != -1, "Could not read '%s'", "data.json");
    CCNxJson *json = ccnxJson_CreateFromText(string);
    char *actual = ccnxJson_ToString(json);

    parcMemory_Deallocate((void **) &actual);
    ccnxJson_Destroy(&json);
    free(string);
}

// ===================================================

int
main(int argc, char *argv[])
{
    LongBowRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(ccnx_Json);
    exit(longBowMain(argc, argv, testRunner, NULL));
}
