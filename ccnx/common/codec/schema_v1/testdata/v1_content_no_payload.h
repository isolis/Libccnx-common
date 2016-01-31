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
 * @file v1_content_no_payload.h
 * @brief Content Object without a payload TLV
 *
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */


#ifndef CCNx_Common_v1_content_no_payload_h
#define CCNx_Common_v1_content_no_payload_h

#include <ccnx/common/codec/testdata/testdata_common.h>
#include <ccnx/common/codec/schema_v1/testdata/v1_ContentObjectSchema.h>

__attribute__((unused))
static uint8_t v1_content_no_payload[] = {
    0x01, 0x01, 0x00, 0x21,
    0x00, 0x00, 0x00, 0x08,
    // -- content object
    0x00, 0x02, 0x00, 0x15,
    // -- name
    0x00, 0x00, 0x00, 0x11,
    0x00, 0x02, 0x00, 0x02,
    0x6e, 0x6f,
    0x00, 0x02, 0x00, 0x07,
    0x70, 0x61, 0x79, 0x6c,
    0x6f, 0x61, 0x64
};

__attribute__((unused))
static TruthTableEntry TRUTHTABLENAME(v1_content_no_payload)[] = {
    { .wellKnownType = true,  .indexOrKey = V1_MANIFEST_OBJ_CONTENTOBJECT,  .bodyManifest=true,  .extent = {12, 21} },
    { .wellKnownType = false, .indexOrKey = T_INVALID,             .extent = { 0,  0} },
};

#define v1_content_no_payload_truthTable TABLEENTRY(v1_content_no_payload, TLV_ERR_NO_ERROR)

#endif
