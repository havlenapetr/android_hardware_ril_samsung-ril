/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2011 Paul Kocialkowski <contact@paulk.fr>
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

#ifndef __DEVICE_IPC_V4_SMS_H__
#define __DEVICE_IPC_V4_SMS_H__

#define IPC_SMS_ACK_NO_ERROR            0x0000
#define IPC_SMS_ACK_PDA_FULL_ERROR      0x8080
#define IPC_SMS_ACK_MALFORMED_REQ_ERROR 0x8061
#define IPC_SMS_ACK_UNSPEC_ERROR        0x806F

struct ipc_sms_incoming_msg {
    unsigned char msg_type;
    unsigned char type;
    unsigned short sim_index;
    unsigned char msg_tpid;
    unsigned char length;
} __attribute__((__packed__));

/*
 * This is followed by:
 * smsc_string (variable length, 1st byte is length)
 * pdu (variable length)
 */
struct ipc_sms_send_msg {
    unsigned char type;
    unsigned char msg_type;
    unsigned char unk;
    unsigned char length;
    unsigned char smsc_len;
} __attribute__((__packed__));

struct ipc_sms_deliv_report_msg {
    unsigned char type;
    unsigned short error;
    unsigned char msg_tpid;
    unsigned char unk;
} __attribute__((__packed__));

#endif

// vim:ts=4:sw=4:expandtab
