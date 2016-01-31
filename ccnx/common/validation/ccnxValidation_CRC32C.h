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
 * @file ccnxValidation_CRC32C.h
 * @brief <#Brief Description#>
 *
 * <#Detailed Description#>
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef CCNx_Common_ccnxValidation_CRC32C_h
#define CCNx_Common_ccnxValidation_CRC32C_h

#include <parc/security/parc_Signer.h>
#include <parc/security/parc_Verifier.h>
#include <ccnx/common/internal/ccnx_TlvDictionary.h>

/**
 * Sets the Validation algorithm to RSA-SHA256
 *
 * Sets the validation algorithm to be RSA with a SHA-256 digest.  Optionally includes
 * a KeyId and KeyLocator with the message.
 *
 * @param [in] message The message dictionary
 *
 * @return `true` success
 * @return `false` failure
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
bool ccnxValidationCRC32C_Set(CCNxTlvDictionary *message);

/**
 * Determines if the validation algorithm is RSA-SHA256 *
 * @param [in] message The message to check
 *
 * @return `true` The validation algorithm in the dictionary is this one
 * @return `false` The validaiton algorithm in the dictionary is something else or not present
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
bool ccnxValidationCRC32C_Test(const CCNxTlvDictionary *message);

/**
 * Creates a signer to compute a CRC32C
 *
 * @return non-null An allocated signer
 * @return null An error
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCSigner *ccnxValidationCRC32C_CreateSigner(void);

/**
 * Creates a verifier to check a CRC32C "signature"
 *
 * @return non-null An allocated verifier
 * @return null An error
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
PARCVerifier *ccnxValidationCRC32C_CreateVerifier(void);
#endif // CCNx_Common_ccnxValidation_CRC32C_h
