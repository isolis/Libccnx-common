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
 * @file ccnx_BufferChunker.h
 * @ingroup ContentObject
 * @brief A BufferChunker is a chunker that segments a PARCBuffer.
 *
 * @author Christopher A. Wood, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef libccnx_ccnx_BufferChunker_h
#define libccnx_ccnx_BufferChunker_h

#include <config.h>

#include <ccnx/common/ccnx_Chunker.h>

struct ccnx_buffer_chunker;
/**
 * @typedef CCNxChunker
 * @brief The CCNx Chunker
 */
typedef struct ccnx_buffer_chunker CCNxBufferChunker;

/**
 * The mapping of a `PARCArrayList` to the generic `PARCList`.
 */
extern CCNxChunkerInterface *CCNxBufferChunkerAsChunker;

/**
 * Create a new chunker to segment data contained in a `PARCBuffer.`
 *
 * @param [in] data A `PARCBuffer` which contains the data.
 * @param [in] chunkSize The size per chunk.
 *
 * @retval CCNxChunker A newly allocated `CCNxChunker`
 * @retval NULL An error occurred.
 *
 * Example
 * @code
 * {
 *     PARCBuffer *dataToChunk = ...
 *     CCNxChunker *chunker = ccnxChunker_CreateFromBuffer(dataToChunk, 32);
 * }
 */
CCNxBufferChunker *ccnxBufferChunker_Create(PARCBuffer *data, size_t chunkSize);

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
 *     CCNxBufferChunker *original = ccnxBufferChunker_Create(...);
 *
 *     CCNxBufferChunker *reference = ccnxBufferChunker_Acquire(original);
 *
 *     ccnxBufferChunker_Release(&original);
 *     ccnxBufferChunker_Release(&reference);
 * }
 * @endcode
 *
 * @see ccnxBufferChunker_Release
 */
CCNxBufferChunker *ccnxBufferChunker_Acquire(const CCNxBufferChunker *chunker);

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
 *     CCNxBufferChunker *chunker = ccnxBufferChunker_Acquire(instance);
 *
 *     ccnxBufferChunker_Release(&chunker);
 * }
 * @endcode
 */
void ccnxBufferChunker_Release(CCNxBufferChunker **chunkerP);

/**
 * Determine if two `CCNxBufferChunker` instances are equal.
 *
 * The following equivalence relations on non-null `CCNxBufferChunker` instances are maintained:
 *
 *  * It is reflexive: for any non-null reference value x, `ccnxBufferChunker_Equals(x, x)`
 *      must return true.
 *
 *  * It is symmetric: for any non-null reference values x and y,
 *    `ccnxBufferChunker_Equals(x, y)` must return true if and only if
 *        `ccnxBufferChunker_Equals(y, x)` returns true.
 *
 *  * It is transitive: for any non-null reference values x, y, and z, if
 *        `ccnxBufferChunker_Equals(x, y)` returns true and
 *        `ccnxBufferChunker_Equals(y, z)` returns true,
 *        then  `ccnxBufferChunker_Equals(x, z)` must return true.
 *
 *  * It is consistent: for any non-null reference values x and y, multiple
 *      invocations of `ccnxBufferChunker_Equals(x, y)` consistently return true or
 *      consistently return false.
 *
 *  * For any non-null reference value x, `ccnxBufferChunker_Equals(x, NULL)` must
 *      return false.
 *
 * @param chunkerA A pointer to a `CCNxBufferChunker` instance.
 * @param chunkerB A pointer to a `CCNxBufferChunker` instance.
 * @return true if the two `CCNxBufferChunker` instances are equal.
 *
 * Example:
 * @code
 * {
 *     PARCBuffer *dataToChunk = ...
 *     CCNxBufferChunker *chunkerA = ccnxBufferChunker_Create(dataToChunk, 32);
 *     CCNxBufferChunker *chunkerB = ccnxBufferChunker_Create(dataToChunk, 32);
 *
 *     bool equals = ccnxBufferChunker_Equals(chunkerA, chunkerB);
 * }
 * @endcode
 */
bool ccnxBufferChunker_Equals(const CCNxBufferChunker *chunkerA, const CCNxBufferChunker *chunkerB);

/**
 * Return an iterator to traverse the chunks of the underlying data in sequential order.
 *
 * This function can only be called once per chunker instance since the iterator
 * will mutate internal state of the chunker.
 *
 * @param [in] chunker A `CCNxBufferChunker` instance.
 *
 * @return a `PARCIterator` that traverses the chunks of the underlying data.
 *
 * Example
 * @code
 * {
 *     PARCBuffer *dataToChunk = ...
 *     CCNxBufferChunker *chunker = ccnxBufferChunker_Create(dataToChunk, 32);
 *
 *     PARCIterator *itr = ccnxBufferChunker_ForwardIterator(chunker);
 *
 *     // use the iterator to traverse the chunker
 * }
 * @endcode
 */
PARCIterator *ccnxBufferChunker_ForwardIterator(const CCNxBufferChunker *chunker);

/**
 * Return an iterator to traverse the chunks of the underlying data in sequential order.
 *
 * This function can only be called once per chunker instance since the iterator
 * will mutate internal state of the chunker.
 *
 * @param [in] chunker A `CCNxBufferChunker` instance.
 *
 * @return a `PARCIterator` that traverses the chunks of the underlying data.
 *
 * Example
 * @code
 * {
 *     PARCBuffer *dataToChunk = ...
 *     CCNxBufferChunker *chunker = ccnxBufferChunker_Create(dataToChunk, 32);
 *
 *     PARCIterator *itr = ccnxBufferChunker_ReverseIterator(chunker);
 *
 *     // use the iterator to traverse the chunker
 * }
 * @endcode
 */
PARCIterator *ccnxBufferChunker_ReverseIterator(const CCNxBufferChunker *chunker);

#endif // libccnx_ccnx_BufferChunker_h
