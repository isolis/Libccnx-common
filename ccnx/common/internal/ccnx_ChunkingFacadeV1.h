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
 * @file ccnx_ChunkingFacade.h
 * @brief <#Brief Description#>
 *
 * <#Detailed Description#>
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef libccnx_ccnx_ChunkingFacadeV1_h
#define libccnx_ccnx_ChunkingFacadeV1_h

#include <ccnx/common/internal/ccnx_TlvDictionary.h>

/**
 * Determines if an EndChunkNumber exists in the metadata
 *
 * Compatible with V0 and V1 schemas.
 *
 * @param [in] contentObjectDictionary A dictionary to check
 *
 * @return false There is no EndChunkNumber specified or the dictinoary is not a ContentObject
 * @return true There is an EndChunkNumber specified
 *
 * Example:
 * @code
 *      static PARCElasticBuffer *
 *      _ccnxContentObjectFacade_CreateFinalBlockId(const CCNxTlvDictionary *contentObjectDictionary)
 *      {
 *          if (ccnxChunkingFacade_HasEndChunkNumber(contentObjectDictionary)) {
 *              uint64_t endChunkNumber = ccnxChunkingFacade_GetEndChunkNumber(contentObjectDictionary);
 *              PARCElasticBuffer *fbid = _ccnxContentObjectFacade_EncodeFinalBlockId(endChunkNumber);
 *              return fbid;
 *          }
 *          return NULL;
 *      }
 * @endcode
 */
bool ccnxChunkingFacadeV1_HasEndChunkNumber(const CCNxTlvDictionary *contentObjectDictionary);

/**
 * Retrieves the end chunk number
 *
 * Retieves the end chunk number as an unsigned 64-bit integer.
 * This function will trapIllegalValue if there is not an EndChunkNumber present.
 * The EndChunkNumber is the chunk number of the last Content Object in a chunked series.
 *
 * @param [in] contentObjectDictionary A dictionary to check
 *
 * @return number The ending chunk number
 *
 * Example:
 * @code
 *      static PARCElasticBuffer *
 *      _ccnxContentObjectFacade_CreateFinalBlockId(const CCNxTlvDictionary *contentObjectDictionary)
 *      {
 *          if (ccnxChunkingFacade_HasEndChunkNumber(contentObjectDictionary)) {
 *              uint64_t endChunkNumber = ccnxChunkingFacade_GetEndChunkNumber(contentObjectDictionary);
 *              PARCElasticBuffer *fbid = _ccnxContentObjectFacade_EncodeFinalBlockId(endChunkNumber);
 *              return fbid;
 *          }
 *          return NULL;
 *      }
 * @endcode
 */
uint64_t ccnxChunkingFacadeV1_GetEndChunkNumber(const CCNxTlvDictionary *contentObjectDictionary);

/**
 * Sets the EndChunkNumber of a ContentObject
 *
 * The dictionary must be a ContentObject, otherwise this function will trapIllegalValue.
 * If an EndChunkNumber already exits, will not update but return false.
 *
 * @param [in] contentObjectDictionary A dictionary to check
 * @param [in] endChunkNumber The ending chunk number
 *
 * @return true The value was set in the dictionary
 * @return false A failure (likely value already set)
 *
 * Example:
 * @code
 * {
 *          CCNxTlvDictionary *obj = ccnxContentObjectFacade_Create(...);
 *          ccnxChunkingFacade_SetEndChunkNumber(obj, 74);
 * }
 * @endcode
 */
bool ccnxChunkingFacadeV1_SetEndChunkNumber(CCNxTlvDictionary *contentObjectDictionary, uint64_t endChunkNumber);
#endif // libccnx_ccnx_ChunkingFacadeV1_h
