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
#include <parc/algol/parc_Buffer.h>
#include <parc/algol/parc_Memory.h>

#include <parc/algol/parc_RandomAccessFile.h>

#include <ccnx/common/ccnx_FileChunker.h>

CCNxChunkerInterface *CCNxFileChunkerAsBunker = &(CCNxChunkerInterface) {
    .ForwardIterator = (void *(*)(const void *))ccnxFileChunker_ForwardIterator,
    .ReverseIterator = (void *(*)(const void *))ccnxFileChunker_ReverseIterator,
    .Release = (void (*)(void **))ccnxFileChunker_Release
};

struct _ccnx_chunker_state {
    size_t chunkNumber;
    int direction;
    bool atEnd;
    size_t position;
    size_t nextChunkSize;
    size_t totalSize;
};

typedef struct _ccnx_chunker_state _ChunkerState;

struct ccnx_buffer_chunker {
    // State
    size_t chunkSize;

    // Container for the data to be parsed
    PARCFile *file;
    PARCRandomAccessFile *fhandle;

    // The current element of the iterator
    PARCBuffer *currentElement;
};

static void
_destroy(CCNxFileChunker **chunkerP)
{
    if ((*chunkerP)->fhandle != NULL) {
        parcRandomAccessFile_Release(&(*chunkerP)->fhandle);
    }

    if ((*chunkerP)->file != NULL) {
        parcFile_Release(&(*chunkerP)->file);
    }

    if ((*chunkerP)->currentElement != NULL) {
        parcBuffer_Release(&(*chunkerP)->currentElement);
    }
}

static void *
_InitForward(CCNxFileChunker *chunker)
{
    _ChunkerState *state = parcMemory_Allocate(sizeof(_ChunkerState));

    state->chunkNumber = 0;
    state->direction = 0;
    state->position = 0;
    state->atEnd = false;
    state->totalSize = parcFile_GetFileSize(chunker->file);

    if (state->totalSize < chunker->chunkSize) {
        state->position = 0;
        state->nextChunkSize = state->totalSize;
    } else {
        state->position = 0;
        state->nextChunkSize = chunker->chunkSize;
    }

    return state;
}

static void *
_InitReverse(CCNxFileChunker *chunker)
{
    _ChunkerState *state = parcMemory_Allocate(sizeof(_ChunkerState));

    state->chunkNumber = 0;
    state->direction = 1;
    state->atEnd = false;
    state->totalSize = parcFile_GetFileSize(chunker->file);

    if (state->totalSize < chunker->chunkSize) {
        state->position = 0;
        state->nextChunkSize = state->totalSize;
    } else {
        state->position = state->totalSize - chunker->chunkSize;
        state->nextChunkSize = chunker->chunkSize;
    }

    return state;
}

static bool
_ccnxChunker_HasNext(CCNxFileChunker *chunker, void *voidstate)
{
    _ChunkerState *state = (_ChunkerState *) voidstate;
    return !state->atEnd;
}

static void
_advanceStateForward(CCNxFileChunker *chunker, _ChunkerState *state)
{
    state->position += state->nextChunkSize;
    size_t remaining = state->totalSize - state->position;

    if (remaining == 0) {
        state->atEnd = true;
    } else if (remaining > chunker->chunkSize) {
        state->nextChunkSize = chunker->chunkSize;
    } else {
        state->nextChunkSize = remaining;
    }
}

static void
_advanceStateBackward(CCNxFileChunker *chunker, _ChunkerState *state)
{
    // Previous chunk size
    size_t chunkSize = state->nextChunkSize;
    if (chunkSize != chunker->chunkSize || state->position == 0) {
        state->atEnd = true;
    } else {
        if (state->position < chunkSize) {
            state->nextChunkSize = state->position; // on next read, go to the current position
            state->position = 0; // we reached the beginning
        } else {
            state->position -= chunkSize;
        }
    }
}

static void
_advanceState(CCNxFileChunker *chunker, _ChunkerState *state)
{
    state->chunkNumber++;

    if (state->direction == 0) {
        _advanceStateForward(chunker, state);
    } else {
        _advanceStateBackward(chunker, state);
    }
}

