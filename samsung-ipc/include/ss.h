/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
 * Copyright (C) 2012 Paul Kocialkowski <contact@oaulk.fr>
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

#ifndef __SS_H__
#define __SS_H__

#define IPC_SS_WAITING                              0x0C01
#define IPC_SS_CLI                                  0x0C02
#define IPC_SS_BARRING                              0x0C03
#define IPC_SS_BARRING_PW                           0x0C04
#define IPC_SS_FORWARDING                           0x0C05
#define IPC_SS_INFO                                 0x0C06
#define IPC_SS_MANAGE_CALL                          0x0C07
#define IPC_SS_USSD                                 0x0C08
#define IPC_SS_AOC                                  0x0C09
#define IPC_SS_RELEASE_COMPLETE                     0x0C0A

#define IPC_SS_USSD_NO_ACTION_REQUIRE               0x01
#define IPC_SS_USSD_ACTION_REQUIRE                  0x02
#define IPC_SS_USSD_TERMINATED_BY_NET               0x03
#define IPC_SS_USSD_OTHER_CLIENT                    0x04 //guess
#define IPC_SS_USSD_NOT_SUPPORT                     0x05 //guess
#define IPC_SS_USSD_TIME_OUT                        0x06 //guess

/*
 * This is followed by the encoded (according to the dcs) bytes of the USSD message.
 */
struct ipc_ss_ussd {
    unsigned char state;
    unsigned char dcs;
    unsigned char length;
} __attribute__((__packed__));

#endif

// vim:ts=4:sw=4:expandtab
