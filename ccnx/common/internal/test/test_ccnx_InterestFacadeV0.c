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
#include "../ccnx_InterestFacadeV0.c"
#include <parc/algol/parc_SafeMemory.h>
#include <LongBow/unit-test.h>

#include <ccnx/common/ccnx_Interest.h>
#include <ccnx/transport/common/transport_MetaMessage.h>
#include <ccnx/common/codec/schema_v0/ccnxCodecSchemaV0_Packet.h>

typedef struct test_data {
    CCNxTlvDictionary *interest;

    CCNxName *name;
    PARCBuffer *keyid;
    PARCBuffer *contentObjectHash;

    // allocated data
    uint8_t keyidArray[32];
    uint8_t contentObjectHashArray[32];

    uint32_t lifetime;
    uint32_t hoplimit;
} TestData;

static TestData *
_commonSetup(void)
{
    TestData *data = parcMemory_AllocateAndClear(sizeof(TestData));
    assertNotNull(data, "parcMemory_AllocateAndClear(%zu) returned NULL", sizeof(TestData));
    data->name = ccnxName_CreateFromURI("lci:/once/upon/a/time");

    for (int i = 0; i < 32; i++) {
        data->keyidArray[i] = i * 7;
        data->contentObjectHashArray[i] = i * 11;
    }

    data->keyid = parcBuffer_Wrap(data->keyidArray, 32, 0, 32);
    data->contentObjectHash = parcBuffer_Wrap(data->contentObjectHashArray, 32, 0, 32);

    data->lifetime = 900;
    data->hoplimit = 77;

    data->interest = _ccnxInterestFacadeV0_Create(data->name,
                                                  data->lifetime,
                                                  data->keyid,
                                                  data->contentObjectHash,
                                                  data->hoplimit);

    return data;
}

static void
_commonTeardown(TestData *data)
{
    ccnxName_Release(&data->name);
    parcBuffer_Release(&data->keyid);
    parcBuffer_Release(&data->contentObjectHash);
    ccnxTlvDictionary_Release(&data->interest);

    parcMemory_Deallocate((void **) &data);
}

LONGBOW_TEST_RUNNER(ccnx_InterestFacadeV0)
{
    parcMemory_SetInterface(&PARCSafeMemoryAsPARCMemory);

    // The following Test Fixtures will run their corresponding Test Cases.
    // Test Fixtures are run in the order specified, but all tests should be idempotent.
    // Never rely on the execution order of tests or share state between them.
    LONGBOW_RUN_TEST_FIXTURE(Performance);

    LONGBOW_RUN_TEST_FIXTURE(Global);
    LONGBOW_RUN_TEST_FIXTURE(Local);
}

// The Test Runner calls this function once before any Test Fixtures are run.
LONGBOW_TEST_RUNNER_SETUP(ccnx_InterestFacadeV0)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

// The Test Runner calls this function once after all the Test Fixtures are run.
LONGBOW_TEST_RUNNER_TEARDOWN(ccnx_InterestFacadeV0)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

// ========================================================================================

LONGBOW_TEST_FIXTURE(Performance)
{
    LONGBOW_RUN_TEST_CASE(Performance, newfangled);
//    LONGBOW_RUN_TEST_CASE(Performance, oldtimey);
}

LONGBOW_TEST_FIXTURE_SETUP(Performance)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Performance)
{
    uint32_t outstandingAllocations = parcSafeMemory_ReportAllocation(STDERR_FILENO);
    if (outstandingAllocations != 0) {
        printf("%s leaks memory by %d allocations\n", longBowTestCase_GetName(testCase), outstandingAllocations);
        return LONGBOW_STATUS_MEMORYLEAK;
    }
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_CASE(Performance, newfangled)
{
    uint8_t keyidArray[32];
    for (int i = 0; i < 32; i++) {
        keyidArray[i] = i;
    }

    PARCBuffer *keyid = parcBuffer_Wrap(keyidArray, 32, 0, 32);
    CCNxName *name = ccnxName_CreateFromURI("lci:/dark/and/stormy/bits");

    struct timeval t0, t1;
    unsigned trials = 10000;
    gettimeofday(&t0, NULL);
    for (int i = 0; i < trials; i++) {
        CCNxTlvDictionary *interest = _ccnxInterestFacadeV0_Create(name,
                                                                   CCNxInterestDefault_LifetimeMilliseconds,
                                                                   keyid,
                                                                   NULL,
                                                                   0x45);

        CCNxCodecNetworkBufferIoVec *vec = ccnxCodecSchemaV0PacketEncoder_DictionaryEncode(interest, NULL);
        ccnxCodecNetworkBufferIoVec_Release(&vec);
        ccnxTlvDictionary_Release(&interest);
    }
    gettimeofday(&t1, NULL);
    timersub(&t1, &t0, &t1);
    double seconds = t1.tv_sec + t1.tv_usec * 1E-6;
    printf("\nNewFangled iterations %u seconds %.3f msg/sec %.3f\n", trials, seconds, trials / seconds);

    ccnxName_Release(&name);
    parcBuffer_Release(&keyid);
}

// ========================================================================================

LONGBOW_TEST_FIXTURE(Global)
{
    LONGBOW_RUN_TEST_CASE(Global, ccnxInterestFacadeV0_AssertValid);
    LONGBOW_RUN_TEST_CASE(Global, ccnxInterestFacadeV0_CreateSimple);

    LONGBOW_RUN_TEST_CASE(Global, ccnxInterestFacadeV0_Display);
    LONGBOW_RUN_TEST_CASE(Global, ccnxInterestFacadeV0_Equals);
    LONGBOW_RUN_TEST_CASE(Global, ccnxInterestFacadeV0_GetContentObjectHash);
    LONGBOW_RUN_TEST_CASE(Global, ccnxInterestFacadeV0_GetHopLimit);
    LONGBOW_RUN_TEST_CASE(Global, ccnxInterestFacadeV0_GetInterestLifetime);
    LONGBOW_RUN_TEST_CASE(Global, ccnxInterestFacadeV0_GetName);
    LONGBOW_RUN_TEST_CASE(Global, ccnxInterestFacadeV0_GetKeyIdRestriction);
}

LONGBOW_TEST_FIXTURE_SETUP(Global)
{
    longBowTestCase_SetClipBoardData(testCase, _commonSetup());

    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Global)
{
    _commonTeardown(longBowTestCase_GetClipBoardData(testCase));

    uint32_t outstandingAllocations = parcSafeMemory_ReportAllocation(STDERR_FILENO);
    if (outstandingAllocations != 0) {
        printf("%s leaks memory by %d allocations\n", longBowTestCase_GetName(testCase), outstandingAllocations);
        return LONGBOW_STATUS_MEMORYLEAK;
    }
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_CASE(Global, ccnxInterestFacadeV0_AssertValid)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    _ccnxInterestFacadeV0_AssertValid(data->interest);
}

LONGBOW_TEST_CASE(Global, ccnxInterestFacadeV0_CreateSimple)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    CCNxTlvDictionary *interest = _ccnxInterestFacadeV0_CreateSimple(data->name);

    CCNxName *test = _ccnxInterestFacadeV0_GetName(interest);
    assertTrue(ccnxName_Equals(test, data->name), "Names do not match");
    ccnxTlvDictionary_Release(&interest);
}

