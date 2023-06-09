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

#ifndef _HE_SIG_A_MU_DL_INFO_H_
#define _HE_SIG_A_MU_DL_INFO_H_
#if !defined(__ASSEMBLER__)
#endif

#define NUM_OF_DWORDS_HE_SIG_A_MU_DL_INFO 2


struct he_sig_a_mu_dl_info {
#ifndef WIFI_BIT_ORDER_BIG_ENDIAN
             uint32_t dl_ul_flag                                              :  1, // [0:0]
                      mcs_of_sig_b                                            :  3, // [3:1]
                      dcm_of_sig_b                                            :  1, // [4:4]
                      bss_color_id                                            :  6, // [10:5]
                      spatial_reuse                                           :  4, // [14:11]
                      transmit_bw                                             :  3, // [17:15]
                      num_sig_b_symbols                                       :  4, // [21:18]
                      comp_mode_sig_b                                         :  1, // [22:22]
                      cp_ltf_size                                             :  2, // [24:23]
                      doppler_indication                                      :  1, // [25:25]
                      reserved_0a                                             :  6; // [31:26]
             uint32_t txop_duration                                           :  7, // [6:0]
                      reserved_1a                                             :  1, // [7:7]
                      num_ltf_symbols                                         :  3, // [10:8]
                      ldpc_extra_symbol                                       :  1, // [11:11]
                      stbc                                                    :  1, // [12:12]
                      packet_extension_a_factor                               :  2, // [14:13]
                      packet_extension_pe_disambiguity                        :  1, // [15:15]
                      crc                                                     :  4, // [19:16]
                      tail                                                    :  6, // [25:20]
                      reserved_1b                                             :  5, // [30:26]
                      rx_integrity_check_passed                               :  1; // [31:31]
#else
             uint32_t reserved_0a                                             :  6, // [31:26]
                      doppler_indication                                      :  1, // [25:25]
                      cp_ltf_size                                             :  2, // [24:23]
                      comp_mode_sig_b                                         :  1, // [22:22]
                      num_sig_b_symbols                                       :  4, // [21:18]
                      transmit_bw                                             :  3, // [17:15]
                      spatial_reuse                                           :  4, // [14:11]
                      bss_color_id                                            :  6, // [10:5]
                      dcm_of_sig_b                                            :  1, // [4:4]
                      mcs_of_sig_b                                            :  3, // [3:1]
                      dl_ul_flag                                              :  1; // [0:0]
             uint32_t rx_integrity_check_passed                               :  1, // [31:31]
                      reserved_1b                                             :  5, // [30:26]
                      tail                                                    :  6, // [25:20]
                      crc                                                     :  4, // [19:16]
                      packet_extension_pe_disambiguity                        :  1, // [15:15]
                      packet_extension_a_factor                               :  2, // [14:13]
                      stbc                                                    :  1, // [12:12]
                      ldpc_extra_symbol                                       :  1, // [11:11]
                      num_ltf_symbols                                         :  3, // [10:8]
                      reserved_1a                                             :  1, // [7:7]
                      txop_duration                                           :  7; // [6:0]
#endif
};


/* Description		DL_UL_FLAG

			Differentiates between DL and UL transmission 
			
			<enum 0 DL_UL_FLAG_IS_DL_OR_TDLS>
			<enum 1 DL_UL_FLAG_IS_UL>
			NOTE: This is unsupported for "HE MU" format (including "MU_SU") 
			<legal all>
*/

#define HE_SIG_A_MU_DL_INFO_DL_UL_FLAG_OFFSET                                       0x00000000
#define HE_SIG_A_MU_DL_INFO_DL_UL_FLAG_LSB                                          0
#define HE_SIG_A_MU_DL_INFO_DL_UL_FLAG_MSB                                          0
#define HE_SIG_A_MU_DL_INFO_DL_UL_FLAG_MASK                                         0x00000001


/* Description		MCS_OF_SIG_B

			Indicates the MCS of HE-SIG-B
			<legal 0-5>
*/

#define HE_SIG_A_MU_DL_INFO_MCS_OF_SIG_B_OFFSET                                     0x00000000
#define HE_SIG_A_MU_DL_INFO_MCS_OF_SIG_B_LSB                                        1
#define HE_SIG_A_MU_DL_INFO_MCS_OF_SIG_B_MSB                                        3
#define HE_SIG_A_MU_DL_INFO_MCS_OF_SIG_B_MASK                                       0x0000000e


/* Description		DCM_OF_SIG_B

			Indicates whether dual sub-carrier modulation is applied
			 to HE-SIG-B 
			
			0: No DCM for HE_SIG_B
			1: DCM for HE_SIG_B
			<legal all>
*/

