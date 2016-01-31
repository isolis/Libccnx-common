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
 * Utilities used by the Schema unit tests to compare buffers
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

/**
 * Compares an encoding buffer to linear memory
 *
 * Will assert if the memory does not compare.  The encoding buffer will be finalized.
 * Will assert if the encoder has an error.
 *
 * @param [in] encoder The encoding buffer to compare
 * @param [in] length The length of linear memory
 * @param [in] memory The "truth" memory to compare against
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
void
testCompareEncoderToLinearMemory(CCNxCodecTlvEncoder *encoder, size_t length, uint8_t memory[length])
{
    assertFalse(ccnxCodecTlvEncoder_HasError(encoder), "Encoder has error")
    {
        printf("ERROR: %s\n", ccnxCodecError_ToString(ccnxCodecTlvEncoder_GetError(encoder)));
    }

    PARCBuffer *truth = parcBuffer_Wrap(memory, length, 0, length);
    ccnxCodecTlvEncoder_Finalize(encoder);
    PARCBuffer *buffer = ccnxCodecTlvEncoder_CreateBuffer(encoder);

    assertTrue(parcBuffer_Equals(buffer, truth), "buffers not equal")
    {
        printf("Expected\n");
        parcBuffer_Display(truth, 3);

        printf("Got this\n");
        parcBuffer_Display(buffer, 3);
    }

    parcBuffer_Release(&truth);
    parcBuffer_Release(&buffer);
}

/**
 * Compares an encoding buffer to a PARCBuffer
 *
 * Will assert if the memory does not compare.  The encoding buffer will be finalized.
 * Will assert if the encoder has an error.
 *
 * @param [in] encoder The encoding buffer to compare
 * @param [in] buffer The buffer to compare to, must be setup to be read (i.e. flipped)
 *
 * Example:
 * @code
 * <#example#>
 * @endcode
 */
void
testCompareEncoderToBuffer(CCNxCodecTlvEncoder *encoder, PARCBuffer *buffer)
{
    assertFalse(ccnxCodecTlvEncoder_HasError(encoder), "Encoder has error")
    {
        printf("ERROR: %s\n", ccnxCodecError_ToString(ccnxCodecTlvEncoder_GetError(encoder)));
    }


    uint8_t *linearMemory = parcByteArray_Array(parcBuffer_Array(buffer));
    size_t offset = parcBuffer_ArrayOffset(buffer) + parcBuffer_Position(buffer);
    size_t length = parcBuffer_Remaining(buffer);

    testCompareEncoderToLinearMemory(encoder, length, linearMemory + offset);
}

