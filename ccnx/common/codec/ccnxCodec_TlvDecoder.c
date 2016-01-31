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
 * We use a 2-byte T and a 2-byte L
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <LongBow/runtime.h>
#include <parc/algol/parc_Memory.h>
#include <parc/algol/parc_Buffer.h>
#include <ccnx/common/codec/ccnxCodec_NetworkBuffer.h>

#include <ccnx/common/codec/ccnxCodec_TlvDecoder.h>

struct ccnx_codec_tlv_decoder {
    // we use a read only buffer because we want independent
    // position and limit from whatever the user gives us.
    PARCBuffer *buffer;

    CCNxCodecError *error;
};

CCNxCodecTlvDecoder *
ccnxCodecTlvDecoder_Create(PARCBuffer *buffer)
{
    assertNotNull(buffer, "Parameter buffer must be non-null");

    CCNxCodecTlvDecoder *decoder = parcMemory_AllocateAndClear(sizeof(CCNxCodecTlvDecoder));
    assertNotNull(decoder, "parcMemory_AllocateAndClear(%zu) returned NULL", sizeof(CCNxCodecTlvDecoder));

    // create a reference but with independent position + limit from what the user gives us
    decoder->buffer = parcBuffer_Slice(buffer);

    return decoder;
}

void
ccnxCodecTlvDecoder_Destroy(CCNxCodecTlvDecoder **decoderPtr)
{
    assertNotNull(decoderPtr, "Parameter must be non-null double pointer");
    assertNotNull(*decoderPtr, "Parameter must dereferecne to non-null pointer");
    CCNxCodecTlvDecoder *decoder = *decoderPtr;
    parcBuffer_Release(&decoder->buffer);


    if (decoder->error) {
        ccnxCodecError_Release(&decoder->error);
    }

    parcMemory_Deallocate((void **) &decoder);
    *decoderPtr = NULL;
}

bool
ccnxCodecTlvDecoder_IsEmpty(CCNxCodecTlvDecoder *decoder)
{
    assertNotNull(decoder, "Parameter decoder must be non-null");
    return (!parcBuffer_HasRemaining(decoder->buffer));
}

bool
ccnxCodecTlvDecoder_EnsureRemaining(CCNxCodecTlvDecoder *decoder, size_t bytes)
{
    assertNotNull(decoder, "Parameter decoder must be non-null");
    return parcBuffer_Remaining(decoder->buffer) >= bytes;
}

size_t
ccnxCodecTlvDecoder_Remaining(const CCNxCodecTlvDecoder *decoder)
{
    assertNotNull(decoder, "Parameter decoder must be non-null");
    return parcBuffer_Remaining(decoder->buffer);
}

uint16_t
ccnxCodecTlvDecoder_PeekType(CCNxCodecTlvDecoder *decoder)
{
    assertNotNull(decoder, "Parameter decoder must be non-null");
    size_t position = parcBuffer_Position(decoder->buffer);
    uint16_t type = parcBuffer_GetUint16(decoder->buffer);
    parcBuffer_SetPosition(decoder->buffer, position);
    return type;
}

uint16_t
ccnxCodecTlvDecoder_GetType(CCNxCodecTlvDecoder *decoder)
{
    assertNotNull(decoder, "Parameter decoder must be non-null");
    return parcBuffer_GetUint16(decoder->buffer);
}

uint16_t
ccnxCodecTlvDecoder_GetLength(CCNxCodecTlvDecoder *decoder)
{
    assertNotNull(decoder, "Parameter decoder must be non-null");
    return parcBuffer_GetUint16(decoder->buffer);
}

PARCBuffer *
ccnxCodecTlvDecoder_GetValue(CCNxCodecTlvDecoder *decoder, uint16_t length)
{
    assertNotNull(decoder, "Parameter decoder must be non-null");
    PARCBuffer *value = NULL;

    if (ccnxCodecTlvDecoder_EnsureRemaining(decoder, length)) {
        value = parcBuffer_Slice(decoder->buffer);
        parcBuffer_SetLimit(value, length);

        size_t position = parcBuffer_Position(decoder->buffer);
        position += length;
        parcBuffer_SetPosition(decoder->buffer, position);
    }

    return value;
}

PARCBuffer *
ccnxCodecTlvDecoder_GetBuffer(CCNxCodecTlvDecoder *decoder, uint16_t type)
{
    assertNotNull(decoder, "Parameter decoder must be non-null");

    PARCBuffer *output = NULL;
    if (ccnxCodecTlvDecoder_EnsureRemaining(decoder, 4)) {
        if (ccnxCodecTlvDecoder_PeekType(decoder) == type) {
            (void) ccnxCodecTlvDecoder_GetType(decoder);
            uint16_t length = ccnxCodecTlvDecoder_GetLength(decoder);
            output = ccnxCodecTlvDecoder_GetValue(decoder, length);
        }
    }
    return output;
}

CCNxCodecTlvDecoder *
ccnxCodecTlvDecoder_GetContainer(CCNxCodecTlvDecoder *decoder, uint16_t length)
{
    CCNxCodecTlvDecoder *innerDecoder = NULL;
    if (ccnxCodecTlvDecoder_EnsureRemaining(decoder, length)) {
        PARCBuffer *value = ccnxCodecTlvDecoder_GetValue(decoder, length);
        innerDecoder = ccnxCodecTlvDecoder_Create(value);
        parcBuffer_Release(&value);
    }
    return innerDecoder;
}

