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
#include <LongBow/runtime.h>

#include <ccnx/common/internal/ccnx_ValidationFacadeV1.h>
#include <ccnx/common/codec/schema_v1/ccnxCodecSchemaV1_TlvDictionary.h>

// ========================================================================================

/**
 * Sets the Validation algorithm to EC-SECP-256K1
 *
 * Sets the validation algorithm to be Elliptical Curve with SECP-256K1 parameters.  Optionally includes
 * a KeyId and KeyLocator with the message.
 *
 * @param [in] message The message dictionary
 * @param [in] keyid (Optional) The KEYID to include the the message
 * @param [in] keyLocator (Optional) The KEY LOCATOR to include in the message
 *
 * @return <#value#> <#explanation#>
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
bool
ccnxValidationEcSecp256K1_Set(CCNxTlvDictionary *message, const PARCBuffer *keyid, const CCNxKeyLocator *keyLocator)
{
    bool success = true;
    switch (ccnxTlvDictionary_GetSchemaVersion(message)) {
        case CCNxTlvDictionary_SchemaVersion_V1: {
            success &= ccnxTlvDictionary_PutInteger(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_CRYPTO_SUITE, PARCCryptoSuite_EC_SECP_256K1);

            if (keyid) {
                success &= ccnxTlvDictionary_PutBuffer(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_KEYID, keyid);
            }

            success &= ccnxValidationFacadeV1_SetKeyLocator(message, (CCNxKeyLocator *) keyLocator); // un-consting

            break;
        }

        default:
            trapIllegalValue(message, "Unknown schema version: %d", ccnxTlvDictionary_GetSchemaVersion(message));
    }
    return success;
}

bool
ccnxValidationEcSecp256K1_Test(const CCNxTlvDictionary *message)
{
    if (ccnxTlvDictionary_IsValueInteger(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_CRYPTO_SUITE)) {
        uint64_t cryptosuite = ccnxTlvDictionary_GetInteger(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_CRYPTO_SUITE);
        return (cryptosuite == PARCCryptoSuite_EC_SECP_256K1);
    }
    return false;
}
