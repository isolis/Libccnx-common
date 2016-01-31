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
 * This is from the version 1 codec.  All the test vectors in this directory (e.g. interest_nameA.h)
 * are encoded using these constants.  These are no longer used for any functional code, only to interpret the test vectors.
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef Libccnx_v1_ContentObjectSchema_h
#define Libccnx_v1_ContentObjectSchema_h

#include <ccnx/common/codec/testdata/tlv_Schema.h>

#define T_CONTENTOBJECT 0x0002

// these are the array indicies used to store the TlvExtent for the item
typedef enum {
    // top level entities
    V1_MANIFEST_OBJ_NAME            = 0,
    V1_MANIFEST_OBJ_CONTENTOBJECT   = 1,  // the top container
    V1_MANIFEST_OBJ_NAMEAUTH        = 2,
    V1_MANIFEST_OBJ_PAYLOADTYPE     = 3,
    V1_MANIFEST_OBJ_PAYLOAD         = 4,
    V1_MANIFEST_OBJ_SIGBITS         = 5,

    // inside the name authenticator
    V1_MANIFEST_OBJ_KEYID           = 6,
    V1_MANIFEST_OBJ_CRYPTO_SUITE    = 7,
    V1_MANIFEST_OBJ_KEY             = 8,
    V1_MANIFEST_OBJ_CERT            = 9,
    V1_MANIFEST_OBJ_KEYNAME         = 10,
    V1_MANIFEST_OBJ_KEYNAME_NAME    = 11,
    V1_MANIFEST_OBJ_KEYNAME_OBJHASH = 12,

    // inside the protocol information
    V1_MANIFEST_OBJ_METADATA        = 13,

    // inside metadata
    V1_MANIFEST_OBJ_OBJ_TYPE        = 14,
    V1_MANIFEST_OBJ_CREATE_TIME     = 15,
    V1_MANIFEST_OBJ_EXPIRY_TIME     = 16,

    // inside signature block
    V1_MANIFEST_OBJ_ValidationPayload = 17,
    V1_MANIFEST_OBJ_ENDSEGMENT      = 18,
    V1_MANIFEST_OBJ_PUBKEY          = 19,

    V1_MANIFEST_OBJ_ValidationAlg   = 20,
    V1_MANIFEST_OBJ_SigningTime     = 21,
    V1_MANIFEST_OBJ_BODYEND         = 22
} SchemaV1ManifestContentObjectBody;

typedef enum {
    V1_MANIFEST_OBJ_OPTHEAD     = 0,
    V1_MANIFEST_OBJ_E2EFRAG     = 2,
    V1_MANIFEST_OBJ_FIXEDHEADER = 3,
    V1_MANIFEST_OBJ_RecommendedCacheTime = 4,
    V1_MANIFEST_OBJ_HEADEND     = 5
} SchemaV1ManifestContentObjectHeaders;

#endif // Libccnx_tlv_ContentObjectSchema_h
