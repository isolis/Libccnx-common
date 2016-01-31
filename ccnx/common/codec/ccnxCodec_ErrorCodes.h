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
 * @file ccnxCodec_ErrorCodes.h
 * @brief The error codes used by CCNxCodecError.
 *
 * The codecs in schema_v0 and schema_v1 use these error codes to report problems inside
 * CCNxCodec_TlvEncoder and CCNxCodec_TlvDecoder.
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef CCNx_Common_ccnxCodec_ErrorCodes_h
#define CCNx_Common_ccnxCodec_ErrorCodes_h

/**
 * @typedef <#CCNBHeaderType#>
 * @abstract <#Abstract#>
 * @constant <#name#> <#description#>
 * @discussion <#Discussion#>
 */
typedef enum ccnx_codec_error_codes {
    TLV_ERR_NO_ERROR,
    TLV_ERR_VERSION,
    TLV_ERR_PACKETTYPE,
    TLV_ERR_BEYOND_PACKET_END,
    TLV_ERR_TOO_LONG,
    TLV_ERR_NOT_FIXED_SIZE,
    TLV_ERR_DUPLICATE_FIELD,
    TLV_ERR_EMPTY_SPACE,

    // generic error for decoding error
    TLV_ERR_DECODE,

    TLV_ERR_PACKETLENGTH_TOO_SHORT,
    TLV_ERR_HEADERLENGTH_TOO_SHORT,
    TLV_ERR_PACKETLENGTHSHORTER,


    // errors for missing mandatory fields
    TLV_MISSING_MANDATORY,
} CCNxCodecErrorCodes;
#endif
