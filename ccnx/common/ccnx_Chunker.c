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
 * @author Christopher Wood, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#include <config.h>

#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include <parc/algol/parc_Object.h>
#include <parc/algol/parc_Memory.h>

#include <ccnx/common/ccnx_Chunker.h>

struct ccnx_chunker {
    void *instance;
    const CCNxChunkerInterface *interface;
};

static void
_destroy(CCNxChunker **chunkerP)
{
    (*chunkerP)->interface->Release(&(*chunkerP)->instance);
}


parcObject_ExtendPARCObject(CCNxChunker, _destroy, NULL, NULL, NULL, NULL, NULL, NULL);
parcObject_ImplementAcquire(ccnxChunker, CCNxChunker);
parcObject_ImplementRelease(ccnxChunker, CCNxChunker);

CCNxChunker *
ccnxChunker_Create(void *instance, CCNxChunkerInterface *interface)
{
    CCNxChunker *chunker = parcObject_CreateInstance(CCNxChunker);

    if (chunker != NULL) {
        chunker->instance = instance;
        chunker->interface = interface;
    }

    return chunker;
}

PARCIterator *
ccnxChunker_ForwardIterator(const CCNxChunker *chunker)
{
    return (chunker->interface)->ForwardIterator(chunker->instance);
}

PARCIterator *
ccnxChunker_ReverseIterator(const CCNxChunker *chunker)
{
    return (chunker->interface)->ReverseIterator(chunker->instance);
}
