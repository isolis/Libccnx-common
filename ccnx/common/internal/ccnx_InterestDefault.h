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
 * @file ccnx_InterestDefault.h
 * @brief Default values for various fields in an Interest
 *
 * Declares several constants that may be used when creating an Interest with default values.
 * These may be used in a V0 or V1 Interest.
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef __CCNx_Common__ccnx_InterestDefault__
#define __CCNx_Common__ccnx_InterestDefault__

#include <inttypes.h>
#include <ccnx/common/internal/ccnx_InterestPayloadIdMethod.h>

/**
 * May be used in calls to create an Interest with the default lifetime.  An Interest with
 * the default lifetime does not encode the field in the wire format.
 */
extern const uint32_t CCNxInterestDefault_LifetimeMilliseconds;

/**
 * May be used in calls to create an Interest with the default hoplimit.
 */
extern const uint32_t CCNxInterestDefault_HopLimit;

/**
 * May be used in calls to create an Interest with the default payload id method.
 *
 * The PayloadIdMethod is a field inside the Interest that describes how the InterestPayloadId in the Name
 * was calcuated.
 */
extern const CCNxInterestPayloadIdMethod CCNxInterestDefault_PayloadIdMethod;

#endif /* defined(__CCNx_Common__ccnx_InterestDefault__) */
