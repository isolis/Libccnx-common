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

// Include the file(s) containing the functions to be tested.
// This permits internal static functions to be visible to this Test Framework.
#include "../ccnx_ContentObjectFacadeV0.c"
#include <parc/algol/parc_SafeMemory.h>
#include <LongBow/unit-test.h>
#include <inttypes.h>

#include <ccnx/common/codec/schema_v1/ccnxCodecSchemaV1_TlvDictionary.h>

typedef struct test_data {
    CCNxName *name;
    CCNxPayloadType payloadType;
    PARCBuffer *payload;

    CCNxTlvDictionary *contentObjectV0;

    // a V0 dictionary but with no values set
    CCNxTlvDictionary *contentObjectV0Empty;

    CCNxTlvDictionary *contentObjectVFF;
} TestData;

static TestData *
_commonSetup(void)
{
    TestData *data = parcMemory_AllocateAndClear(sizeof(TestData));
    assertNotNull(data, "parcMemory_AllocateAndClear(%zu) returned NULL", sizeof(TestData));

    data->name = ccnxName_CreateFromURI("lci:/foo/bar");
    data->payloadType = CCNxPayloadType_DATA;

    data->payload = parcBuffer_Flip(parcBuffer_PutArray(parcBuffer_Allocate(20), 7, (uint8_t *) "payload"));
    data->contentObjectV0 = _ccnxContentObjectFacadeV0_CreateWithPayload(data->name, data->payloadType, data->payload);

    data->contentObjectV0Empty = ccnxCodecSchemaV0TlvDictionary_CreateContentObject();

    data->contentObjectVFF = ccnxTlvDictionary_Create(CCNxCodecSchemaV1TlvDictionary_MessageFastArray_END, CCNxCodecSchemaV1TlvDictionary_Lists_END);
    ccnxTlvDictionary_SetMessageType_ContentObject(data->contentObjectVFF, 0xFF);
    return data;
}

static void
_commonTeardown(TestData *data)
{
    ccnxName_Release(&data->name);
    parcBuffer_Release(&data->payload);

    ccnxTlvDictionary_Release(&data->contentObjectV0);
    ccnxTlvDictionary_Release(&data->contentObjectV0Empty);
    ccnxTlvDictionary_Release(&data->contentObjectVFF);
    parcMemory_Deallocate((void **) &data);
}

static PARCCryptoSuite
_ccnxContentObjectFacade_GetCryptoSuite(const CCNxTlvDictionary *contentObjectDictionary)
{
    if (ccnxValidationRsaSha256_Test(contentObjectDictionary)) {
        return PARCCryptoSuite_RSA_SHA256;
    }

    if (ccnxValidationHmacSha256_Test(contentObjectDictionary)) {
        return PARCCryptoSuite_HMAC_SHA256;
    }

    trapNotImplemented("Only RSA-SHA256 and HMAC-SHA256 supported");
}

static PARCBuffer *
_ccnxContentObjectFacade_EncodeFinalBlockId(uint64_t value)
{
    PARCBufferComposer *buffer = parcBufferComposer_Create();

    bool mustContinue = false;
    for (int byte = 7; byte >= 0; byte--) {
        uint8_t b = (value >> (byte * 8)) & 0xFF;
        if (b != 0 || byte == 0 || mustContinue) {
            parcBufferComposer_PutUint8(buffer, b);
            mustContinue = true;
        }
    }

    PARCBuffer *finalBuffer = parcBufferComposer_ProduceBuffer(buffer);
    parcBufferComposer_Release(&buffer);

    return finalBuffer;
}


LONGBOW_TEST_RUNNER(ccnx_ContentObjectFacade)
{
    // The following Test Fixtures will run their corresponding Test Cases.
    // Test Fixtures are run in the order specified, but all tests should be idempotent.
    // Never rely on the execution order of tests or share state between them.
    LONGBOW_RUN_TEST_FIXTURE(ImplInterface);
    LONGBOW_RUN_TEST_FIXTURE(Local);
}