#define HE_SIG_A_MU_DL_INFO_DCM_OF_SIG_B_OFFSET                                     0x00000000
#define HE_SIG_A_MU_DL_INFO_DCM_OF_SIG_B_LSB                                        4
#define HE_SIG_A_MU_DL_INFO_DCM_OF_SIG_B_MSB                                        4
#define HE_SIG_A_MU_DL_INFO_DCM_OF_SIG_B_MASK                                       0x00000010


/* Description		BSS_COLOR_ID

			BSS color ID 
			
			Field Used by MAC HW
			<legal all>
*/

#define HE_SIG_A_MU_DL_INFO_BSS_COLOR_ID_OFFSET                                     0x00000000
#define HE_SIG_A_MU_DL_INFO_BSS_COLOR_ID_LSB                                        5
#define HE_SIG_A_MU_DL_INFO_BSS_COLOR_ID_MSB                                        10
#define HE_SIG_A_MU_DL_INFO_BSS_COLOR_ID_MASK                                       0x000007e0


/* Description		SPATIAL_REUSE

			Spatial reuse
			
			For 20MHz one SR field corresponding to entire 20MHz (other
			 3 fields indicate identical values)
			For 40MHz two SR fields for each 20MHz (other 2 fields indicate
			 identical values)
			For 80MHz four SR fields for each 20MHz
			For 160MHz four SR fields for each 40MHz
			<legal all>
*/

#define HE_SIG_A_MU_DL_INFO_SPATIAL_REUSE_OFFSET                                    0x00000000
#define HE_SIG_A_MU_DL_INFO_SPATIAL_REUSE_LSB                                       11
#define HE_SIG_A_MU_DL_INFO_SPATIAL_REUSE_MSB                                       14
#define HE_SIG_A_MU_DL_INFO_SPATIAL_REUSE_MASK                                      0x00007800


/* Description		TRANSMIT_BW

			Bandwidth of the PPDU.
			
			<enum 0 HE_SIG_A_MU_DL_BW20> 20 Mhz 
			<enum 1 HE_SIG_A_MU_DL_BW40> 40 Mhz 
			<enum 2 HE_SIG_A_MU_DL_BW80> 80 MHz non-preamble puncturing
			 mode
			<enum 3 HE_SIG_A_MU_DL_BW160> 160 MHz and 80+80 MHz non-preamble
			 puncturing mode
			<enum 4 HE_SIG_A_MU_DL_BW80_SEC_20_PUNC> for preamble puncturing
			 in 80 MHz, where in the preamble only the secondary 20 
			MHz is punctured
			<enum 5 HE_SIG_A_MU_DL_BW80_20_PUNC_IN_SEC_40> for preamble
			 puncturing in 80 MHz, where in the preamble only one of
			 the two 20 MHz sub-channels in secondary 40 MHz is punctured.
			
			<enum 6 HE_SIG_A_MU_DL_BW160_SEC_20_PUNC> for preamble puncturing
			 in 160 MHz or 80+80 MHz, where in the primary 80 MHz of
			 the preamble only the secondary 20 MHz is punctured.
			<enum 7 HE_SIG_A_MU_DL_BW160_SEC_40_80_PUNC> for preamble
			 puncturing in 160 MHz or 80+80 MHz, where in the primary
			 80 MHz of the preamble the primary 40 MHz is present.
			
			On RX side, Field Used by MAC HW
			<legal 0-7>
*/

#define HE_SIG_A_MU_DL_INFO_TRANSMIT_BW_OFFSET                                      0x00000000
#define HE_SIG_A_MU_DL_INFO_TRANSMIT_BW_LSB                                         15
#define HE_SIG_A_MU_DL_INFO_TRANSMIT_BW_MSB                                         17
#define HE_SIG_A_MU_DL_INFO_TRANSMIT_BW_MASK                                        0x00038000


/* Description		NUM_SIG_B_SYMBOLS

			Number of symbols
			
			For OFDMA, the actual number of symbols is 1 larger then
			 indicated in this field.
			
			For MU-MIMO this is equal to the number of users - 1: the
			 following encoding is used:
			1 => 2 users
			2 => 3 users
			Etc.
			
			<legal all>
*/

#define HE_SIG_A_MU_DL_INFO_NUM_SIG_B_SYMBOLS_OFFSET                                0x00000000
#define HE_SIG_A_MU_DL_INFO_NUM_SIG_B_SYMBOLS_LSB                                   18
#define HE_SIG_A_MU_DL_INFO_NUM_SIG_B_SYMBOLS_MSB                                   21
#define HE_SIG_A_MU_DL_INFO_NUM_SIG_B_SYMBOLS_MASK                                  0x003c0000