static void *
_ccnxChunker_NextFromBuffer(CCNxFileChunker *chunker, _ChunkerState *state)
{
    size_t chunkSize = state->nextChunkSize;

    parcRandomAccessFile_Seek(chunker->fhandle, state->position, PARCRandomAccessFilePosition_Start);

    PARCBuffer *slice = parcBuffer_Allocate(chunkSize);
    parcRandomAccessFile_Read(chunker->fhandle, slice);
    slice = parcBuffer_Flip(slice);

    _advanceState(chunker, state);

    return slice;
}

static void *
_ccnxChunker_Next(CCNxFileChunker *chunker, void *state)
{
    PARCBuffer *buffer = _ccnxChunker_NextFromBuffer(chunker, state);

    if (chunker->currentElement != NULL) {
        parcBuffer_Release(&chunker->currentElement);
    }
    if (buffer != NULL) {
        chunker->currentElement = parcBuffer_Acquire(buffer);
    }

    return state;
}

static void
_ccnxChunker_RemoveAt(CCNxFileChunker *chunker, void **state)
{
    // pass
}

static void *
_ccnxChunker_GetElement(CCNxFileChunker *chunker, void *state)
{
    return chunker->currentElement;
}

static void
_ccnxChunker_Finish(CCNxFileChunker *chunker, void *state)
{
    _ChunkerState *thestate = (_ChunkerState *) state;
    parcMemory_Deallocate(&thestate);
}

static void
_ccnxChunker_AssertValid(const void *state)
{
    // pass
}

parcObject_ExtendPARCObject(CCNxFileChunker, _destroy, NULL, NULL, NULL, NULL, NULL, NULL);
parcObject_ImplementAcquire(ccnxFileChunker, CCNxFileChunker);
parcObject_ImplementRelease(ccnxFileChunker, CCNxFileChunker);

CCNxFileChunker *
ccnxFileChunker_Create(PARCFile *file, size_t chunkSize)
{
    CCNxFileChunker *chunker = parcObject_CreateInstance(CCNxFileChunker);

    if (chunker != NULL) {
        chunker->chunkSize = chunkSize;
        chunker->file = parcFile_Acquire(file);
        chunker->fhandle = parcRandomAccessFile_Open(chunker->file);
        chunker->currentElement = NULL;
    }

    return chunker;
}


PARCIterator *
ccnxFileChunker_ForwardIterator(const CCNxFileChunker *chunker)
{
    PARCIterator *iterator = parcIterator_Create((void *) chunker,
                                                 (void *(*)(PARCObject *))_InitForward,
                                                 (bool (*)(PARCObject *, void *))_ccnxChunker_HasNext,
                                                 (void *(*)(PARCObject *, void *))_ccnxChunker_Next,
                                                 (void (*)(PARCObject *, void **))_ccnxChunker_RemoveAt,
                                                 (void *(*)(PARCObject *, void *))_ccnxChunker_GetElement,
                                                 (void (*)(PARCObject *, void *))_ccnxChunker_Finish,
                                                 (void (*)(const void *))_ccnxChunker_AssertValid);

    return iterator;
}

PARCIterator *
ccnxFileChunker_ReverseIterator(const CCNxFileChunker *chunker)
{
    PARCIterator *iterator = parcIterator_Create((void *) chunker,
                                                 (void *(*)(PARCObject *))_InitReverse,
                                                 (bool (*)(PARCObject *, void *))_ccnxChunker_HasNext,
                                                 (void *(*)(PARCObject *, void *))_ccnxChunker_Next,
                                                 (void (*)(PARCObject *, void **))_ccnxChunker_RemoveAt,
                                                 (void *(*)(PARCObject *, void *))_ccnxChunker_GetElement,
                                                 (void (*)(PARCObject *, void *))_ccnxChunker_Finish,
                                                 (void (*)(const void *))_ccnxChunker_AssertValid);

    return iterator;
}
