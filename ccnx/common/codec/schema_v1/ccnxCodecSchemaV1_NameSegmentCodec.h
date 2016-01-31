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
 * @file ccnxCodecSchemaV1_NameSegmentCodec.h
 * @brief TLV codec for CCNx types
 *
 * Encode/decode a CCNx name segment using the V1 schema
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef CCNxCodecSchemaV1_NameSegmentCodec_h
#define CCNxCodecSchemaV1_NameSegmentCodec_h

#include <ccnx/common/codec/ccnxCodec_TlvEncoder.h>
#include <ccnx/common/codec/ccnxCodec_TlvDecoder.h>
#include <ccnx/common/ccnx_Name.h>

/**
 * Encodes the name segment using the segment type as the TLV type
 *
 * Appends the name segment to the encoder.  The TLV type is implicit in
 * the CCNxNameSegment.
 *
 * @param [<#in out in,out#>] <#name#> <#description#>
 *
 * @return number The number of bytes appended, including the type and length.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
size_t ccnxCodecSchemaV1NameSegmentCodec_Encode(CCNxCodecTlvEncoder *encoder, CCNxNameSegment *segment);

/**
 * Decodes the current location of the decoder as a CCNxNameSegment
 *
 * <#Paragraphs Of Explanation#>
 *
 * @param [in] decoder The decoder object
 *
 * @return non-null A CCNxNameSement
 * @return null An error, such as buffer underrun
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
CCNxNameSegment *ccnxCodecSchemaV1NameSegmentCodec_Decode(CCNxCodecTlvDecoder *decoder);
#endif // CCNxCodecSchemaV1_NameSegmentCodec_h