/* Description		COMP_MODE_SIG_B

			Indicates the compression mode of HE-SIG-B
			
			0: Regular [uncomp mode]
			1: compressed mode (full-BW MU-MIMO only) 
			<legal all>
*/

#define HE_SIG_A_MU_DL_INFO_COMP_MODE_SIG_B_OFFSET                                  0x00000000
#define HE_SIG_A_MU_DL_INFO_COMP_MODE_SIG_B_LSB                                     22
#define HE_SIG_A_MU_DL_INFO_COMP_MODE_SIG_B_MSB                                     22
#define HE_SIG_A_MU_DL_INFO_COMP_MODE_SIG_B_MASK                                    0x00400000


/* Description		CP_LTF_SIZE

			Indicates the CP and HE-LTF type 
			
			<enum 0 MU_FourX_LTF_0_8CP> 4xLTF + 0.8 us CP
			<enum 1 MU_TwoX_LTF_0_8CP> 2x LTF + 0.8 µs CP
			<enum 2 MU_TwoX_LTF_1_6CP> 2x LTF + 1.6 µs CP
			<enum 3 MU_FourX_LTF_3_2CP> 4x LTF + 3.2 µs CP 
			
			<legal all>
*/

#define HE_SIG_A_MU_DL_INFO_CP_LTF_SIZE_OFFSET                                      0x00000000
#define HE_SIG_A_MU_DL_INFO_CP_LTF_SIZE_LSB                                         23
#define HE_SIG_A_MU_DL_INFO_CP_LTF_SIZE_MSB                                         24
#define HE_SIG_A_MU_DL_INFO_CP_LTF_SIZE_MASK                                        0x01800000


/* Description		DOPPLER_INDICATION

			0: No Doppler support
			1: Doppler support
			<legal all>
*/

#define HE_SIG_A_MU_DL_INFO_DOPPLER_INDICATION_OFFSET                               0x00000000
#define HE_SIG_A_MU_DL_INFO_DOPPLER_INDICATION_LSB                                  25
#define HE_SIG_A_MU_DL_INFO_DOPPLER_INDICATION_MSB                                  25
#define HE_SIG_A_MU_DL_INFO_DOPPLER_INDICATION_MASK                                 0x02000000


/* Description		RESERVED_0A

			<legal 0>
*/

#define HE_SIG_A_MU_DL_INFO_RESERVED_0A_OFFSET                                      0x00000000
#define HE_SIG_A_MU_DL_INFO_RESERVED_0A_LSB                                         26
#define HE_SIG_A_MU_DL_INFO_RESERVED_0A_MSB                                         31
#define HE_SIG_A_MU_DL_INFO_RESERVED_0A_MASK                                        0xfc000000


/* Description		TXOP_DURATION

			Indicates the remaining time in the current TXOP
			
			Field Used by MAC HW
			 <legal all>
*/

#define HE_SIG_A_MU_DL_INFO_TXOP_DURATION_OFFSET                                    0x00000004
#define HE_SIG_A_MU_DL_INFO_TXOP_DURATION_LSB                                       0
#define HE_SIG_A_MU_DL_INFO_TXOP_DURATION_MSB                                       6
#define HE_SIG_A_MU_DL_INFO_TXOP_DURATION_MASK                                      0x0000007f



#define HE_SIG_A_MU_DL_INFO_RESERVED_1A_OFFSET                                      0x00000004
#define HE_SIG_A_MU_DL_INFO_RESERVED_1A_LSB                                         7
#define HE_SIG_A_MU_DL_INFO_RESERVED_1A_MSB                                         7
#define HE_SIG_A_MU_DL_INFO_RESERVED_1A_MASK                                        0x00000080


/* Description		NUM_LTF_SYMBOLS

			Indicates the number of HE-LTF symbols
			
			0: 1 LTF
			1: 2 LTFs
			2: 4 LTFs
			3: 6 LTFs
			4: 8 LTFs
			
			<legal all>
*/

#define HE_SIG_A_MU_DL_INFO_NUM_LTF_SYMBOLS_OFFSET                                  0x00000004
#define HE_SIG_A_MU_DL_INFO_NUM_LTF_SYMBOLS_LSB                                     8
#define HE_SIG_A_MU_DL_INFO_NUM_LTF_SYMBOLS_MSB                                     10
#define HE_SIG_A_MU_DL_INFO_NUM_LTF_SYMBOLS_MASK                                    0x00000700


/* Description		LDPC_EXTRA_SYMBOL

			If LDPC, 
			  0: LDPC extra symbol not present
			  1: LDPC extra symbol present
			Else 
			  Set to 1
			<legal all>
*/