// The Test Runner calls this function once before any Test Fixtures are run.
LONGBOW_TEST_RUNNER_SETUP(ccnx_ContentObjectFacade)
{
    parcMemory_SetInterface(&PARCSafeMemoryAsPARCMemory);
    return LONGBOW_STATUS_SUCCEEDED;
}

// The Test Runner calls this function once after all the Test Fixtures are run.
LONGBOW_TEST_RUNNER_TEARDOWN(ccnx_ContentObjectFacade)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

// ======================================================================================

LONGBOW_TEST_FIXTURE(ImplInterface)
{
    LONGBOW_RUN_TEST_CASE(ImplInterface, ccnxContentObjectFacadeV0_Init);

    LONGBOW_RUN_TEST_CASE(ImplInterface, ccnxContentObjectFacadeV0_GetName);
    LONGBOW_RUN_TEST_CASE(ImplInterface, ccnxContentObjectFacadeV0_GetPayload);
    LONGBOW_RUN_TEST_CASE(ImplInterface, ccnxContentObjectFacadeV0_GetPayloadType);
    LONGBOW_RUN_TEST_CASE(ImplInterface, ccnxContentObjectFacadeV0_GetPayloadType_Unset);
    LONGBOW_RUN_TEST_CASE(ImplInterface, ccnxContentObjectFacadeV0_SetSignature);

    LONGBOW_RUN_TEST_CASE(ImplInterface, ccnxContentObjectFacadeV0_ToString);
    LONGBOW_RUN_TEST_CASE(ImplInterface, _ccnxContentObjectFacadeV0_Display);
    LONGBOW_RUN_TEST_CASE(ImplInterface, ccnxContentObjectFacadeV0_SetPayload);
}

LONGBOW_TEST_FIXTURE_SETUP(ImplInterface)
{
    longBowTestCase_SetClipBoardData(testCase, _commonSetup());
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(ImplInterface)
{
    _commonTeardown(longBowTestCase_GetClipBoardData(testCase));

    uint32_t outstandingAllocations = parcSafeMemory_ReportAllocation(STDERR_FILENO);
    if (outstandingAllocations != 0) {
        printf("%s leaks memory by %d allocations\n", longBowTestCase_GetName(testCase), outstandingAllocations);
        return LONGBOW_STATUS_MEMORYLEAK;
    }
    return LONGBOW_STATUS_SUCCEEDED;
}

// ======================================================================================

LONGBOW_TEST_CASE(ImplInterface, ccnxContentObjectFacadeV0_Init)
{
    CCNxContentObjectInterface *impl = &CCNxContentObjectFacadeV0_Implementation;
    assertNotNull(impl->createWithPayload, "Expected CreateWithPayload to be set");
    assertNotNull(impl->getName, "Expected GetName to be set");
    assertNotNull(impl->setSignature, "Expected SetSignature to be set");
    assertNotNull(impl->getPayload, "Expected GetPayload to be set");
    assertNotNull(impl->getPayloadType, "Expected GetPayloadType to be set");

    assertNotNull(impl->hasFinalChunkNumber, "Expected HasFinalChunkNumber to be set");
    assertNotNull(impl->getFinalChunkNumber, "Expected GetFinalChunkNumber to be set");
    assertNotNull(impl->setFinalChunkNumber, "Expected SetFinalChunkNumber to be set");

    assertNotNull(impl->toString, "Expected ToString to be set");
    assertNotNull(impl->display, "Expected Display to be set");
}

LONGBOW_TEST_CASE(ImplInterface, ccnxContentObjectFacadeV0_GetName)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    CCNxName *test = _ccnxContentObjectFacadeV0_GetName(data->contentObjectV0);
    assertTrue(ccnxName_Equals(test, data->name), "Names do not match")
    {
        ccnxName_Display(test, 0);
        ccnxName_Display(data->name, 0);
    }
}

LONGBOW_TEST_CASE(ImplInterface, ccnxContentObjectFacadeV0_GetPayload)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    PARCBuffer *test = _ccnxContentObjectFacadeV0_GetPayload(data->contentObjectV0);
    assertTrue(parcBuffer_Equals(test, data->payload), "payloads do not match")
    {
        parcBuffer_Display(test, 0);
        parcBuffer_Display(data->payload, 0);
    }
}

