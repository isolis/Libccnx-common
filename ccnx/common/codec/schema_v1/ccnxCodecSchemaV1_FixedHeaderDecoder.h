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
#ifndef Libccnx_ccnxCodecSchemaV1_FixedHeaderDecoder_h
#define Libccnx_ccnxCodecSchemaV1_FixedHeaderDecoder_h

#include <stdbool.h>

#include <parc/algol/parc_Buffer.h>

#include <ccnx/common/internal/ccnx_TlvDictionary.h>
#include <ccnx/common/codec/ccnxCodec_TlvDecoder.h>

/**
 * The decode a V1 fixed header
 *
 * The decoder should point to byte 0 of the Fixed Header.
 * It will be advanced to the first byte following it.
 * The results are put in the provided.
 *
 * @param [in] decoder The decoder to parse
 * @param [in] dictionary The results go directly in to the provided dictionary.
 *
 * @return true Fully parsed interest, no errors
 * @return false Error decoding, decoder is left pointing to the first byte of the error
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
bool ccnxCodecSchemaV1FixedHeaderDecoder_Decode(CCNxCodecTlvDecoder *decoder, CCNxTlvDictionary *packetDictionary);

/**
 * A convenience function to return the version
 *
 * <#Paragraphs Of Explanation#>
 *
 * @param [in] fixedHeaderDictionary The FixedHeader dictionary
 *
 * @return positive The Version
 * @return -1 The field does not exist
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
int ccnxCodecSchemaV1FixedHeaderDecoder_GetVersion(CCNxTlvDictionary *packetDictionary);

/**
 * A convenience function to return the PacketType
 *
 * <#Paragraphs Of Explanation#>
 *
 * @param [in] fixedHeaderDictionary The FixedHeader dictionary
 *
 * @return positive The PacketType
 * @return -1 The field does not exist
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
int  ccnxCodecSchemaV1FixedHeaderDecoder_GetPacketType(CCNxTlvDictionary *packetDictionary);

/**
 * A convenience function to return the PacketLength
 *
 * The PacketLength is measured from byte 0 to the end of the packet
 *
 * @param [in] fixedHeaderDictionary The FixedHeader dictionary
 *
 * @return positive The packet length (in host byte order)
 * @return -1 The field does not exist
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
int ccnxCodecSchemaV1FixedHeaderDecoder_GetPacketLength(CCNxTlvDictionary *packetDictionary);

/**
 * A convenience function to return the HeaderLength
 *
 * In a version 1 packet, the header length includes the fixed header.  It is measured from
 * byte 0 to the end of the hop-by-hop headers.
 *
 * @param [in] fixedHeaderDictionary The FixedHeader dictionary
 *
 * @return positive The header length
 * @return -1 The field does not exist
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
int ccnxCodecSchemaV1FixedHeaderDecoder_GetHeaderLength(CCNxTlvDictionary *packetDictionary);

/**
 * Returns the bytes of the optional headers
 *
 * Computes ccnxCodecSchemaV1FixedHeaderDecoder_GetHeaderLength() - sizeof(fixedHeader)
 *
 * @param [in] fixedHeaderDictionary The FixedHeader dictionary
 *
 * @retval non-negative The length of the optional headers
 * @retval negative An error
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
int ccnxCodecSchemaV1FixedHeaderDecoder_GetOptionalHeaderLength(CCNxTlvDictionary *packetDictionary);


/**
 * A convenience function to return the ReturnCode of an Interest or InterestReturn
 *
 * @param [in] fixedHeaderDictionary The FixedHeader dictionary
 *
 * @return positive The Return Code
 * @return -1 The field does not exist
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
int ccnxCodecSchemaV1FixedHeaderDecoder_GetReturnCode(CCNxTlvDictionary *packetDictionary);

/**
 * A convenience function to return the header Flags
 *
 * @param [in] fixedHeaderDictionary The FixedHeader dictionary
 *
 * @return positive The flags
 * @return -1 The field does not exist
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
int ccnxCodecSchemaV1FixedHeaderDecoder_GetFlags(CCNxTlvDictionary *packetDictionary);

#endif // Libccnx_ccnxCodecSchemaV1_FixedHeaderDecoder_h