bool
ccnxCodecTlvDecoder_GetUint8(CCNxCodecTlvDecoder *decoder, uint16_t type, uint8_t *output)
{
    const size_t valueLength = 1;
    bool success = false;
    if (parcBuffer_Remaining(decoder->buffer) >= 4 + valueLength) {
        if (ccnxCodecTlvDecoder_PeekType(decoder) == type) {
            // advance the buffer
            (void) ccnxCodecTlvDecoder_GetType(decoder);
            if (ccnxCodecTlvDecoder_GetLength(decoder) == valueLength) {
                *output = parcBuffer_GetUint8(decoder->buffer);
                success = true;
            }
        }
    }
    return success;
}

bool
ccnxCodecTlvDecoder_GetUint16(CCNxCodecTlvDecoder *decoder, uint16_t type, uint16_t *output)
{
    const size_t valueLength = 2;
    bool success = false;
    if (parcBuffer_Remaining(decoder->buffer) >= 4 + valueLength) {
        if (ccnxCodecTlvDecoder_PeekType(decoder) == type) {
            // advance the buffer
            (void) ccnxCodecTlvDecoder_GetType(decoder);
            if (ccnxCodecTlvDecoder_GetLength(decoder) == valueLength) {
                *output = parcBuffer_GetUint16(decoder->buffer);
                success = true;
            }
        }
    }
    return success;
}

bool
ccnxCodecTlvDecoder_GetUint32(CCNxCodecTlvDecoder *decoder, uint16_t type, uint32_t *output)
{
    const size_t valueLength = 4;
    bool success = false;
    if (parcBuffer_Remaining(decoder->buffer) >= 4 + valueLength) {
        if (ccnxCodecTlvDecoder_PeekType(decoder) == type) {
            // advance the buffer
            (void) ccnxCodecTlvDecoder_GetType(decoder);
            if (ccnxCodecTlvDecoder_GetLength(decoder) == valueLength) {
                *output = parcBuffer_GetUint32(decoder->buffer);
                success = true;
            }
        }
    }
    return success;
}

bool
ccnxCodecTlvDecoder_GetUint64(CCNxCodecTlvDecoder *decoder, uint16_t type, uint64_t *output)
{
    const size_t valueLength = 8;
    bool success = false;
    if (parcBuffer_Remaining(decoder->buffer) >= 4 + valueLength) {
        if (ccnxCodecTlvDecoder_PeekType(decoder) == type) {
            // advance the buffer
            (void) ccnxCodecTlvDecoder_GetType(decoder);
            if (ccnxCodecTlvDecoder_GetLength(decoder) == valueLength) {
                *output = parcBuffer_GetUint64(decoder->buffer);
                success = true;
            }
        }
    }
    return success;
}


size_t
ccnxCodecTlvDecoder_Position(CCNxCodecTlvDecoder *decoder)
{
    assertNotNull(decoder, "Parameter decoder must be non-null");
    return parcBuffer_Position(decoder->buffer);
}

bool
ccnxCodecTlvDecoder_Advance(CCNxCodecTlvDecoder *decoder, uint16_t length)
{
    assertNotNull(decoder, "Parameter decoder must be non-null");
    bool success = false;
    if (parcBuffer_Remaining(decoder->buffer) >= length) {
        size_t position = parcBuffer_Position(decoder->buffer);
        position += length;
        parcBuffer_SetPosition(decoder->buffer, position);
        success = true;
    }
    return success;
}

bool
ccnxCodecTlvDecoder_BufferToVarInt(PARCBuffer *buffer, uint16_t length, uint64_t *output)
{
    assertNotNull(buffer, "Parameter buffer must be non-null");
    assertNotNull(output, "Parameter output must be non-null");

    bool success = false;
    if (length >= 1 && length <= 8 && parcBuffer_Remaining(buffer) >= length) {
        uint64_t value = 0;
        for (int i = 0; i < length; i++) {
            value = value << 8 | parcBuffer_GetUint8(buffer);
        }
        *output = value;
        success = true;
    }
    return success;
}

bool
ccnxCodecTlvDecoder_GetVarInt(CCNxCodecTlvDecoder *decoder, uint16_t length, uint64_t *output)
{
    assertNotNull(decoder, "Parameter decoder must be non-null");
    return ccnxCodecTlvDecoder_BufferToVarInt(decoder->buffer, length, output);
}

bool
ccnxCodecTlvDecoder_HasError(const CCNxCodecTlvDecoder *decoder)
{
    assertNotNull(decoder, "Parameter decoder must be non-null");
    if (decoder->error) {
        return true;
    }

    return false;
}


bool
ccnxCodecTlvDecoder_SetError(CCNxCodecTlvDecoder *decoder, CCNxCodecError *error)
{
    assertNotNull(decoder, "Parameter decoder must be non-null");
    if (ccnxCodecTlvDecoder_HasError(decoder)) {
        return false;
    }

    decoder->error = ccnxCodecError_Acquire(error);
    return true;
}


void
ccnxCodecTlvDecoder_ClearError(CCNxCodecTlvDecoder *decoder)
{
    assertNotNull(decoder, "Parameter decoder must be non-null");
    if (ccnxCodecTlvDecoder_HasError(decoder)) {
        ccnxCodecError_Release(&decoder->error);
    }
}


CCNxCodecError *
ccnxCodecTlvDecoder_GetError(const CCNxCodecTlvDecoder *decoder)
{
    assertNotNull(decoder, "Parameter decoder must be non-null");
    return decoder->error;
}
