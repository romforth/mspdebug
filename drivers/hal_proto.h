/* MSPDebug - debugging tool for MSP430 MCUs
 * Copyright (C) 2009-2013 Daniel Beer
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef HAL_PROTO_H_
#define HAL_PROTO_H_

#include <stdint.h>
#include <stddef.h>
#include "transport.h"

/* Low-level HAL message types */
typedef enum {
	HAL_PROTO_TYPE_UP_INIT			= 0x51,
	HAL_PROTO_TYPE_UP_ERASE			= 0x52,
	HAL_PROTO_TYPE_UP_WRITE			= 0x53,
	HAL_PROTO_TYPE_UP_READ			= 0x54,
	HAL_PROTO_TYPE_UP_CORE			= 0x55,
	HAL_PROTO_TYPE_DCDC_CALIBRATE		= 0x56,
	HAL_PROTO_TYPE_DCDC_INIT_INTERFACE	= 0x57,
	HAL_PROTO_TYPE_DCDC_SUB_MCU_VERSION	= 0x58,
	HAL_PROTO_TYPE_DCDC_LAYER_VERSION	= 0x59,
	HAL_PROTO_TYPE_DCDC_POWER_DOWN		= 0x60,
	HAL_PROTO_TYPE_DCDC_SET_VCC		= 0x61,
	HAL_PROTO_TYPE_DCDC_RESTART		= 0x62,
	HAL_PROTO_TYPE_CORE_SET_VCC		= 0x63,
	HAL_PROTO_TYPE_CORE_GET_VCC		= 0x64,
	HAL_PROTO_TYPE_CORE_SWITCH_FET		= 0x65,
	HAL_PROTO_TYPE_CMP_VERSIONS		= 0x66,

	HAL_PROTO_TYPE_CMD_LEGACY		= 0x7e,
	HAL_PROTO_TYPE_CMD_SYNC			= 0x80,
	HAL_PROTO_TYPE_CMD_EXECUTE		= 0x81,
	HAL_PROTO_TYPE_CMD_EXECUTE_LOOP		= 0x82,
	HAL_PROTO_TYPE_CMD_LOAD			= 0x83,
	HAL_PROTO_TYPE_CMD_LOAD_CONTINUED	= 0x84,
	HAL_PROTO_TYPE_CMD_DATA			= 0x85,
	HAL_PROTO_TYPE_CMD_KILL			= 0x86,
	HAL_PROTO_TYPE_CMD_MOVE			= 0x87,
	HAL_PROTO_TYPE_CMD_UNLOAD		= 0x88,
	HAL_PROTO_TYPE_CMD_BYPASS		= 0x89,
	HAL_PROTO_TYPE_CMD_EXECUTE_LOOP_CONT	= 0x8a,
	HAL_PROTO_TYPE_CMD_COM_RESET		= 0x8b,
	HAL_PROTO_TYPE_CMD_PAUSE_LOOP		= 0x8c,
	HAL_PROTO_TYPE_CMD_RESUME_LOOP		= 0x8d,
	HAL_PROTO_TYPE_CMD_KILL_ALL		= 0x8e,
	HAL_PROTO_TYPE_CMD_OVER_CURRENT		= 0x8f,

	HAL_PROTO_TYPE_ACKNOWLEDGE		= 0x91,
	HAL_PROTO_TYPE_EXCEPTION		= 0x92,
	HAL_PROTO_TYPE_DATA			= 0x93,
	HAL_PROTO_TYPE_DATA_REQUEST		= 0x94,
	HAL_PROTO_TYPE_STATUS			= 0x95
} hal_proto_type_t;

typedef enum {
	HAL_PROTO_CHECKSUM	= 0x01
} hal_proto_flags_t;

