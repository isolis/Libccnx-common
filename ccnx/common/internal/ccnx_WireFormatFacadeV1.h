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
 * @file ccnx_WireFormatFacadeV1.h
 * @ingroup Utility
 *
 * A WireFormat facade will set/get the wire format representation of a message from the
 * dictionary.
 *
 * One may also create a message dictionary only with a wire format, not specifying the actual message type.
 * This occurs mostly at the lowest layer that receives a network buffer and does not yet know what sort of message it holds.
 *
 * This facade is used by the Forwarder Connector to create the original dictionary
 * at the bottom of the stack on receive.  It is also used by the Codec component to set
 * the wireformat to encode a packet.
 *
 * If an application has a pre-encoded packet, it can create an empty dictionary and set the wire format
 * then send that down the stack.
 *
 * @author Marc Mosko, Palo Alto Research Center (Xerox PARC)
 * @copyright 2013-2015, Xerox Corporation (Xerox)and Palo Alto Research Center (PARC).  All rights reserved.
 */
#ifndef libccnx_ccnx_WireFormatFacadeV1_h
#define libccnx_ccnx_WireFormatFacadeV1_h


#include <ccnx/common/internal/ccnx_WireFormatMessageInterface.h>

extern CCNxWireFormatMessageInterface CCNxWireFormatFacadeV1_Implementation;
#endif // libccnx_ccnx_WireFormatFacadeV1_h
