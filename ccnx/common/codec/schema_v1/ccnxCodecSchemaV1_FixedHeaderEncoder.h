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
 * @file ccnxCodecSchemaV1_FixedHeaderEncoder.h
 * @brief <#Brief Description#>
 *
 * <#Detailed Description#>
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef Libccnx_ccnxCodecSchemaV1_FixedHeaderEncoder_h
#define Libccnx_ccnxCodecSchemaV1_FixedHeaderEncoder_h

#include <ccnx/common/codec/ccnxCodec_TlvEncoder.h>

#include <ccnx/common/codec/schema_v1/ccnxCodecSchemaV1_FixedHeader.h>

/**
 * Set the values in the fixed header
 *
 * Put the provided fixed header at the given byte location.  The provided fixed header is not put
 * in as-is (i.e byte for byte), but is parsed and put in the correct byte positions and encodings
 * assuming the fixed header starts at the given position.
 *
 * The encoder is returned to its current position after putting the header.
 *
 * @param [in] encoder The encoder to append the fixed header in to
 * @param [in] The header, in host byte order
 *
 * @return Number The bytes appended, or -1 on error
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
ssize_t ccnxCodecSchemaV1FixedHeaderEncoder_EncodeHeader(CCNxCodecTlvEncoder *encoder, const CCNxCodecSchemaV1FixedHeader *header);
#endif // Libccnx_ccnxCodecSchemaV1_FixedHeaderEncoder_h
