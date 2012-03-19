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

#ifndef __NET_H__
#define __NET_H__

#if defined(DEVICE_IPC_V4)
#include "device/ipc-v4/net.h"
#elif defined(DEVICE_H1)
#include "device/h1/net.h"
#endif

#define IPC_NET_PREF_PLMN                                           0x0801
#define IPC_NET_PLMN_SEL                                            0x0802
#define IPC_NET_CURRENT_PLMN                                        0x0803
#define IPC_NET_PLMN_LIST                                           0x0804
#define IPC_NET_REGIST                                              0x0805
#define IPC_NET_SUBSCRIBER_NUM                                      0x0806
#define IPC_NET_BAND_SEL                                            0x0807
#define IPC_NET_SERVICE_DOMAIN_CONFIG                               0x0808
#define IPC_NET_POWERON_ATTACH                                      0x0809
#define IPC_NET_MODE_SEL                                            0x080A
#define IPC_NET_ACQ_ORDER                                           0x080B
#define IPC_NET_IDENTITY                                            0x080C
#define IPC_NET_CURRENT_RRC_STATUS                                  0x080D

#define IPC_NET_PLMN_STATUS_AVAILABLE                               0x02
#define IPC_NET_PLMN_STATUS_CURRENT                                 0x03
#define IPC_NET_PLMN_STATUS_FORBIDDEN                               0x04

#define IPC_NET_PLMN_SEL_MANUAL                                     0x03
#define IPC_NET_PLMN_SEL_AUTO                                       0x02

#define IPC_NET_REGISTRATION_STATE_NONE                             0x01
#define IPC_NET_REGISTRATION_STATE_HOME                             0x02
#define IPC_NET_REGISTRATION_STATE_SEARCHING                        0x03
#define IPC_NET_REGISTRATION_STATE_EMERGENCY                        0x04
#define IPC_NET_REGISTRATION_STATE_UNKNOWN                          0x05
#define IPC_NET_REGISTRATION_STATE_ROAMING                          0x06

#define IPC_NET_SERVICE_DOMAIN_GSM                                  0x02
#define IPC_NET_SERVICE_DOMAIN_GPRS                                 0x03

#define IPC_NET_MODE_SEL_GSM_UMTS                                   0x01
#define IPC_NET_MODE_SEL_GSM_ONLY                                   0x02
#define IPC_NET_MODE_SEL_UMTS_ONLY                                  0x03

struct ipc_net_regist_get {
    unsigned char net;
    unsigned char domain;
} __attribute__((__packed__));

struct ipc_net_regist {
    unsigned char act; // IPC_NET_ACCESS_TECHNOLOGY_...
    unsigned char domain; // IPC_NET_SERVICE_DOMAIN_...
    unsigned char reg_state; // IPC_NET_REGISTRATION_STATE_...
    unsigned char edge;
    unsigned short lac;
    unsigned int cid;
    char rej_cause;
} __attribute__((__packed__));

struct ipc_net_plmn_entry {
    unsigned char status; // IPC_NET_PLMN_STATUS_...
    char plmn[6];
    unsigned char type;
    char unk[2];
} __attribute__((__packed__));

struct ipc_net_plmn_entries {
    unsigned char num;
} __attribute__((__packed__));

struct ipc_net_mode_sel {
    unsigned char mode_sel;
} __attribute__((__packed__));

struct ipc_net_plmn_sel_get {
    unsigned char plmn_sel;
} __attribute__((__packed__));

struct ipc_net_plmn_sel_set {
    unsigned char mode;
    char plmn[6]; // 5 plmn bytes + 1 '#' byte
    unsigned char act; // IPC_NET_ACCESS_TECHNOLOGY_...
} __attribute__((__packed__));

void ipc_net_regist_setup(struct ipc_net_regist_get *message, unsigned char domain);
void ipc_net_plmn_sel_setup(struct ipc_net_plmn_sel_set *message, unsigned char mode, char *plmn, unsigned char act);

#endif

// vim:ts=4:sw=4:expandtab
