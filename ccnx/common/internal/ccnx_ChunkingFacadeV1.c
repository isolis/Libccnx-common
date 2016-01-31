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

#include <config.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <LongBow/runtime.h>

#include <ccnx/common/internal/ccnx_ChunkingFacadeV1.h>
#include <ccnx/common/codec/schema_v1/ccnxCodecSchemaV1_TlvDictionary.h>

static void
_assertInvariants(const CCNxTlvDictionary *dictionary)
{
    assertNotNull(dictionary, "Parameter contentObjectDictionary must be non-null");
    trapIllegalValueIf(ccnxTlvDictionary_GetSchemaVersion(dictionary) != CCNxTlvDictionary_SchemaVersion_V1,
                       "Wrong schema version, expected %d got %d",
                       CCNxTlvDictionary_SchemaVersion_V1,
                       ccnxTlvDictionary_GetSchemaVersion(dictionary));
}

bool
ccnxChunkingFacadeV1_HasEndChunkNumber(const CCNxTlvDictionary *contentObjectDictionary)
{
    _assertInvariants(contentObjectDictionary);
    return ccnxTlvDictionary_IsValueInteger(contentObjectDictionary, CCNxCodecSchemaV1TlvDictionary_MessageFastArray_ENDSEGMENT);
}

uint64_t
ccnxChunkingFacadeV1_GetEndChunkNumber(const CCNxTlvDictionary *contentObjectDictionary)
{
    _assertInvariants(contentObjectDictionary);
    return ccnxTlvDictionary_GetInteger(contentObjectDictionary, CCNxCodecSchemaV1TlvDictionary_MessageFastArray_ENDSEGMENT);
}

bool
ccnxChunkingFacadeV1_SetEndChunkNumber(CCNxTlvDictionary *contentObjectDictionary, uint64_t endChunkNumber)
{
    _assertInvariants(contentObjectDictionary);
    trapIllegalValueIf(!ccnxTlvDictionary_IsContentObject(contentObjectDictionary), "Dictionary is not a ContentObject");
    return ccnxTlvDictionary_PutInteger(contentObjectDictionary, CCNxCodecSchemaV1TlvDictionary_MessageFastArray_ENDSEGMENT, endChunkNumber);
}
