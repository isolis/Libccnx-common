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
 * @brief <#Brief Description#>
 *
 * <#Detailed Description#>
 *
 * @author Alan Walendowski, Palo Alto Research Center (Xerox PARC)
 * @copyright 2014-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef CCNx_Common_ccnx_internal_InterestReturnInterface_h
#define CCNx_Common_ccnx_internal_InterestReturnInterface_h

#include <ccnx/common/internal/ccnx_TlvDictionary.h>
#include <ccnx/common/ccnx_InterestReturn.h>
#include <ccnx/common/ccnx_Interest.h>


typedef struct ccnx_interest_return_interface {
    CCNxInterestInterface interestImpl;

    CCNxTlvDictionary  *(*Create)(const CCNxInterest * interest, CCNxInterestReturn_ReturnCode code);

    bool                (*Equals)(const CCNxTlvDictionary *objectA, const CCNxTlvDictionary *objectB);
    void                (*AssertValid)(const CCNxTlvDictionary *dict);
    char               *(*ToString)(const CCNxTlvDictionary * dict);

    uint32_t            (*GetReturnCode)(const CCNxTlvDictionary *dict);
} CCNxInterestReturnInterface;

extern CCNxInterestReturnInterface CCNxInterestReturnFacadeV1_Implementation;

/**
 * Given a CCNxTlvDictionary representing a CCNxInterestReturn, return the address of the CCNxInterestReturnInterface
 * instance that should be used to access the InterestReturn.
 *
 * @param interestDictionary - a {@link CCNxTlvDictionary} representing a CCNxInterestReturn.
 * @return the address of the `CCNxInterestReturnInterface` instance that should be used to access the CCNxInterestReturn.
 *
 * Example:
 * @code
 * {
 *
 *     CCNxInterest *interest = ...;
 *     CCNxInterestReturn *interestReturn =
 *          ccnxInterestReturn_Create(interest, CCNxInterestReturn_ReturnCode_NoRoute);
 *
 *     //V1 test
 *     if (ccnxInterestReturnInterface_GetInterface(interestReturn) == &CCNxInterestReturnFacadeV1_Implementation) {
 *         printf("Using a V1 CCNxInterestReturnInterface \n");
 *     }
 *
 *     ...
 *
 *     ccnxInterestReturn_Release(&interestReturn);
 * } * @endcode
 */
CCNxInterestReturnInterface *ccnxInterestReturnInterface_GetInterface(const CCNxTlvDictionary *interestDictionary);
#endif
