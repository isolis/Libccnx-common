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
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2014-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#include <config.h>

#include <ccnx/common/codec/schema_v1/ccnxCodecSchemaV1_CryptoSuite.h>


bool
ccnxCodecSchemaV1CryptoSuite_ParcToTlv(PARCCryptoSuite parcSuite, CCNxCodecSchemaV1TlvDictionary_CryptoSuite *outputValue)
{
    bool matchFound = false;
    switch (parcSuite) {
        case PARCCryptoSuite_RSA_SHA256:
            *outputValue = CCNxCodecSchemaV1TlvDictionary_CryptoSuite_RsaSha256;
            matchFound = true;
            break;

        case PARCCryptoSuite_DSA_SHA256:
            // not supported yet
            break;

        case PARCCryptoSuite_RSA_SHA512:
            // not supported yet
            break;

        case PARCCryptoSuite_HMAC_SHA256:
            *outputValue = CCNxCodecSchemaV1TlvDictionary_CryptoSuite_HmacSha256;
            matchFound = true;
            break;

        case PARCCryptoSuite_HMAC_SHA512:
            // not supported yet
            break;

        case PARCCryptoSuite_NULL_CRC32C:
            *outputValue = CCNxCodecSchemaV1TlvDictionary_CryptoSuite_CRC32C;
            matchFound = true;
            break;

        default:
            // unknown
            break;
    }
    return matchFound;
}

bool
ccnxCodecSchemaV1CryptoSuite_TlvToParc(CCNxCodecSchemaV1TlvDictionary_CryptoSuite tlvValue, PARCCryptoSuite *outputSuite)
{
    bool matchFound = false;
    switch (tlvValue) {
        case CCNxCodecSchemaV1TlvDictionary_CryptoSuite_RsaSha256:
            *outputSuite = PARCCryptoSuite_RSA_SHA256;
            matchFound = true;
            break;

        case CCNxCodecSchemaV1TlvDictionary_CryptoSuite_CRC32C:
            *outputSuite = PARCCryptoSuite_NULL_CRC32C;
            matchFound = true;
            break;

        case CCNxCodecSchemaV1TlvDictionary_CryptoSuite_HmacSha256:
            *outputSuite = PARCCryptoSuite_HMAC_SHA256;
            matchFound = true;
            break;

        case CCNxCodecSchemaV1TlvDictionary_CryptoSuite_EcSecp256K1:
            // not supported yet
            break;

        default:
            // unknown
            break;
    }
    return matchFound;
}

bool
ccnxCodecSchemaV1CryptoSuite_SignAndHashToTlv(PARCSigningAlgorithm signAlgorithm, PARCCryptoHashType hashType, CCNxCodecSchemaV1TlvDictionary_CryptoSuite *outputValue)
{
    bool matchFound = false;
    switch (signAlgorithm) {
        case PARCSigningAlgorithm_RSA: {
            switch (hashType) {
                case PARC_HASH_SHA256:
                    *outputValue = CCNxCodecSchemaV1TlvDictionary_CryptoSuite_RsaSha256;
                    matchFound = true;

                default:
                    break;
            }
            break;
        }

        case PARCSigningAlgorithm_HMAC: {
            switch (hashType) {
                case PARC_HASH_SHA256:
                    *outputValue = CCNxCodecSchemaV1TlvDictionary_CryptoSuite_HmacSha256;
                    matchFound = true;
                default:
                    break;
            }
            break;
        }

        case PARCSigningAlgortihm_NULL: {
            switch (hashType) {
                case PARC_HASH_CRC32C:
                    *outputValue = CCNxCodecSchemaV1TlvDictionary_CryptoSuite_CRC32C;
                    matchFound = true;
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
    return matchFound;
}

