/*
 * Copyright (c) 2023 Qualcomm Innovation Center, Inc. All rights reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _ACK_REPORT_H_
#define _ACK_REPORT_H_
#if !defined(__ASSEMBLER__)
#endif

#define NUM_OF_DWORDS_ACK_REPORT 1


struct ack_report {
#ifndef WIFI_BIT_ORDER_BIG_ENDIAN
             uint32_t selfgen_response_reason                                 :  4, // [3:0]
                      ax_trigger_type                                         :  4, // [7:4]
                      sr_ppdu                                                 :  1, // [8:8]
                      reserved                                                :  7, // [15:9]
                      frame_control                                           : 16; // [31:16]
#else
             uint32_t frame_control                                           : 16, // [31:16]
                      reserved                                                :  7, // [15:9]
                      sr_ppdu                                                 :  1, // [8:8]
                      ax_trigger_type                                         :  4, // [7:4]
                      selfgen_response_reason                                 :  4; // [3:0]
#endif
};


/* Description		SELFGEN_RESPONSE_REASON

			Field that indicates why the received frame needs a response
			 in SIFS time. The possible responses are listed in order.
			
			
			<enum 0     CTS_frame> 
			<enum 1     ACK_frame> 
			<enum 2     BA_frame > 
			<enum 3     Qboost_trigger> Qboost trigger received
			<enum 4     PSPOLL_trigger> PSPOLL trigger received
			<enum 5     UAPSD_trigger > Unscheduled APSD  trigger received
			 
			<enum 6     CBF_frame> the CBF frame needs to be send as
			 a result of NDP or BRPOLL
			<enum 7     ax_su_trigger> 11ax trigger received for this
			 device
			<enum 8     ax_wildcard_trigger> 11ax wildcardtrigger has
			 been received 
			<enum 9     ax_unassoc_wildcard_trigger> 11ax wildcard trigger
			 for unassociated STAs has been received
			<enum 12     eht_su_trigger> EHT R1 trigger received for
			 this device
			
			<enum 10     MU_UL_response_to_response>
			
			<enum 11     Ranging_NDP_LMR_frames> Ranging NDP + LMR need
			 to be sent in response to ranging NDPA + NDP
			
			<legal 0-12>
*/

#define ACK_REPORT_SELFGEN_RESPONSE_REASON_OFFSET                                   0x00000000
#define ACK_REPORT_SELFGEN_RESPONSE_REASON_LSB                                      0
#define ACK_REPORT_SELFGEN_RESPONSE_REASON_MSB                                      3
#define ACK_REPORT_SELFGEN_RESPONSE_REASON_MASK                                     0x0000000f


/* Description		AX_TRIGGER_TYPE

			Field Only valid when selfgen_response_reason is an 11ax
			 related trigger
			
			The 11AX trigger type/ trigger number:
			It identifies which trigger was received.
			<enum 0 ax_trigger_basic>
			<enum 1 ax_trigger_brpoll>
			<enum 2 ax_trigger_mu_bar>
			<enum 3 ax_trigger_mu_rts>
			<enum 4 ax_trigger_buffer_size>
			<enum 5 ax_trigger_gcr_mu_bar>
			<enum 6 ax_trigger_BQRP> 
			<enum 7 ax_trigger_NDP_fb_report_poll> 
			<enum 8 ax_tb_ranging_trigger>
			<enum 9 ax_trigger_reserved_9>
			<enum 10 ax_trigger_reserved_10>
			<enum 11 ax_trigger_reserved_11>
			<enum 12 ax_trigger_reserved_12>
			<enum 13 ax_trigger_reserved_13>
			<enum 14 ax_trigger_reserved_14>
			<enum 15 ax_trigger_reserved_15>
			
			<legal all>
*/

#define ACK_REPORT_AX_TRIGGER_TYPE_OFFSET                                           0x00000000
#define ACK_REPORT_AX_TRIGGER_TYPE_LSB                                              4
#define ACK_REPORT_AX_TRIGGER_TYPE_MSB                                              7
#define ACK_REPORT_AX_TRIGGER_TYPE_MASK                                             0x000000f0


/* Description		SR_PPDU

			Field only valid with SRP Responder support
			
			Indicates if the received frame was sent using SRP as indicated
			 by the 'SR PPDU' bit in the 'CAS Control' in the 'HE A-Control' 
			in one of the MPDUs received
			<legal all>
*/

#define ACK_REPORT_SR_PPDU_OFFSET                                                   0x00000000
#define ACK_REPORT_SR_PPDU_LSB                                                      8
#define ACK_REPORT_SR_PPDU_MSB                                                      8
#define ACK_REPORT_SR_PPDU_MASK                                                     0x00000100


/* Description		RESERVED

			<legal 0>
*/

#define ACK_REPORT_RESERVED_OFFSET                                                  0x00000000
#define ACK_REPORT_RESERVED_LSB                                                     9
#define ACK_REPORT_RESERVED_MSB                                                     15
#define ACK_REPORT_RESERVED_MASK                                                    0x0000fe00


/* Description		FRAME_CONTROL

			Field not valid when selfgen_response_reason is MU_UL_response_to_response
			
			
			For SU receptions:
			frame control field of the received frame
			
			In 11ah Mode of Operation, for non-NDP frames the BW information
			 is extracted from Frame Control fields [11:8].
			
			Decode is as follows 
			
			Bits[11] - Dynamic/Static 
			Bits[10:8] - Channel BW
*/

#define ACK_REPORT_FRAME_CONTROL_OFFSET                                             0x00000000
#define ACK_REPORT_FRAME_CONTROL_LSB                                                16
#define ACK_REPORT_FRAME_CONTROL_MSB                                                31
#define ACK_REPORT_FRAME_CONTROL_MASK                                               0xffff0000



#endif   // ACK_REPORT
