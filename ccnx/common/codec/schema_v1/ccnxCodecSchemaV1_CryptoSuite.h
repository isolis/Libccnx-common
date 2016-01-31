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
 * @file ccnxCodecSchemaV1_CryptoSuite.h
 * @brief Translates between PARC CryptoSuite values and the wire encoding
 *
 * <#Detailed Description#>
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#include <stdbool.h>
#include <parc/security/parc_CryptoHashType.h>
#include <parc/security/parc_SigningAlgorithm.h>
#include <ccnx/common/codec/schema_v1/ccnxCodecSchemaV1_TlvDictionary.h>

/**
 * Converts a PARC Crypto Suite to its TLV value
 *
 * Looks up the PARC cryptosuite value and returns the corresponding TLV wire format value.
 * If no match is found, returns false and outputSuite is not modified.
 *
 *
 * @param [in] parcSuite The PARC cryptosuite
 * @param [out] outputValue The wire encoding equivalent
 *
 * @retval true if supported suite and outputValue set.
 * @retval false if not supported.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
bool ccnxCodecSchemaV1CryptoSuite_ParcToTlv(PARCCryptoSuite parcSuite, CCNxCodecSchemaV1TlvDictionary_CryptoSuite *outputValue);

/**
 * Converts a wire format cryptosuite value to the PARC cryptosuite
 *
 * Looks up the TLV wire format value and returns the corresponding PARC cryptosuite.
 * If no match is found, returns false and outputSuite is not modified.
 *
 * @param [in] tlvValue The wire format value
 * @param [out] outputValue The PARC equivalent
 *
 * @return true if match found and parcSuite set.
 * @return false if no match found.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
bool ccnxCodecSchemaV1CryptoSuite_TlvToParc(CCNxCodecSchemaV1TlvDictionary_CryptoSuite tlvValue, PARCCryptoSuite *outputSuite);

/**
 * Lookup a signing algorithm and hash type and convert to a wire format value
 *
 * Based on a PARCSigner's algorithm and hash type, find the corresponding wire format crypto suite.
 *
 * @param [in] signAlgorithm The signing algorithm
 * @param [in] hashType The hash used by the signing algorithm
 * @param [out] outputValue The wire format value
 *
 * @retval true if supported suite and outputValue set.
 * @retval false if not supported.
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
bool ccnxCodecSchemaV1CryptoSuite_SignAndHashToTlv(PARCSigningAlgorithm signAlgorithm, PARCCryptoHashType hashType, CCNxCodecSchemaV1TlvDictionary_CryptoSuite *outputValue);
