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

#ifndef _MACTX_VHT_SIG_B_SU20_H_
#define _MACTX_VHT_SIG_B_SU20_H_
#if !defined(__ASSEMBLER__)
#endif

#include "vht_sig_b_su20_info.h"
#define NUM_OF_DWORDS_MACTX_VHT_SIG_B_SU20 2

#define NUM_OF_QWORDS_MACTX_VHT_SIG_B_SU20 1


struct mactx_vht_sig_b_su20 {
#ifndef WIFI_BIT_ORDER_BIG_ENDIAN
             struct   vht_sig_b_su20_info                                       mactx_vht_sig_b_su20_info_details;
             uint32_t tlv64_padding                                           : 32; // [31:0]
#else
             struct   vht_sig_b_su20_info                                       mactx_vht_sig_b_su20_info_details;
             uint32_t tlv64_padding                                           : 32; // [31:0]
#endif
};


/* Description		MACTX_VHT_SIG_B_SU20_INFO_DETAILS

			See detailed description of the STRUCT
*/


/* Description		LENGTH

			VHT-SIG-B Length (in units of 4 octets) = ceiling (LENGTH/4)
			
			<legal all>
*/

#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_LENGTH_OFFSET        0x0000000000000000
#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_LENGTH_LSB           0
#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_LENGTH_MSB           16
#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_LENGTH_MASK          0x000000000001ffff


/* Description		VHTB_RESERVED

			Reserved:  Set  to all ones for non-NDP frames and ignored
			 on receive
			<legal 2,7>
*/

#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_VHTB_RESERVED_OFFSET 0x0000000000000000
#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_VHTB_RESERVED_LSB    17
#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_VHTB_RESERVED_MSB    19
#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_VHTB_RESERVED_MASK   0x00000000000e0000


/* Description		TAIL

			Used to terminate the trellis of the convolutional decoder.
			
			Set to 0.  <legal 0>
*/

#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_TAIL_OFFSET          0x0000000000000000
#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_TAIL_LSB             20
#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_TAIL_MSB             25
#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_TAIL_MASK            0x0000000003f00000


/* Description		RESERVED

			Not part of VHT-SIG-B.
			Reserved: Set to 0 and ignored on receive  <legal 0>
*/

#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_RESERVED_OFFSET      0x0000000000000000
#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_RESERVED_LSB         26
#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_RESERVED_MSB         30
#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_RESERVED_MASK        0x000000007c000000


/* Description		RX_NDP

			Not part of VHT-SIG-B.
			Used to identify received NDP frame
			<legal 0,1>
*/

#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_RX_NDP_OFFSET        0x0000000000000000
#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_RX_NDP_LSB           31
#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_RX_NDP_MSB           31
#define MACTX_VHT_SIG_B_SU20_MACTX_VHT_SIG_B_SU20_INFO_DETAILS_RX_NDP_MASK          0x0000000080000000


/* Description		TLV64_PADDING

			Automatic DWORD padding inserted while converting TLV32 
			to TLV64 for 64 bit ARCH
			<legal 0>
*/

#define MACTX_VHT_SIG_B_SU20_TLV64_PADDING_OFFSET                                   0x0000000000000000
#define MACTX_VHT_SIG_B_SU20_TLV64_PADDING_LSB                                      32
#define MACTX_VHT_SIG_B_SU20_TLV64_PADDING_MSB                                      63
#define MACTX_VHT_SIG_B_SU20_TLV64_PADDING_MASK                                     0xffffffff00000000



#endif   // MACTX_VHT_SIG_B_SU20
