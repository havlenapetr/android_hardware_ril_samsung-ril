/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
 *
 * libsamsung-ipc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libsamsung-ipc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libsamsung-ipc.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __CALL_H__
#define __CALL_H__

#if defined(DEVICE_IPC_V4)
#include "device/ipc-v4/call.h"
#elif defined(DEVICE_H1)
#include "device/h1/call.h"
#endif

/* Message types */
#define IPC_CALL_OUTGOING               0x0201
#define IPC_CALL_INCOMING               0x0202
#define IPC_CALL_RELEASE                0x0203
#define IPC_CALL_ANSWER                 0x0204
#define IPC_CALL_STATUS                 0x0205
#define IPC_CALL_LIST                   0x0206
#define IPC_CALL_BURST_DTMF             0x0207
#define IPC_CALL_CONT_DTMF              0x0208
#define IPC_CALL_WAITING                0x0209
#define IPC_CALL_LINE_ID                0x020A

/* Enum values */
#define IPC_CALL_TYPE_VOICE             0x01
#define IPC_CALL_TYPE_DATA              0x03

#define IPC_CALL_IDENTITY_DEFAULT           0x00
#define IPC_CALL_IDENTITY_HIDE              0x01
#define IPC_CALL_IDENTITY_SHOW              0x02

#define IPC_CALL_PREFIX_NONE                0x00
#define IPC_CALL_PREFIX_INTL                0x11

/* Only for ipc_call_status, NOT call_list */
#define IPC_CALL_STATE_DIALING                      0x01
#define IPC_CALL_STATE_IGNORING_INCOMING_STATUS     0x02
#define IPC_CALL_STATE_CONNECTED                    0x03
#define IPC_CALL_STATE_RELEASED                     0x04
#define IPC_CALL_STATE_CONNECTING                   0x05

#define IPC_CALL_LIST_ENTRY_STATE_ACTIVE            0x01
#define IPC_CALL_LIST_ENTRY_STATE_HOLDING           0x02
#define IPC_CALL_LIST_ENTRY_STATE_DIALING           0x03
#define IPC_CALL_LIST_ENTRY_STATE_ALERTING          0x04
#define IPC_CALL_LIST_ENTRY_STATE_INCOMING          0x05
#define IPC_CALL_LIST_ENTRY_STATE_WAITING           0x06

#define IPC_CALL_TERM_MO                0x01
#define IPC_CALL_TERM_MT                0x02

#define IPC_CALL_DTMF_STATE_START       0x01
#define IPC_CALL_DTMF_STATE_STOP        0x02

struct ipc_message_info;

struct ipc_call_cont_dtmf {
    unsigned char state;
    unsigned char tone;
} __attribute__((__packed__));

void ipc_call_outgoing_setup(struct ipc_call_outgoing *message, unsigned char type,
                             unsigned char identity, unsigned char prefix, char *number);

unsigned int ipc_call_list_response_get_num_entries(struct ipc_message_info *response);
struct ipc_call_list_entry* ipc_call_list_response_get_entry(struct ipc_message_info *response, unsigned int num);
char* ipc_call_list_response_get_entry_number(struct ipc_message_info *response, unsigned int num);
unsigned char* ipc_call_cont_dtmf_burst_pack(struct ipc_call_cont_dtmf *message, unsigned char *burst, int burst_len);

#endif

// vim:ts=4:sw=4:expandtab
