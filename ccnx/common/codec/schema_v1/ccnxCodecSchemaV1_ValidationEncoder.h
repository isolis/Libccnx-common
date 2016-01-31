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
 * @file ccnxCodecSchemaV1_ValidationEncoder.h
 * @brief Encode the Validation Algorithm and Payload
 *
 * Encodes the validation algorithm and payload from the dictionary.  Optionally computes
 * a signature if one is not specified in the dictionary and the encoder has a signer.
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2014-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef __CCNx_Common__ccnxCodecSchemaV1_ValidationEncoder__
#define __CCNx_Common__ccnxCodecSchemaV1_ValidationEncoder__

#include <ccnx/common/internal/ccnx_TlvDictionary.h>
#include <ccnx/common/codec/ccnxCodec_TlvEncoder.h>

/**
 * Appends the Validation Algorithm to the packet encoder
 *
 * If the dictionary has a CryptoSuite specified, we will create a ValidationAlgorithm section
 * and fill it in as per the CryptoSuite and supplied validation algorithm arguments, such as
 * a KeyId, KeyName, Cert, etc.  For most signatures, only the KeyId is mandatory, the other
 * fields will only be specified if the user put something in the dictionary.
 *
 * the caller is responsible for writing the ValidationAlgorithm TL container.
 *
 * @param [in] encoder An allocated encoder to append to
 * @param [in] packetDictionary The dictionary containing the optional headers
 *
 * @return non-negative Total bytes appended to encoder
 * @return -1 An error
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
ssize_t ccnxCodecSchemaV1ValidationEncoder_EncodeAlg(CCNxCodecTlvEncoder *encoder, CCNxTlvDictionary *packetDictionary);

/**
 * Appends the Validation Payload to the packet encoder
 *
 * This will append the Valdiation Payload from the dictionary, or if it is missing and the
 * encoder has a signer, will create a signature.
 *
 * the caller is responsible for writing the ValidationPayload TL container.
 *
 * To create the signature, the caller must have used ccnxCodecTlvEncoder_MarkSignatureStart() and
 * ccnxCodecTlvEncoder_MarkSignatureEnd() functions to specify the byte locations of the start and
 * stop of the protected region.
 *
 * @param [in] encoder An allocated encoder to append to
 * @param [in] packetDictionary The dictionary containing the optional headers
 *
 * @return non-negative Total bytes appended to encoder
 * @return -1 An error
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
ssize_t ccnxCodecSchemaV1ValidationEncoder_EncodePayload(CCNxCodecTlvEncoder *encoder, CCNxTlvDictionary *packetDictionary);

#endif /* defined(__CCNx_Common__ccnxCodecSchemaV1_ValidationEncoder__) */