typedef enum {
	HAL_PROTO_ERR_NONE	= 0x00,
	HAL_PROTO_ERR_UNDEFINED	= 0xffff,

	HAL_PROTO_ERR_EXECUTE_FUNCLET_NO_RAM_START	= 0xFFFE,
	HAL_PROTO_ERR_EXECUTE_FUNCLET_NO_RAM_SIZE	= 0xFFFD,
	HAL_PROTO_ERR_EXECUTE_FUNCLET_NO_OFFSET		= 0xFFFC,
	HAL_PROTO_ERR_EXECUTE_FUNCLET_NO_ADDRESS	= 0xFFFB,
	HAL_PROTO_ERR_EXECUTE_FUNCLET_NO_LENGTH		= 0xFFFA,
	HAL_PROTO_ERR_EXECUTE_FUNCLET_NO_TYPE		= 0xFFF9,
	HAL_PROTO_ERR_EXECUTE_FUNCLET_NO_LOCKA		= 0xFFF8,
	HAL_PROTO_ERR_EXECUTE_FUNCLET_EXECUTION_TIMEOUT	= 0xFFF7,
	HAL_PROTO_ERR_EXECUTE_FUNCLET_EXECUTION_ERROR	= 0xFFF6,
+
	HAL_PROTO_ERR_WRITE_MEM_WORD_NO_RAM_ADDRESS	= 0xFFF5,
	HAL_PROTO_ERR_WRITE_MEM_WORD_NO_RAM_SIZE	= 0xFFF4,
	HAL_PROTO_ERR_WRITE_MEM_WORD_UNKNOWN		= 0xFFF3,
+
	HAL_PROTO_ERR_WRITE_MEM_BYTES_NO_RAM_ADDRESS	= 0xFFF2,
	HAL_PROTO_ERR_WRITE_MEM_BYTES_NO_RAM_SIZE	= 0xFFF1,
	HAL_PROTO_ERR_WRITE_MEM_BYTES_UNKNOWN		= 0xFFF0,
+
	HAL_PROTO_ERR_WRITE_FLASH_WORD_NO_FLASH_ADDRESS	= 0xFFEF,
	HAL_PROTO_ERR_WRITE_FLASH_WORD_NO_FLASH_SIZE	= 0xFFEE,
	HAL_PROTO_ERR_WRITE_FLASH_WORD_UNKNOWN		= 0xFFED,
+
	HAL_PROTO_ERR_WRITE_FLASH_QUICK_UNKNOWN		= 0xFFEC,
+
	HAL_PROTO_ERR_START_JTAG_NO_PROTOCOL		= 0xFFEB,
	HAL_PROTO_ERR_START_JTAG_PROTOCOL_UNKNOWN	= 0xFFEA,
+
	HAL_PROTO_ERR_SET_CHAIN_CONFIGURATION_STREAM	= 0xFFE9,
+
	HAL_PROTO_ERR_RESTORECONTEXT_RELEASE_JTAG_NO_WDT_ADDRESS	= 0xFFE8,
	HAL_PROTO_ERR_RESTORECONTEXT_RELEASE_JTAG_NO_WDT_VALUE		= 0xFFE7,
	HAL_PROTO_ERR_RESTORECONTEXT_RELEASE_JTAG_NO_PC			= 0xFFE6,
	HAL_PROTO_ERR_RESTORECONTEXT_RELEASE_JTAG_NO_SR			= 0xFFE5,
	HAL_PROTO_ERR_RESTORECONTEXT_RELEASE_JTAG_NO_CONTROL_MASK	= 0xFFE4,
	HAL_PROTO_ERR_RESTORECONTEXT_RELEASE_JTAG_NO_MDB		= 0xFFE3,
+
	HAL_PROTO_ERR_READ_MEM_WORD_NO_ADDRESS	= 0xFFF2,
	HAL_PROTO_ERR_READ_MEM_WORD_NO_SIZE	= 0xFFF1,
+
	HAL_PROTO_ERR_READ_MEM_UNKNOWN		= 0xFFE0,
+
	HAL_PROTO_ERR_READ_MEM_BYTES_NO_ADDRESS	= 0xFFDF,
	HAL_PROTO_ERR_READ_MEM_BYTES_NO_SIZE	= 0xFFDE,
+
	HAL_PROTO_ERR_PSA_NO_ADDRESS		= 0xFFDD,
	HAL_PROTO_ERR_PSA_NO_SIZE		= 0xFFDC,
+
	HAL_PROTO_ERR_SYNC_JTAG_ASSERT_POR_JTAG_TIMEOUT		= 0xFFDB,
	HAL_PROTO_ERR_SYNC_JTAG_ASSERT_POR_NO_WDT_ADDRESS	= 0xFFDA,
	HAL_PROTO_ERR_SYNC_JTAG_ASSERT_POR_NO_WDT_VALUE		= 0xFFD9,
+
	HAL_PROTO_ERR_WRITE_ALL_CPU_REGISTERS_STREAM	= 0xFFD8,
+
	HAL_PROTO_ERR_WRITE_MEM_WORD_XV2_NO_RAM_ADDRESS	= 0xFFD7,
	HAL_PROTO_ERR_WRITE_MEM_WORD_XV2_NO_RAM_SIZE	= 0xFFD6,
+
	HAL_PROTO_ERR_SECURE_NO_TGT_HAS_TEST_PIN	= 0xFFD5,
+
	HAL_PROTO_ERR_SYNC_JTAG_CONDITIONAL_JTAG_TIMEOUT	= 0xFFD4,
	HAL_PROTO_ERR_SYNC_JTAG_CONDITIONAL_NO_WDT_ADDRESS	= 0xFFD3,
	HAL_PROTO_ERR_SYNC_JTAG_CONDITIONAL_NO_WDT_VALUE	= 0xFFD2,
+
	HAL_PROTO_ERR_INSTRUCTION_BOUNDARY_ERROR	= 0xFFD1,
	HAL_PROTO_ERR_JTAG_VERSION_MISMATCH		= 0xFFD0,
+
	HAL_PROTO_ERR_JTAG_MAILBOX_IN_TIMOUT		= 0xFFCF,
	HAL_PROTO_ERR_JTAG_PASSWORD_WRONG		= 0xFFCE,
+
	HAL_PROTO_ERR_START_JTAG_NO_ACTIVATION_CODE	= 0xFFCD,
	HAL_PROTO_ERR_SINGLESTEP_WAITFOREEM_TIMEOUT	= 0xFFCC,
+
	HAL_PROTO_ERR_CONFIG_NO_PARAMETER		= 0xFFCB,
	HAL_PROTO_ERR_CONFIG_NO_VALUE			= 0xFFCA,
	HAL_PROTO_ERR_CONFIG_PARAM_UNKNOWN_PARAMETER	= 0xFFC9,
+
	HAL_PROTO_ERR_NO_NUM_BITS			= 0xFFC8,
	HAL_PROTO_ERR_ARRAY_SIZE_MISMATCH		= 0xFFC7,
+
	HAL_PROTO_ERR_NO_COMMAND			= 0xFFC6,
	HAL_PROTO_ERR_UNKNOWN_COMMAND			= 0xFFC5,
	HAL_PROTO_ERR_NO_DATA				= 0xFFC4,
	HAL_PROTO_ERR_NO_BIT_SIZE			= 0xFFC3,
	HAL_PROTO_ERR_INVALID_BIT_SIZE			= 0xFFC2,
+
	HAL_PROTO_ERR_UNLOCK_NO_PASSWORD_LENGTH		= 0xFFC1,
	HAL_PROTO_ERR_UNLOCK_INVALID_PASSWORD_LENGTH	= 0xFFC0,
+
	HAL_PROTO_ERR_EXECUTE_FUNCLET_FINISH_TIMEOUT	= 0xFFBF,
+
	HAL_PROTO_ERR_EXECUTE_FUNCLET_NO_MAXRSEL	= 0xFFBE,
+
	HAL_PROTO_ERR_API_CALL_NOT_SUPPORTED		= 0xFFBD,
+
	HAL_PROTO_ERR_MAGIC_PATTERN			= 0xFFBC,
	HAL_PROTO_ERR_MAGIC_PATTERN_BOOT_DATA_CRC_WRONG	= 0xFFBB,
	HAL_PROTO_ERR_DAP_NACK				= 0xFFBA,
+
	HAL_PROTO_MESSAGE_NO_RESPONSE		= 0x8000,
	HAL_PROTO_EXCEPTION_NOT_IMPLEMENT_ERR	= 0x8001,
	HAL_PROTO_EXCEPTION_MSGID_ERR		= 0x8002,
	HAL_PROTO_EXCEPTION_CRC_ERR		= 0x8003,
	HAL_PROTO_EXCEPTION_RX_TIMEOUT_ERR	= 0x8004,
	HAL_PROTO_EXCEPTION_TX_TIMEOUT_ERR	= 0x8005,
	HAL_PROTO_EXCEPTION_RX_OVERFLOW_ERR	= 0x8006,
	HAL_PROTO_EXCEPTION_TX_NO_BUFFER	= 0x8007,
	HAL_PROTO_EXCEPTION_COM_RESET		= 0x8008,
	HAL_PROTO_EXCEPTION_RX_NO_BUFFER	= 0x8009,
	HAL_PROTO_EXCEPTION_RX_TO_SMALL_BUFFER	= 0x800A,
	HAL_PROTO_EXCEPTION_RX_LENGTH		= 0x800B,
} hal_proto_error_t;

#define HAL_MAX_PAYLOAD		253

struct hal_proto {
	transport_t		trans;
	hal_proto_flags_t	flags;
	uint8_t			ref_id;

	/* Receive parameters */
	hal_proto_type_t	type;
	uint8_t			ref;
	uint8_t			seq;

	/* Execute data */
	int			length;
	uint8_t			payload[4096];
};

/* Initialize a HAL protocol interpreter */
void hal_proto_init(struct hal_proto *p, transport_t trans,
		    hal_proto_flags_t flags);

/* Send a low-level HAL command */
int hal_proto_send(struct hal_proto *p, hal_proto_type_t type,
		   const uint8_t *data, int length);

/* Receive a low-level HAL response */
int hal_proto_receive(struct hal_proto *p, uint8_t *buf, int max_len);

/* Execute a high-level function. The reply data is kept in the payload
 * buffer.
 */
int hal_proto_execute(struct hal_proto *p, uint8_t fid,
		      const uint8_t *data, int len);

#endif
