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

#ifndef _L_SIG_A_INFO_H_
#define _L_SIG_A_INFO_H_
#if !defined(__ASSEMBLER__)
#endif

#define NUM_OF_DWORDS_L_SIG_A_INFO 1


struct l_sig_a_info {
#ifndef WIFI_BIT_ORDER_BIG_ENDIAN
             uint32_t rate                                                    :  4, // [3:0]
                      lsig_reserved                                           :  1, // [4:4]
                      length                                                  : 12, // [16:5]
                      parity                                                  :  1, // [17:17]
                      tail                                                    :  6, // [23:18]
                      pkt_type                                                :  4, // [27:24]
                      captured_implicit_sounding                              :  1, // [28:28]
                      reserved                                                :  2, // [30:29]
                      rx_integrity_check_passed                               :  1; // [31:31]
#else
             uint32_t rx_integrity_check_passed                               :  1, // [31:31]
                      reserved                                                :  2, // [30:29]
                      captured_implicit_sounding                              :  1, // [28:28]
                      pkt_type                                                :  4, // [27:24]
                      tail                                                    :  6, // [23:18]
                      parity                                                  :  1, // [17:17]
                      length                                                  : 12, // [16:5]
                      lsig_reserved                                           :  1, // [4:4]
                      rate                                                    :  4; // [3:0]
#endif
};


/* Description		RATE

			This format is originally defined for OFDM as a 4 bit field
			 but the 5th bit was added to indicate 11b formatted frames. 
			 In the standard bit [4] is specified as reserved.  For 
			11b frames this L-SIG is transformed in the PHY into the
			 11b preamble format.  The following are the rates:
			<enum 8     ofdm_48_mbps> 64-QAM 2/3 (48 Mbps)
			<enum 9     ofdm_24_mbps> 16-QAM 1/2 (24 Mbps)
			<enum 10     ofdm_12_mbps> QPSK 1/2 (12 Mbps)
			<enum 11     ofdm_6_mbps> BPSK 1/2 (6 Mbps)
			<enum 12     ofdm_54_mbps> 64-QAM 3/4 (54 Mbps)
			<enum 13     ofdm_36_mbps> 16-QAM 3/4 (36 Mbps)
			<enum 14     ofdm_18_mbps> QPSK 1/2 (18 Mbps)
			<enum 15     ofdm_9_mbps> BPSK 3/4 (9 Mbps)
			<legal 8-15>
*/

#define L_SIG_A_INFO_RATE_OFFSET                                                    0x00000000
#define L_SIG_A_INFO_RATE_LSB                                                       0
#define L_SIG_A_INFO_RATE_MSB                                                       3
#define L_SIG_A_INFO_RATE_MASK                                                      0x0000000f


/* Description		LSIG_RESERVED

			Reserved: Should be set to 0 by the MAC and ignored by the
			 PHY
			<legal 0>
*/

#define L_SIG_A_INFO_LSIG_RESERVED_OFFSET                                           0x00000000
#define L_SIG_A_INFO_LSIG_RESERVED_LSB                                              4
#define L_SIG_A_INFO_LSIG_RESERVED_MSB                                              4
#define L_SIG_A_INFO_LSIG_RESERVED_MASK                                             0x00000010


/* Description		LENGTH

			The length indicates the number of octets in this MPDU. 
			 Note that when using mixed mode .11n preamble or .11ac/.11ax/.11ba/.11be
			 this length provides the spoofed length for the PPDU.  
			This length provides part of the information (viz. PPDU 
			duration) to derive the actually PSDU length.  For legacy
			 OFDM and 11B frames the maximum length is 4095.
			<legal all>
*/

#define L_SIG_A_INFO_LENGTH_OFFSET                                                  0x00000000
#define L_SIG_A_INFO_LENGTH_LSB                                                     5
#define L_SIG_A_INFO_LENGTH_MSB                                                     16
#define L_SIG_A_INFO_LENGTH_MASK                                                    0x0001ffe0


