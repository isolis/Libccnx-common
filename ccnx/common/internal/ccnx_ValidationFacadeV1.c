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
#include <stdio.h>
#include <LongBow/runtime.h>

#include <ccnx/common/internal/ccnx_ValidationFacadeV1.h>
#include <ccnx/common/codec/schema_v1/ccnxCodecSchemaV1_TlvDictionary.h>

static void
_assertInvariants(const CCNxTlvDictionary *message)
{
    assertNotNull(message, "Parameter message must be non-null");
}

PARCBuffer *
ccnxValidationFacadeV1_GetKeyId(const CCNxTlvDictionary *message)
{
    _assertInvariants(message);
    return ccnxTlvDictionary_GetBuffer(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_KEYID);
}

CCNxLink *
ccnxValidationFacadeV1_GetKeyName(const CCNxTlvDictionary *message)
{
    _assertInvariants(message);
    CCNxLink *link = NULL;
    CCNxName *name = ccnxTlvDictionary_GetName(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_KEYNAME_NAME);
    if (name) {
        PARCBuffer *keyid = ccnxTlvDictionary_GetBuffer(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_KEYNAME_KEYID);
        PARCBuffer *hash = ccnxTlvDictionary_GetBuffer(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_KEYNAME_OBJHASH);

        link = ccnxLink_Create(name, keyid, hash);
    }
    return link;
}

PARCBuffer *
ccnxValidationFacadeV1_GetPublicKey(const CCNxTlvDictionary *message)
{
    _assertInvariants(message);
    return ccnxTlvDictionary_GetBuffer(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_KEY);
}

PARCBuffer *
ccnxValidationFacadeV1_GetCertificate(const CCNxTlvDictionary *message)
{
    _assertInvariants(message);
    return ccnxTlvDictionary_GetBuffer(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_CERT);
}

PARCBuffer *
ccnxValidationFacadeV1_GetPayload(const CCNxTlvDictionary *message)
{
    _assertInvariants(message);
    return ccnxTlvDictionary_GetBuffer(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_PAYLOAD);
}

bool
ccnxValidationFacadeV1_HasCryptoSuite(const CCNxTlvDictionary *message)
{
    bool hasCryptoSuite = false;
    _assertInvariants(message);
    if (ccnxTlvDictionary_IsValueInteger(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_CRYPTO_SUITE)) {
        hasCryptoSuite = true;
    }
    return hasCryptoSuite;
}

PARCCryptoSuite
ccnxValidationFacadeV1_GetCryptoSuite(const CCNxTlvDictionary *message)
{
    if (ccnxValidationFacadeV1_HasCryptoSuite(message)) {
        return (PARCCryptoSuite) ccnxTlvDictionary_GetInteger(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_CRYPTO_SUITE);
    }

    trapUnexpectedState("Dictionary does not have a CryptoSuite set");
}

bool
ccnxValidationFacadeV1_HasSigningTime(const CCNxTlvDictionary *message)
{
    bool hasSigningTime = false;
    _assertInvariants(message);
    if (ccnxTlvDictionary_IsValueInteger(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_SIGNTIME)) {
        hasSigningTime = true;
    }
    return hasSigningTime;
}

uint64_t
ccnxValidationFacadeV1_GetSigningTime(const CCNxTlvDictionary *message)
{
    if (ccnxValidationFacadeV1_HasSigningTime(message)) {
        return ccnxTlvDictionary_GetInteger(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_SIGNTIME);
    }

    trapUnexpectedState("Dictionary does not have a CryptoSuite set");
}

// ===========================================================
// Setters

bool
ccnxValidationFacadeV1_SetKeyId(CCNxTlvDictionary *message, const PARCBuffer *keyid)
{
    _assertInvariants(message);
    return ccnxTlvDictionary_PutBuffer(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_KEYID, keyid);
}

bool
ccnxValidationFacadeV1_SetKeyName(CCNxTlvDictionary *message, const CCNxLink *keyNameLink)
{
    _assertInvariants(message);
    const CCNxName *name = ccnxLink_GetName(keyNameLink);
    bool success = ccnxTlvDictionary_PutName(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_KEYNAME_NAME, name);
    if (success) {
        PARCBuffer *keyid = ccnxLink_GetKeyID(keyNameLink);
        if (keyid) {
            success = ccnxTlvDictionary_PutBuffer(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_KEYNAME_KEYID, keyid);
        }

        if (success) {
            PARCBuffer *hash = ccnxLink_GetContentObjectHash(keyNameLink);
            success = ccnxTlvDictionary_PutBuffer(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_KEYNAME_OBJHASH, hash);
        }
    }
    return success;
}

bool
ccnxValidationFacadeV1_SetKeyLocator(CCNxTlvDictionary *message, CCNxKeyLocator *keyLocator)
{
    bool success = true;
    if (keyLocator) {
        if (ccnxKeyLocator_IsKey(keyLocator)) {
            PARCKey *key = ccnxKeyLocator_GetKey(keyLocator);
            PARCBuffer *keybuffer = parcKey_GetKey(key);
            success &= ccnxTlvDictionary_PutBuffer(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_KEY, keybuffer);
        } else if (ccnxKeyLocator_IsKeyLink(keyLocator)) {
            CCNxLink *link = ccnxKeyLocator_GetKeyLink(keyLocator);
            const CCNxName *name = ccnxLink_GetName(link);

            // Support KeyId and COH as part of the keyname, case 1012
            success &= ccnxTlvDictionary_PutName(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_KEYNAME_NAME, name);
        } else {
            trapUnrecoverableState("KeyLocator is not a known type");
        }
    }
    return success;
}

bool
ccnxValidationFacadeV1_SetPublicKey(CCNxTlvDictionary *message, const PARCBuffer *derEncodedKey)
{
    _assertInvariants(message);
    return ccnxTlvDictionary_PutBuffer(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_KEY, derEncodedKey);
}

bool
ccnxValidationFacadeV1_SetCertificate(CCNxTlvDictionary *message, const PARCBuffer *derEncodedCertificate)
{
    _assertInvariants(message);
    return ccnxTlvDictionary_PutBuffer(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_CERT, derEncodedCertificate);
}

bool
ccnxValidationFacadeV1_SetCryptoSuite(CCNxTlvDictionary *message, PARCCryptoSuite suite)
{
    _assertInvariants(message);
    return ccnxTlvDictionary_PutInteger(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_CRYPTO_SUITE, suite);
}

bool
ccnxValidationFacadeV1_SetSigningTime(CCNxTlvDictionary *message, uint64_t signingTime)
{
    _assertInvariants(message);
    return ccnxTlvDictionary_PutInteger(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_SIGNTIME, signingTime);
}

bool
ccnxValidationFacadeV1_SetPayload(CCNxTlvDictionary *message, const PARCBuffer *validationPayload)
{
    _assertInvariants(message);
    return ccnxTlvDictionary_PutBuffer(message, CCNxCodecSchemaV1TlvDictionary_ValidationFastArray_PAYLOAD, validationPayload);
}