LONGBOW_TEST_CASE(Global, ccnxInterestFacadeV0_Display)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    _ccnxInterestFacadeV0_Display(data->interest, 0);
}

LONGBOW_TEST_CASE(Global, ccnxInterestFacadeV0_Equals)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    CCNxTlvDictionary *a = _ccnxInterestFacadeV0_CreateSimple(data->name);
    CCNxTlvDictionary *b = _ccnxInterestFacadeV0_CreateSimple(data->name);

    bool success = _ccnxInterestFacadeV0_Equals(a, b);
    assertTrue(success, "Two equal interests not equal");
    ccnxTlvDictionary_Release(&a);
    ccnxTlvDictionary_Release(&b);
}


LONGBOW_TEST_CASE(Global, ccnxInterestFacadeV0_GetContentObjectHash)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    PARCBuffer *test = _ccnxInterestFacadeV0_GetContentObjectHashRestriction(data->interest);
    assertTrue(parcBuffer_Equals(test, data->contentObjectHash), "KeyIDs do not match")
    {
        printf("\ngot     : \n"); parcBuffer_Display(test, 3);
        printf("\nexpected: \n"); parcBuffer_Display(data->contentObjectHash, 3);
    }
}

LONGBOW_TEST_CASE(Global, ccnxInterestFacadeV0_GetHopLimit)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    unsigned test = (unsigned) _ccnxInterestFacadeV0_GetHopLimit(data->interest);
    assertTrue(test == data->hoplimit, "Wrong hoplimit: got %u expected %u", test, data->hoplimit);
}

LONGBOW_TEST_CASE(Global, ccnxInterestFacadeV0_GetInterestLifetime)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    unsigned test = (unsigned) _ccnxInterestFacadeV0_GetLifetime(data->interest);
    assertTrue(test == data->lifetime, "Wrong lifetime: got %u expected %u", test, data->lifetime);
}

LONGBOW_TEST_CASE(Global, ccnxInterestFacadeV0_GetName)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    CCNxName *test = _ccnxInterestFacadeV0_GetName(data->interest);
    assertTrue(ccnxName_Equals(test, data->name), "Names do not match")
    {
        printf("\ngot     : \n"); ccnxName_Display(test, 3);
        printf("\nexpected: \n"); ccnxName_Display(data->name, 3);
    }
}

LONGBOW_TEST_CASE(Global, ccnxInterestFacadeV0_GetKeyIdRestriction)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    PARCBuffer *test = _ccnxInterestFacadeV0_GetKeyIdRestriction(data->interest);
    assertTrue(parcBuffer_Equals(test, data->keyid), "KeyIDs do not match")
    {
        printf("\ngot     : \n"); parcBuffer_Display(test, 3);
        printf("\nexpected: \n"); parcBuffer_Display(data->keyid, 3);
    }
}

// ========================================================================================

LONGBOW_TEST_FIXTURE(Local)
{
}

LONGBOW_TEST_FIXTURE_SETUP(Local)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Local)
{
    uint32_t outstandingAllocations = parcSafeMemory_ReportAllocation(STDERR_FILENO);
    if (outstandingAllocations != 0) {
        printf("%s leaks memory by %d allocations\n", longBowTestCase_GetName(testCase), outstandingAllocations);
        return LONGBOW_STATUS_MEMORYLEAK;
    }
    return LONGBOW_STATUS_SUCCEEDED;
}

int
main(int argc, char *argv[])
{
    LongBowRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(ccnx_InterestFacadeV0);
    int exitStatus = longBowMain(argc, argv, testRunner, NULL);
    longBowTestRunner_Destroy(&testRunner);
    exit(exitStatus);
}