LONGBOW_TEST_CASE(ImplInterface, ccnxContentObjectFacadeV0_GetPayloadType)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    CCNxPayloadType test = _ccnxContentObjectFacadeV0_GetPayloadType(data->contentObjectV0);
    assertTrue(test == data->payloadType, "payloads do not match, got %d expected %d", test, data->payloadType)
    {
        ccnxTlvDictionary_Display(data->contentObjectV0, 0);
    }
}

LONGBOW_TEST_CASE(ImplInterface, ccnxContentObjectFacadeV0_GetPayloadType_Unset)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    CCNxPayloadType test = _ccnxContentObjectFacadeV0_GetPayloadType(data->contentObjectV0Empty);
    assertTrue(test == CCNxPayloadType_DATA, "payloads do not match, got %d expected %d", test, CCNxPayloadType_DATA)
    {
        ccnxTlvDictionary_Display(data->contentObjectV0, 0);
    }
}

LONGBOW_TEST_CASE_EXPECTS(ImplInterface, ccnxContentObjectFacadeV0_ToString, .event = &LongBowTrapNotImplemented)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    _ccnxContentObjectFacadeV0_ToString(data->contentObjectV0);
}


LONGBOW_TEST_CASE(ImplInterface, _ccnxContentObjectFacadeV0_Display)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    _ccnxContentObjectFacadeV0_Display(data->contentObjectV0, 0);
}

// ======================================================================================

LONGBOW_TEST_FIXTURE(Local)
{
//    LONGBOW_RUN_TEST_CASE(Local, _ccnxContentObjectFacade_CreateKeyLocator_Key);
//    LONGBOW_RUN_TEST_CASE(Local, _ccnxContentObjectFacade_CreateKeyLocator_KeyName);

    LONGBOW_RUN_TEST_CASE(Local, ccnxContentObjectFacadeV0_GetCryptoSuite_RsaSha256);
    LONGBOW_RUN_TEST_CASE(Local, ccnxContentObjectFacadeV0_GetCryptoSuite_HmacSha256);
    LONGBOW_RUN_TEST_CASE(Local, ccnxContentObjectFacadeV0_GetCryptoSuite_Invalid);

    LONGBOW_RUN_TEST_CASE(Local, ccnxContentObjectFacadeV0_EncodeFinalBlockId);
}

LONGBOW_TEST_FIXTURE_SETUP(Local)
{
    longBowTestCase_SetClipBoardData(testCase, _commonSetup());

    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Local)
{
    _commonTeardown(longBowTestCase_GetClipBoardData(testCase));

    uint32_t outstandingAllocations = parcSafeMemory_ReportAllocation(STDERR_FILENO);
    if (outstandingAllocations != 0) {
        printf("%s leaks memory by %d allocations\n", longBowTestCase_GetName(testCase), outstandingAllocations);
        return LONGBOW_STATUS_MEMORYLEAK;
    }
    return LONGBOW_STATUS_SUCCEEDED;
}

// ======================================================================================