/* Description		PARITY

			11a/n/ac TX: This field provides even parity over the first
			 18 bits of the signal field which means that the sum of
			 1s in the signal field will always be even on transmission. 
			The value of the field is computed by the MAC.
			11a/n/ac RX: this field contains the received parity field
			 from the L-SIG symbol for the current packet.
			<legal 0-1>
*/

#define L_SIG_A_INFO_PARITY_OFFSET                                                  0x00000000
#define L_SIG_A_INFO_PARITY_LSB                                                     17
#define L_SIG_A_INFO_PARITY_MSB                                                     17
#define L_SIG_A_INFO_PARITY_MASK                                                    0x00020000


/* Description		TAIL

			The 6 bits of tail is always set to 0 is used to flush the
			 BCC encoder and decoder.  <legal 0>
*/

#define L_SIG_A_INFO_TAIL_OFFSET                                                    0x00000000
#define L_SIG_A_INFO_TAIL_LSB                                                       18
#define L_SIG_A_INFO_TAIL_MSB                                                       23
#define L_SIG_A_INFO_TAIL_MASK                                                      0x00fc0000


/* Description		PKT_TYPE

			Only used on the RX side.  
			Note: This is not really part of L-SIG
			
			Packet type:
			<enum 0 dot11a>802.11a PPDU type
			<enum 1 dot11b>802.11b PPDU type
			<enum 2 dot11n_mm>802.11n Mixed Mode PPDU type
			<enum 3 dot11ac>802.11ac PPDU type
			<enum 4 dot11ax>802.11ax PPDU type
			<enum 5 dot11ba>802.11ba (WUR) PPDU type
			<enum 6 dot11be>802.11be PPDU type
			<enum 7 dot11az>802.11az (ranging) PPDU type
			<enum 8 dot11n_gf>802.11n Green Field PPDU type (unsupported
			 & aborted)
*/

#define L_SIG_A_INFO_PKT_TYPE_OFFSET                                                0x00000000
#define L_SIG_A_INFO_PKT_TYPE_LSB                                                   24
#define L_SIG_A_INFO_PKT_TYPE_MSB                                                   27
#define L_SIG_A_INFO_PKT_TYPE_MASK                                                  0x0f000000


/* Description		CAPTURED_IMPLICIT_SOUNDING

			Only used on the RX side.  
			Note: This is not really part of L-SIG
			
			This indicates that the PHY has captured implicit sounding.
			
*/

#define L_SIG_A_INFO_CAPTURED_IMPLICIT_SOUNDING_OFFSET                              0x00000000
#define L_SIG_A_INFO_CAPTURED_IMPLICIT_SOUNDING_LSB                                 28
#define L_SIG_A_INFO_CAPTURED_IMPLICIT_SOUNDING_MSB                                 28
#define L_SIG_A_INFO_CAPTURED_IMPLICIT_SOUNDING_MASK                                0x10000000


/* Description		RESERVED

			Reserved: Should be set to 0 by the transmitting MAC and
			 ignored by the PHY <legal 0>
*/

#define L_SIG_A_INFO_RESERVED_OFFSET                                                0x00000000
#define L_SIG_A_INFO_RESERVED_LSB                                                   29
#define L_SIG_A_INFO_RESERVED_MSB                                                   30
#define L_SIG_A_INFO_RESERVED_MASK                                                  0x60000000


/* Description		RX_INTEGRITY_CHECK_PASSED

			TX side: Set to 0
			RX side: Set to 1 if PHY determines the L-SIG integrity 
			check has passed, else set to 0
			
			<legal all>
*/

#define L_SIG_A_INFO_RX_INTEGRITY_CHECK_PASSED_OFFSET                               0x00000000
#define L_SIG_A_INFO_RX_INTEGRITY_CHECK_PASSED_LSB                                  31
#define L_SIG_A_INFO_RX_INTEGRITY_CHECK_PASSED_MSB                                  31
#define L_SIG_A_INFO_RX_INTEGRITY_CHECK_PASSED_MASK                                 0x80000000



#endif   // L_SIG_A_INFO
