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

#ifndef __MISC_H__
#define __MISC_H__

#if defined(DEVICE_IPC_V4)
#include "device/ipc-v4/misc.h"
#elif defined(DEVICE_H1)
#include "device/h1/misc.h"
#endif

struct ipc_message_info;

#define IPC_MISC_ME_VERSION             0x0A01
#define IPC_MISC_ME_IMSI                0x0A02
#define IPC_MISC_ME_SN                  0x0A03
#define IPC_MISC_TIME_INFO              0x0A07

#define IPC_MISC_ME_SN_SERIAL_NUM                   0x01
#define IPC_MISC_ME_SN_SERIAL_NUM_SERIAL            0x04
#define IPC_MISC_ME_SN_SERIAL_NUM_MANUFACTURE_DATE  0x05
#define IPC_MISC_ME_SN_SERIAL_NUM_BARCODE           0x06

struct ipc_misc_time_info {
    unsigned char tz_valid, daylight_valid;
    unsigned char year, mon, day;
    unsigned char hour, min, sec;
    unsigned char tz, dl, dv;
    char plmn[6];
} __attribute__((__packed__));

char* ipc_misc_me_imsi_response_get_imsi(struct ipc_message_info *response);

#endif

// vim:ts=4:sw=4:expandtab
