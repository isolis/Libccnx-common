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
 * @file ccnxCodecSchemaV1_FixedHeader.h
 * @brief common definitions and functions for the FixedHeader
 *
 * See ccnxCodecSchemaV1_Packet.h for an overview of the version 1 codec
 *
 * This is the one file you need to include for all FixedHeader operations.  It will
 * include all the Decoders and Encoders.
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */

#ifndef TransportRTA_ccnxCodecSchemaV1_FixedHeader_h
#define TransportRTA_ccnxCodecSchemaV1_FixedHeader_h

typedef struct __attribute__ ((__packed__)) rta_tlv_schema_v1_fixed_header {
    uint8_t version;
    uint8_t packetType;
    uint16_t packetLength;
    uint8_t reserved[3];
    uint8_t headerLength;
} CCNxCodecSchemaV1FixedHeader;

typedef struct __attribute__ ((__packed__)) rta_tlv_schema_v1_interest_header {
    uint8_t version;
    uint8_t packetType;
    uint16_t packetLength;
    uint8_t hopLimit;
    uint8_t returnCode;
    uint8_t flags;
    uint8_t headerLength;
} CCNxCodecSchemaV1InterestHeader;


#include <ccnx/common/codec/schema_v1/ccnxCodecSchemaV1_FixedHeaderDecoder.h>
#include <ccnx/common/codec/schema_v1/ccnxCodecSchemaV1_FixedHeaderEncoder.h>
#endif // TransportRTA_ccnxCodecSchemaV1_FixedHeader_h
