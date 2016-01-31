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
 * This is from the version 0 codec.  All the test vectors in this directory (e.g. interest_nameA.h)
 * are encoded using these constants.  These are no longer used for any functional code, only to interpret the test vectors.
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef Libccnx_v1_InterestSchema_h
#define Libccnx_v1_InterestSchema_h

#include <ccnx/common/codec/testdata/tlv_Schema.h>

// -----------------------------------------------------
// these are the array indicies used to store the TlvExtent for the item
typedef enum {
    V1_MANIFEST_INT_INTEREST = 0, // start of Interest body to end

    V1_MANIFEST_INT_NAME     = 1,
    V1_MANIFEST_INT_KEYID    = 2,
    V1_MANIFEST_INT_OBJHASH  = 3,
    V1_MANIFEST_INT_PAYLOAD  = 4,
    V1_MANIFEST_INT_IPIDM    = 5,

    V1_MANIFEST_INT_ValidationAlg  = 6,     // start of validation algorithm
    V1_MANIFEST_INT_ValidationPayload = 7,  // start of validation payload

    V1_MANIFEST_INT_BODYEND  = 7
} ScheamV1ManifestInterestBody;

typedef enum {
    V1_MANIFEST_INT_OPTHEAD  = 0,  // the start of the optional headers
    V1_MANIFEST_INT_LIFETIME = 1,
    V1_MANIFEST_INT_E2EFRAG  = 2,
    V1_MANIFEST_INT_HEADEND  = 3,
} ScheamV1ManifestInterestHeaders;


#define T_INTEREST 0x0001

#endif // Libccnx_tlv_InterestSchema_h
