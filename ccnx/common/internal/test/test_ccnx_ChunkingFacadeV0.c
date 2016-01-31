/*
 * Copyright (c) 2013-2014, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
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
 * @copyright 2013-2014, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

// Include the file(s) containing the functions to be tested.
// This permits internal static functions to be visible to this Test Framework.
#include "../ccnx_ChunkingFacadeV0.c"
#include <parc/algol/parc_SafeMemory.h>

#include <LongBow/unit-test.h>
#include <inttypes.h>

#include <ccnx/common/ccnx_ContentObject.h>
#include <ccnx/common/ccnx_Interest.h>
#include <ccnx/common/ccnx_PayloadType.h>

#include <ccnx/common/internal/ccnx_ContentObjectInterface.h>
#include <ccnx/common/internal/ccnx_InterestInterface.h>

typedef struct test_data {
    CCNxName *name;
    CCNxTlvDictionary *contentObjectV0;
    CCNxTlvDictionary *interest;
} TestData;

static TestData *
_commonSetup(void)
{
    TestData *data = parcMemory_AllocateAndClear(sizeof(TestData));
    assertNotNull(data, "parcMemory_AllocateAndClear(%zu) returned NULL", sizeof(TestData));

    data->name = ccnxName_CreateFromURI("lci:/foo/bar");
    data->contentObjectV0 = CCNxContentObjectFacadeV0_Implementation.createWithPayload(data->name, CCNxPayloadType_DATA, NULL);

    data->interest = CCNxInterestFacadeV0_Implementation.create(data->name, 5000, NULL, NULL, 100);

    return data;
}

static void
_commonTeardown(TestData *data)
{
    ccnxName_Release(&data->name);
    ccnxTlvDictionary_Release(&data->contentObjectV0);
    ccnxTlvDictionary_Release(&data->interest);
    parcMemory_Deallocate((void **) &data);
}

LONGBOW_TEST_RUNNER(ccnx_ChunkingFacade)
{
    // The following Test Fixtures will run their corresponding Test Cases.
    // Test Fixtures are run in the order specified, but all tests should be idempotent.
    // Never rely on the execution order of tests or share state between them.
    LONGBOW_RUN_TEST_FIXTURE(Global);
    LONGBOW_RUN_TEST_FIXTURE(Local);
}

// The Test Runner calls this function once before any Test Fixtures are run.
LONGBOW_TEST_RUNNER_SETUP(ccnx_ChunkingFacade)
{
    parcMemory_SetInterface(&PARCSafeMemoryAsPARCMemory);
    return LONGBOW_STATUS_SUCCEEDED;
}

// The Test Runner calls this function once after all the Test Fixtures are run.
LONGBOW_TEST_RUNNER_TEARDOWN(ccnx_ChunkingFacade)
{
    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE(Global)
{
    LONGBOW_RUN_TEST_CASE(Global, ccnxChunkingFacade_GetEndChunkNumber_NotContentObject);
    LONGBOW_RUN_TEST_CASE(Global, ccnxChunkingFacade_GetEndChunkNumber_V0_With);
    LONGBOW_RUN_TEST_CASE(Global, ccnxChunkingFacade_GetEndChunkNumber_V0_Without);

    LONGBOW_RUN_TEST_CASE(Global, ccnxChunkingFacade_HasEndChunkNumber_NotContentObject);
    LONGBOW_RUN_TEST_CASE(Global, ccnxChunkingFacade_HasEndChunkNumber_V0_With);
    LONGBOW_RUN_TEST_CASE(Global, ccnxChunkingFacade_HasEndChunkNumber_V0_Without);

    LONGBOW_RUN_TEST_CASE(Global, ccnxChunkingFacade_SetEndChunkNumber_NotContentObject);
    LONGBOW_RUN_TEST_CASE(Global, ccnxChunkingFacade_SetEndChunkNumber_V0);
}

LONGBOW_TEST_FIXTURE_SETUP(Global)
{
    longBowTestCase_SetClipBoardData(testCase, _commonSetup());

    return LONGBOW_STATUS_SUCCEEDED;
}

LONGBOW_TEST_FIXTURE_TEARDOWN(Global)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    _commonTeardown(data);

    uint32_t outstandingAllocations = parcSafeMemory_ReportAllocation(STDERR_FILENO);
    if (outstandingAllocations != 0) {
        printf("%s leaks memory by %d allocations\n", longBowTestCase_GetName(testCase), outstandingAllocations);
        return LONGBOW_STATUS_MEMORYLEAK;
    }
    return LONGBOW_STATUS_SUCCEEDED;
}

// ======================================================================================

LONGBOW_TEST_CASE_EXPECTS(Global, ccnxChunkingFacade_GetEndChunkNumber_NotContentObject, .event = &LongBowTrapIllegalValue)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    ccnxChunkingFacadeV0_GetEndChunkNumber(data->interest);
}

LONGBOW_TEST_CASE(Global, ccnxChunkingFacade_GetEndChunkNumber_V0_With)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    uint64_t endChunkNumber = 5;

    ccnxChunkingFacadeV0_SetEndChunkNumber(data->contentObjectV0, endChunkNumber);
    uint64_t test = ccnxChunkingFacadeV0_GetEndChunkNumber(data->contentObjectV0);
    assertTrue(test == endChunkNumber, "wrong value, got %" PRIu64 " expected %" PRIu64, test, endChunkNumber)
    {
        ccnxTlvDictionary_Display(data->contentObjectV0, 3);
    }
}

LONGBOW_TEST_CASE_EXPECTS(Global, ccnxChunkingFacade_GetEndChunkNumber_V0_Without, .event = &LongBowTrapIllegalValue)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    ccnxChunkingFacadeV0_GetEndChunkNumber(data->contentObjectV0);
}


// ======================================================================================


LONGBOW_TEST_CASE(Global, ccnxChunkingFacade_HasEndChunkNumber_NotContentObject)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    bool success = ccnxChunkingFacadeV0_HasEndChunkNumber(data->interest);
    assertFalse(success, "An Interest should always return FALSE for EndChunkNumber");
}

LONGBOW_TEST_CASE(Global, ccnxChunkingFacade_HasEndChunkNumber_V0_With)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);

    ccnxChunkingFacadeV0_SetEndChunkNumber(data->contentObjectV0, 5);
    bool success = ccnxChunkingFacadeV0_HasEndChunkNumber(data->contentObjectV0);
    assertTrue(success, "Content Object with EndChunkNumber returned false")
    {
        ccnxTlvDictionary_Display(data->contentObjectV0, 3);
    }
}

LONGBOW_TEST_CASE(Global, ccnxChunkingFacade_HasEndChunkNumber_V0_Without)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);

    bool success = ccnxChunkingFacadeV0_HasEndChunkNumber(data->contentObjectV0);
    assertFalse(success, "Content Object without EndChunkNumber returned true")
    {
        ccnxTlvDictionary_Display(data->contentObjectV0, 3);
    }
}

// ======================================================================================

LONGBOW_TEST_CASE_EXPECTS(Global, ccnxChunkingFacade_SetEndChunkNumber_NotContentObject, .event = &LongBowTrapIllegalValue)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    uint64_t endChunkNumber = 7;
    ccnxChunkingFacadeV0_SetEndChunkNumber(data->interest, endChunkNumber);
}

LONGBOW_TEST_CASE(Global, ccnxChunkingFacade_SetEndChunkNumber_V0)
{
    TestData *data = longBowTestCase_GetClipBoardData(testCase);
    uint64_t endChunkNumber = 7;
    bool success = ccnxChunkingFacadeV0_SetEndChunkNumber(data->contentObjectV0, endChunkNumber);

    assertTrue(success, "Setting EndChunkNumber failed")
    {
        ccnxTlvDictionary_Display(data->contentObjectV0, 3);
    }
}

// ======================================================================================

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
    LongBowRunner *testRunner = LONGBOW_TEST_RUNNER_CREATE(ccnx_ChunkingFacade);
    int exitStatus = longBowMain(argc, argv, testRunner, NULL);
    longBowTestRunner_Destroy(&testRunner);
    exit(exitStatus);
}