//LONGBOW_TEST_CASE(Local, _ccnxContentObjectFacade_CreateKeyLocator_Key)
//{
//    TestData *data = longBowTestCase_GetClipBoardData(testCase);
//
//    PARCBuffer *keyid = parcBuffer_Flip(parcBuffer_PutArray(parcBuffer_Allocate(20), 5, (uint8_t *) "keyid"));
//    CCNxKey *key = ccnxKey_CreateFromHexString("123456");
//    CCNxKeyLocator *keyLocator = ccnxKeyLocator_CreateFromCCNxKey(key);
//    ccnxValidationRsaSha256_Set(data->contentObjectV0, keyid, keyLocator);
//
//    CCNxKeyLocator *test = _ccnxContentObjectFacade_CreateKeyLocator(data->contentObjectV0);
//    assertTrue(ccnxKeyLocator_Equals(test, keyLocator), "Key Locators not equal");
//
//    ccnxKeyLocator_Release(&test);
//    ccnxKey_Release(&key);
//    ccnxKeyLocator_Release(&keyLocator);
//    parcBuffer_Release(&keyid);
//}
//
//LONGBOW_TEST_CASE(Local, _ccnxContentObjectFacade_CreateKeyLocator_KeyName)
//{
//    TestData *data = longBowTestCase_GetClipBoardData(testCase);
//
//    PARCBuffer *keyid = parcBuffer_Flip(parcBuffer_PutArray(parcBuffer_Allocate(20), 5, (uint8_t *) "keyid"));
//    CCNxName *keyname = ccnxName_CreateFromURI("lci:/key/name");
//    CCNxKeyLocator *keyLocator = ccnxKeyLocator_FromKeyName(keyname);
//    ccnxValidationRsaSha256_Set(data->contentObjectV0, keyid, keyLocator);
//
//    CCNxKeyLocator *test = _ccnxContentObjectFacade_CreateKeyLocator(data->contentObjectV0);
//    assertTrue(ccnxKeyLocator_Equals(test, keyLocator), "Key Locators not equal");
//
//    ccnxKeyLocator_Release(&test);
//    ccnxKeyLocator_Release(&keyLocator);
//    ccnxName_Release(&keyname);
//    parcBuffer_Release(&keyid);
//}

LONGBOW_TEST_CASE(Local, ccnxContentObjectFacadeV0_GetCryptoSuite_RsaSha256)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    ccnxValidationRsaSha256_Set(data->contentObjectV0, NULL, NULL);

    PARCCryptoSuite test = _ccnxContentObjectFacade_GetCryptoSuite(data->contentObjectV0);
    assertTrue(test == PARCCryptoSuite_RSA_SHA256, "Wrong suite, got %d expected %d", test, PARCCryptoSuite_RSA_SHA256);
}

LONGBOW_TEST_CASE(Local, ccnxContentObjectFacadeV0_GetCryptoSuite_HmacSha256)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    ccnxValidationHmacSha256_Set(data->contentObjectV0, NULL);

    PARCCryptoSuite test = _ccnxContentObjectFacade_GetCryptoSuite(data->contentObjectV0);
    assertTrue(test == PARCCryptoSuite_HMAC_SHA256, "Wrong suite, got %d expected %d", test, PARCCryptoSuite_HMAC_SHA256);
}

LONGBOW_TEST_CASE_EXPECTS(Local, ccnxContentObjectFacadeV0_GetCryptoSuite_Invalid, .event = &LongBowTrapNotImplemented)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    ccnxTlvDictionary_PutInteger(data->contentObjectV0, CCNxCodecSchemaV0TlvDictionary_ContentObjectFastArray_CRYPTO_SUITE, 0xFF);
    _ccnxContentObjectFacade_GetCryptoSuite(data->contentObjectV0);
}

LONGBOW_TEST_CASE(Local, ccnxContentObjectFacadeV0_EncodeFinalBlockId)
{
    struct test_struct {
        uint64_t value;
        size_t encodedBytes;
        uint8_t *encoded;
    } test_vector[] = {
        { .value = 0x0000000000000000ULL, .encodedBytes = 1, .encoded = (uint8_t[1]) { 0x00 } },
        { .value = 0x0000000000000001ULL, .encodedBytes = 1, .encoded = (uint8_t[1]) { 0x01 } },
        { .value = 0x00000000000000FFULL, .encodedBytes = 1, .encoded = (uint8_t[1]) { 0xFF } },
        { .value = 0x0000000000000100ULL, .encodedBytes = 2, .encoded = (uint8_t[2]) { 0x01, 0x00} },
        { .value = 0x0100000000000100ULL, .encodedBytes = 8, .encoded = (uint8_t[8]) { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00} },
        { .value = 0x8000000000000100ULL, .encodedBytes = 8, .encoded = (uint8_t[8]) { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00} },
        { .value = 0xFFFFFFFFFFFFFFFFULL, .encodedBytes = 8, .encoded = (uint8_t[8]) { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF} },
        { .value = 0,                     .encodedBytes = 0, .encoded = NULL }
    };

    for (int i = 0; test_vector[i].encoded != NULL; i++) {
        PARCBuffer *truthBuffer = parcBuffer_Allocate(test_vector[i].encodedBytes);
        parcBuffer_Flip(parcBuffer_PutArray(truthBuffer, test_vector[i].encodedBytes, test_vector[i].encoded));
        PARCBuffer *testbuffer = _ccnxContentObjectFacade_EncodeFinalBlockId(test_vector[i].value);

        assertTrue(parcBuffer_Equals(truthBuffer, testbuffer),
                   "Buffers do not match index %d value %016" PRIx64 ": expected %s got %s\n",
                   i,
                   test_vector[i].value,
                   parcBuffer_ToString(truthBuffer),
                   parcBuffer_ToString(testbuffer));

        parcBuffer_Release(&truthBuffer);
        parcBuffer_Release(&testbuffer);
    }
}

