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
 * @file ccnx_Chunker.h
 * @ingroup ContentObject
 * @brief A Chunker is an object that breaks up a large piece of data from a `PARCBuffer`
 *        or a file and provides an iterator to walk over the chunks in sequential order.
 *
 * @author Christopher A. Wood, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef libccnx_ccnx_Chunker_h
#define libccnx_ccnx_Chunker_h

#include <config.h>

#include <parc/algol/parc_Object.h>
#include <parc/algol/parc_Iterator.h>

struct ccnx_chunker;
/**
 * @typedef CCNxChunker
 * @brief The CCNx Chunker
 */
typedef struct ccnx_chunker CCNxChunker;

typedef struct ccnx_chunker_interface {
    /**
     * @see ccnxChunker_ForwardIterator
     */
    void *(*ForwardIterator)(const void *original);

    /**
     * @see ccnxChunker_ReverseIterator
     */
    void *(*ReverseIterator)(const void *original);

    /**
     * @see ccnxChunker_Release
     */
    void (*Release)(void **originalP);
} CCNxChunkerInterface;

/**
 * Create a new chunker from the given concrete instance.
 *
 * @param [in] instance A `CCNxChunker` instance.
 * @param [in] interface The interface implementation of the chunker.
 *
 * @retval CCNxChunker A newly allocated `CCNxChunker`
 * @retval NULL An error occurred.
 *
 * Example
 * @code
 * {
 *     PARCBuffer *dataToChunk = ...
 *     CCNxChunkerBuffer *bufferChunker = ccnxBufferChunker_Create(dataToChunk, 32);
 *     CCNxChunker *chunker = ccnxChunker_Create(bufferCunker, &CCNxBufferChunkerAsChunker);
 * }
 */
CCNxChunker *ccnxChunker_Create(void *instance, CCNxChunkerInterface *interface);

/**
 * Create a new chunker to segment data contained in a file.
 *
 * @param [in] fileName The name of a file from which to read.
 * @param [in] chunkSize The size per chunk.
 *
 * @retval CCNxChunker A newly allocated `CCNxChunker`
 * @retval NULL An error occurred.
 *
 * Example
 * @code
 * {
 *     char *bigFileName = "big_file.bin";
 *     CCNxChunker *chunker = ccnxChunker_CreateFromBuffer(bigFileName, 32);
 * }
 */
//CCNxChunker *ccnxChunker_CreateFromFile(char *fileName, size_t maxDataSize);

/**
 * Increase the number of references to a `CCNxChunker` instance.
 *
 * Note that new `CCNxChunker` is not created,
 * only that the given `CCNxChunker` reference count is incremented.
 * Discard the reference by invoking {@link ccnxChunker_Release}.
 *
 * @param [in] chunker A pointer to the original `CCNxChunker`.
 * @return The value of the input parameter @p chunker.
 *
 * Example:
 * @code
 * {
 *     CCNxChunker *original = ...
 *
 *     CCNxChunker *reference = ccnxChunker_Acquire(original);
 *
 *     ccnxChunker_Release(&original);
 *     ccnxChunker_Release(&reference);
 * }
 * @endcode
 *
 * @see ccnxChunker_Release
 */
CCNxChunker *ccnxChunker_Acquire(const CCNxChunker *chunker);

/**
 * Release a previously acquired reference to the specified instance,
 * decrementing the reference count for the instance.
 *
 * The pointer to the instance is set to NULL as a side-effect of this function.
 *
 * If the invocation causes the last reference to the instance to be released,
 * the instance is deallocated and the instance's implementation will perform
 * additional cleanup and release other privately held references.
 *
 * @param [in,out] chunkerP A pointer to a pointer to the instance to release.
 *
 *
 * Example:
 * @code
 * {
 *     ...
 *
 *     CCNxChunker *chunker = ccnxChunker_Acquire(instance);
 *
 *     ccnxChunker_Release(&chunker);
 * }
 * @endcode
 */
void ccnxChunker_Release(CCNxChunker **chunkerP);

/**
 * Determine if two `CCNxChunker` instances are equal.
 *
 * The following equivalence relations on non-null `CCNxChunker` instances are maintained:
 *
 *  * It is reflexive: for any non-null reference value x, `ccnxChunker_Equals(x, x)`
 *      must return true.
 *
 *  * It is symmetric: for any non-null reference values x and y,
 *    `ccnxChunker_Equals(x, y)` must return true if and only if
 *        `ccnxChunker_Equals(y, x)` returns true.
 *
 *  * It is transitive: for any non-null reference values x, y, and z, if
 *        `ccnxChunker_Equals(x, y)` returns true and
 *        `ccnxChunker_Equals(y, z)` returns true,
 *        then  `ccnxChunker_Equals(x, z)` must return true.
 *
 *  * It is consistent: for any non-null reference values x and y, multiple
 *      invocations of `ccnxChunker_Equals(x, y)` consistently return true or
 *      consistently return false.
 *
 *  * For any non-null reference value x, `ccnxChunker_Equals(x, NULL)` must
 *      return false.
 *
 * @param chunkerA A pointer to a `CCNxChunker` instance.
 * @param chunkerB A pointer to a `CCNxChunker` instance.
 * @return true if the two `CCNxChunker` instances are equal.
 *
 * Example:
 * @code
 * {
 *     PARCBuffer *dataToChunk = ...
 *     CCNxChunker *chunkerA = ...
 *     CCNxChunker *chunkerB = ...
 *
 *     bool equals = ccnxChunker_Equals(chunkerA, chunkerB);
 * }
 * @endcode
 */
bool ccnxChunker_Equals(const CCNxChunker *chunkerA, const CCNxChunker *chunkerB);

/**
 * Return an iterator to traverse the chunks of the underlying data in sequential order.
 *
 * This function can only be called once per chunker instance since the iterator
 * will mutate internal state of the chunker.
 *
 * @param [in] chunker A `CCNxChunker` instance.
 *
 * @return a `PARCIterator` that traverses the chunks of the underlying data.
 *
 * Example
 * @code
 * {
 *     PARCBuffer *dataToChunk = ...
 *     CCNxBufferChunker *chunker = ...
 *
 *     PARCIterator *itr = ccnxChunker_ForwardIterator(chunker);
 *
 *     // use the iterator to traverse the chunker
 * }
 * @endcode
 */
PARCIterator *ccnxChunker_ForwardIterator(const CCNxChunker *chunker);

/**
 * Return an iterator to traverse the chunks of the underlying data in sequential order.
 *
 * This function can only be called once per chunker instance since the iterator
 * will mutate internal state of the chunker.
 *
 * @param [in] chunker A `CCNxChunker` instance.
 *
 * @return a `PARCIterator` that traverses the chunks of the underlying data.
 *
 * Example
 * @code
 * {
 *     PARCBuffer *dataToChunk = ...
 *     CCNxChunker *chunker = ...
 *
 *     PARCIterator *itr = ccnxChunker_ReverseIterator(chunker);
 *
 *     // use the iterator to traverse the chunker
 * }
 * @endcode
 */
PARCIterator *ccnxChunker_ReverseIterator(const CCNxChunker *chunker);
#endif // libccnx_ccnx_Chunker_h
