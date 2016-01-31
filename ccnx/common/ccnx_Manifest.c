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
 * @author Christopher A. Wood, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#include <config.h>
#include <stdio.h>
#include <string.h>

#include <LongBow/runtime.h>

#include <parc/algol/parc_Object.h>

#include <ccnx/common/ccnx_Manifest.h>

struct ccnx_manifest {
    CCNxLink *nameLink;
    CCNxManifestSection *metadataSection;
    CCNxManifestSection *payloadSection;
    PARCSignature *signature;
};

static void
_ccnxManifest_FinalRelease(CCNxManifest **manifestP)
{
    parcSignature_Release(&(*manifestP)->signature);
    ccnxLink_Release(&(*manifestP)->nameLink);
    if ((*manifestP)->metadataSection != NULL) {
        ccnxManifestSection_Release(&(*manifestP)->metadataSection);
    }
    if ((*manifestP)->payloadSection != NULL) {
        ccnxManifestSection_Release(&(*manifestP)->payloadSection);
    }
}

parcObject_ExtendPARCObject(CCNxManifest, _ccnxManifest_FinalRelease, NULL,
                            ccnxManifest_ToString, ccnxManifest_Equals, NULL, NULL, NULL);

parcObject_ImplementAcquire(ccnxManifest, CCNxManifest);

parcObject_ImplementRelease(ccnxManifest, CCNxManifest);

CCNxManifest *
ccnxManifest_Create(PARCSignature *signature, CCNxLink *nameLink, CCNxManifestSection *metadata,
                    CCNxManifestSection *payload)
{
    CCNxManifest *manifest = parcObject_CreateInstance(CCNxManifest);

    if (manifest != NULL) {
        manifest->signature = parcSignature_Acquire(signature);
        manifest->nameLink = ccnxLink_Acquire(nameLink);

        if (metadata != NULL) {
            manifest->metadataSection = ccnxManifestSection_Acquire(metadata);
        } else {
            manifest->metadataSection = NULL;
        }

        if (payload != NULL) {
            manifest->payloadSection = ccnxManifestSection_Acquire(payload);
        } else {
            manifest->payloadSection = NULL;
        }
    }

    return manifest;
}

CCNxManifestSection *
ccnxManifest_GetMetadataSection(const CCNxManifest *manifest)
{
    return manifest->metadataSection;
}

CCNxManifestSection *
ccnxManifest_GetPayloadSection(const CCNxManifest *manifest)
{
    return manifest->payloadSection;
}

CCNxLink *
ccnxManifest_GetNameLink(const CCNxManifest *manifest)
{
    return manifest->nameLink;
}

PARCSignature *
ccnxManifest_GetSignature(const CCNxManifest *manifest)
{
    return manifest->signature;
}

bool
ccnxManifest_Equals(const CCNxManifest *objectA, const CCNxManifest *objectB)
{
    if (objectA == objectB) {
        return true;
    }
    if (objectA == NULL || objectB == NULL) {
        return false;
    }
    if (parcSignature_Equals(objectA->signature, objectB->signature)) {
        if (ccnxLink_Equals(objectA->nameLink, objectB->nameLink)) {
            if (ccnxManifestSection_Equals(objectA->metadataSection, objectB->metadataSection)) {
                if (ccnxManifestSection_Equals(objectA->payloadSection, objectB->payloadSection)) {
                    return true;
                }
            }
        }
    }
    return false;
}

char *
ccnxManifest_ToString(const CCNxManifest *manifest)
{
    char *nameString = ccnxLink_ToString(manifest->nameLink);
    char *signatureString = parcSignature_ToString(manifest->signature);

    char *metadataString = "NULL";
    bool nullMetadata = true;
    if (manifest->metadataSection != NULL) {
        metadataString = ccnxManifestSection_ToString(manifest->metadataSection);
        nullMetadata = false;
    }

    char *payloadString = "NULL";
    bool nullPayload = true;
    if (manifest->payloadSection != NULL) {
        payloadString = ccnxManifestSection_ToString(manifest->payloadSection);
        nullPayload = false;
    }

    char *string;
    int failure = asprintf(&string, "CCNxManifest { .name=\"%s\", .signature=\"%s\", .metadataSection=\"%s\", .payloadSection=\"%s\"}",
                           nameString,
                           signatureString,
                           metadataString,
                           payloadString);
    assertTrue(failure > -1, "Error asprintf");

    parcMemory_Deallocate((void **) &nameString);
    parcMemory_Deallocate((void **) &signatureString);
    if (!nullMetadata) {
        parcMemory_Deallocate((void **) &metadataString);
    }
    if (!nullPayload) {
        parcMemory_Deallocate((void **) &payloadString);
    }

    char *result = parcMemory_StringDuplicate(string, strlen(string));
    free(string);

    return result;
}

CCNxManifest *
ccnxManifest_Verify(const CCNxManifest *manifest)
{
    ccnxManifest_AssertValid(manifest);
    return (CCNxManifest *) manifest;
}

void
ccnxManifest_AssertValid(const CCNxManifest *manifest)
{
    assertNotNull(manifest, "Parameter must be a non-null CCNxManifest pointer.");
    assertNotNull(manifest->signature, "PARCSignature signature cannot be NULL.");
    assertNotNull(manifest->nameLink, "CCNxLink name cannot be NULL.");
    ccnxLink_AssertValid(manifest->nameLink);
}
