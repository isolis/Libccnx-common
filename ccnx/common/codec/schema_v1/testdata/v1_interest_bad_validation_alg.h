/*
 * Copyright (c) 2014-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC)
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
 * @file v1_interest_bad_validation_alg.h
 * @brief Interest with CRC validation
 *
 * This is an error packet, the ValidationAlg TLV does not have the correct type
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2014-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef testdata_v1_interest_bad_validation_alg
#define testdata_v1_interest_bad_validation_alg

/**
 * A well formed interest with only a name
 */

#include <ccnx/common/codec/testdata/testdata_common.h>
#include <ccnx/common/codec/schema_v1/testdata/v1_InterestSchema.h>

__attribute__((unused))
static uint8_t v1_interest_bad_validation_alg[] = {
    0x01, 0x00, 0x00,   65,     // ver = 1, type = interest, length = 65
    0x20, 0x00, 0x00,   24,     // HopLimit = 32, reserved = 0, header length = 24
    // ------------------------
    0x00, 0x03, 0x00,   12,     // Interest Fragment
    0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08,     // fragment 0x0102030405060708
    0x05, 0xDC, 0x00, 0x00,     // MTU 1500, fragcnt 0, fragnum 0
    // ------------------------
    0x00, 0x01, 0x00, 0x15,     // type = interest, length = 21
    // ------------------------
    0x00, 0x00, 0x00, 0x11,     // type = name, length = 17
    0x00, 0x02, 0x00, 0x05,     // type = binary, length = 5
    'h',  'e',  'l',  'l',      // "hello"
    'o',
    0xF0, 0x00, 0x00, 0x04,     // type = app, length = 4
    'o',  'u',  'c',  'h',      // "ouch"
    // ------------------------
    0x00, 0xFF, 0x00,    4,     // Not "0x03" validation alg length = 4
    0x00, 0xFF, 0x00, 0x00,     // unknown validation alg
    // ------------------------
    0x00, 0x04, 0x00,    4,     // validation payload
    0x6A, 0xD7, 0xB1, 0xF2      // 6AD7B1F2
};

__attribute__((unused))
static TruthTableEntry TRUTHTABLENAME(v1_interest_bad_validation_alg)[] = {
    { .wellKnownType = true,  .indexOrKey = V1_MANIFEST_INT_E2EFRAG,           .bodyManifest=false, .extent = {12, 12} },
    { .wellKnownType = true,  .indexOrKey = V1_MANIFEST_INT_INTEREST,          .bodyManifest=true,  .extent = {24, 25} },
    { .wellKnownType = true,  .indexOrKey = V1_MANIFEST_INT_NAME,              .bodyManifest=true,  .extent = {32, 17} },
    { .wellKnownType = true,  .indexOrKey = V1_MANIFEST_INT_ValidationAlg,     .bodyManifest=true,  .extent = {53, 4} },
    { .wellKnownType = true,  .indexOrKey = V1_MANIFEST_INT_ValidationPayload, .bodyManifest=true,  .extent = {61, 4} },
    { .wellKnownType = false, .indexOrKey = T_INVALID,             .extent = { 0,  0} },
};

#define v1_interest_bad_validation_alg_truthTable TABLEENTRY(v1_interest_bad_validation_alg, TLV_ERR_NO_ERROR)

#endif