LONGBOW_TEST_CASE(ImplInterface, ccnxContentObjectFacadeV0_SetSignature)
{
    CCNxName *name = ccnxName_CreateFromURI("lci:/foo/bar/baz");
    PARCBuffer *payload = parcBuffer_Allocate(100);

    CCNxTlvDictionary *contentObject = _ccnxContentObjectFacadeV0_CreateWithPayload(name, CCNxPayloadType_DATA, payload);

    PARCBuffer *keyId = parcBuffer_WrapCString("keyhash");
    char *rawsig = "siggybits";
    PARCBuffer *sigbits = parcBuffer_CreateFromArray((void *) rawsig, strlen(rawsig));

    PARCSignature *signature = parcSignature_Create(PARCSigningAlgorithm_RSA, PARC_HASH_SHA256, parcBuffer_Flip(sigbits));
    parcBuffer_Release(&sigbits);

    assertTrue(_ccnxContentObjectFacadeV0_SetSignature(contentObject, keyId, signature, NULL),
               "Expected to be able to set the signature");

    ccnxName_Release(&name);
    parcBuffer_Release(&payload);
    parcSignature_Release(&signature);
    parcBuffer_Release(&keyId);
    ccnxTlvDictionary_Release(&contentObject);
}

LONGBOW_TEST_CASE(ImplInterface, ccnxContentObjectFacadeV0_SetPayload)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    PARCBuffer *newPayload = parcBuffer_WrapCString("this is a new payload");

    // Shouldn't be able to set it on an already initialized ContentObject.
    // (Though this may change...)
    assertFalse(_ccnxContentObjectFacadeV0_SetPayload(data->contentObjectV0, CCNxPayloadType_DATA, newPayload),
                "Expected to not be able to re-assign a payload on an already initialized ContentObject");

    CCNxTlvDictionary *contentObject =
        _ccnxContentObjectFacadeV0_CreateWithPayload(data->name,
                                                     CCNxPayloadType_DATA,
                                                     NULL);


    bool status = _ccnxContentObjectFacadeV0_SetPayload(contentObject, CCNxPayloadType_KEY, newPayload);
    assertTrue(status, "Expected to be able to set the buffer");

    PARCBuffer *testPayload = _ccnxContentObjectFacadeV0_GetPayload(contentObject);
    assertTrue(parcBuffer_Equals(newPayload, testPayload), "payloads do not match")
    {
        parcBuffer_Display(newPayload, 0);
        parcBuffer_Display(data->payload, 0);
    }

    CCNxPayloadType testType = _ccnxContentObjectFacadeV0_GetPayloadType(contentObject);
    assertTrue(testType == CCNxPayloadType_KEY, "Expected type KEY");

    parcBuffer_Release(&newPayload);
    ccnxTlvDictionary_Release(&contentObject);
}

// ======================================================================================

int
main(int argc, char *argv[])
{
    LongBowRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(ccnx_ContentObjectFacade);
    int exitStatus = longBowMain(argc, argv, testRunner, NULL);
    longBowTestRunner_Destroy(&testRunner);
    exit(exitStatus);
}
