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
 * @author Alan Walendowski, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#include <config.h>

#include <LongBow/runtime.h>

#include <ccnx/common/internal/ccnx_InterestInterface.h>

CCNxInterestInterface *
ccnxInterestInterface_GetInterface(const CCNxTlvDictionary *dictionary)
{
    assertTrue((ccnxTlvDictionary_IsInterest(dictionary) ||
                ccnxTlvDictionary_IsInterestReturn(dictionary)), "Expected an Interest or InterestReturn");

    CCNxInterestInterface *impl = (CCNxInterestInterface *) ccnxTlvDictionary_GetMessageInterface(dictionary);

    if (impl == NULL) {
        // If we're here, we need to update the interface pointer.
        // Figure out what the typeInterface should be, based on the attributes we know.
        int schemaVersion = ccnxTlvDictionary_GetSchemaVersion(dictionary);

        switch (schemaVersion) {
            case CCNxTlvDictionary_SchemaVersion_V1:
                impl = &CCNxInterestFacadeV1_Implementation;
                break;
            default:
                trapUnexpectedState("Unknown SchemaVersion encountered in ccnxInterestInterface_GetInterface()");
                break;
        }

        if (impl == NULL) {
            // The cast to (CCNxTlvDictionary *) is to break the const.
            ccnxTlvDictionary_SetMessageInterface((CCNxTlvDictionary *) dictionary, (CCNxMessageInterface *) impl);
        }
    }
    return impl;
}

