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
 * @file ccnxCodecSchemaV1_ValidationDecoder.h
 * @brief Decode the validation algorithm and payload
 *
 * <#Detailed Description#>
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2014-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef __CCNx_Common__ccnxCodecSchemaV1_ValidationDecoder__
#define __CCNx_Common__ccnxCodecSchemaV1_ValidationDecoder__

#include <stdbool.h>

#include <ccnx/common/internal/ccnx_TlvDictionary.h>
#include <ccnx/common/codec/ccnxCodec_TlvDecoder.h>

/**
 * The decode the validation algorithm
 *
 * The decoder should point to byte 0 of the valdiation algorithm "value"
 *
 * The results are put in the provided dictionary.
 * It is an error if the "value" does not extend to the end of
 * the decoder.
 *
 * @param [in] decoder The decoder to parse
 * @param [in] packetDictionary The results go directly in to the provided dictionary.
 *
 * @return true Fully parsed, no errors
 * @return false Error decoding, decoder is left pointing to the first byte of the error
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
bool ccnxCodecSchemaV1ValidationDecoder_DecodeAlg(CCNxCodecTlvDecoder *decoder, CCNxTlvDictionary *packetDictionary);

/**
 * The decode the validation payload
 *
 * The decoder should point to byte 0 of the valdiation payload "value"
 * The payload is an opaque block, so this function will just put the "value" in to the proper
 * dictionary location.  There's no real parsing.
 *
 * @param [in] decoder The decoder to parse
 * @param [in] packetDictionary The results go directly in to the provided dictionary.
 *
 * @return true Fully parsed, no errors
 * @return false Error decoding, decoder is left pointing to the first byte of the error
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
bool ccnxCodecSchemaV1ValidationDecoder_DecodePayload(CCNxCodecTlvDecoder *decoder, CCNxTlvDictionary *packetDictionary);

#endif /* defined(__CCNx_Common__ccnxCodecSchemaV1_ValidationDecoder__) */