#define HE_SIG_A_MU_DL_INFO_LDPC_EXTRA_SYMBOL_OFFSET                                0x00000004
#define HE_SIG_A_MU_DL_INFO_LDPC_EXTRA_SYMBOL_LSB                                   11
#define HE_SIG_A_MU_DL_INFO_LDPC_EXTRA_SYMBOL_MSB                                   11
#define HE_SIG_A_MU_DL_INFO_LDPC_EXTRA_SYMBOL_MASK                                  0x00000800


/* Description		STBC

			Indicates whether STBC is applied
			0: No STBC
			1: STBC
			<legal all>
*/

#define HE_SIG_A_MU_DL_INFO_STBC_OFFSET                                             0x00000004
#define HE_SIG_A_MU_DL_INFO_STBC_LSB                                                12
#define HE_SIG_A_MU_DL_INFO_STBC_MSB                                                12
#define HE_SIG_A_MU_DL_INFO_STBC_MASK                                               0x00001000


/* Description		PACKET_EXTENSION_A_FACTOR

			the packet extension duration of the trigger-based PPDU 
			response with these two bits indicating the "a-factor" 
			
			<enum 0 a_factor_4>
			<enum 1 a_factor_1>
			<enum 2 a_factor_2>
			<enum 3 a_factor_3>
			
			<legal all>
*/

#define HE_SIG_A_MU_DL_INFO_PACKET_EXTENSION_A_FACTOR_OFFSET                        0x00000004
#define HE_SIG_A_MU_DL_INFO_PACKET_EXTENSION_A_FACTOR_LSB                           13
#define HE_SIG_A_MU_DL_INFO_PACKET_EXTENSION_A_FACTOR_MSB                           14
#define HE_SIG_A_MU_DL_INFO_PACKET_EXTENSION_A_FACTOR_MASK                          0x00006000


/* Description		PACKET_EXTENSION_PE_DISAMBIGUITY

			the packet extension duration of the trigger-based PPDU 
			response with this bit indicating the PE-Disambiguity 
			<legal all>
*/

#define HE_SIG_A_MU_DL_INFO_PACKET_EXTENSION_PE_DISAMBIGUITY_OFFSET                 0x00000004
#define HE_SIG_A_MU_DL_INFO_PACKET_EXTENSION_PE_DISAMBIGUITY_LSB                    15
#define HE_SIG_A_MU_DL_INFO_PACKET_EXTENSION_PE_DISAMBIGUITY_MSB                    15
#define HE_SIG_A_MU_DL_INFO_PACKET_EXTENSION_PE_DISAMBIGUITY_MASK                   0x00008000


/* Description		CRC

			CRC for HE-SIG-A contents.
			<legal all>
*/

#define HE_SIG_A_MU_DL_INFO_CRC_OFFSET                                              0x00000004
#define HE_SIG_A_MU_DL_INFO_CRC_LSB                                                 16
#define HE_SIG_A_MU_DL_INFO_CRC_MSB                                                 19
#define HE_SIG_A_MU_DL_INFO_CRC_MASK                                                0x000f0000


/* Description		TAIL

			<legal 0>
*/

#define HE_SIG_A_MU_DL_INFO_TAIL_OFFSET                                             0x00000004
#define HE_SIG_A_MU_DL_INFO_TAIL_LSB                                                20
#define HE_SIG_A_MU_DL_INFO_TAIL_MSB                                                25
#define HE_SIG_A_MU_DL_INFO_TAIL_MASK                                               0x03f00000


/* Description		RESERVED_1B

			<legal 0>
*/

#define HE_SIG_A_MU_DL_INFO_RESERVED_1B_OFFSET                                      0x00000004
#define HE_SIG_A_MU_DL_INFO_RESERVED_1B_LSB                                         26
#define HE_SIG_A_MU_DL_INFO_RESERVED_1B_MSB                                         30
#define HE_SIG_A_MU_DL_INFO_RESERVED_1B_MASK                                        0x7c000000


/* Description		RX_INTEGRITY_CHECK_PASSED

			TX side: Set to 0
			RX side: Set to 1 if PHY determines the HE-SIG-A CRC check
			 has passed, else set to 0
			
			<legal all>
*/

#define HE_SIG_A_MU_DL_INFO_RX_INTEGRITY_CHECK_PASSED_OFFSET                        0x00000004
#define HE_SIG_A_MU_DL_INFO_RX_INTEGRITY_CHECK_PASSED_LSB                           31
#define HE_SIG_A_MU_DL_INFO_RX_INTEGRITY_CHECK_PASSED_MSB                           31
#define HE_SIG_A_MU_DL_INFO_RX_INTEGRITY_CHECK_PASSED_MASK                          0x80000000



#endif   // HE_SIG_A_MU_DL_INFO
