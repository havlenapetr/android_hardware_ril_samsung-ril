/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com
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

#include <string.h>
#include <radio.h>

void ipc_net_regist_setup(struct ipc_net_regist_get *message, unsigned char domain)
{
    //FIXME: could that be IPC_NET_ACCESS_TECHNOLOGY_... (act) ?
    message->net = 0xff;
    message->domain = domain;
}

void ipc_net_plmn_sel_setup(struct ipc_net_plmn_sel_set *message, unsigned char mode, char *plmn, unsigned char act)
{
    int message_plmn_len = sizeof(message->plmn) / sizeof(char);
    int plmn_len;
    int i;

    memset(message, 0, sizeof(struct ipc_net_plmn_sel_set));

    if (mode == IPC_NET_PLMN_SEL_AUTO)
    {
        message->mode = IPC_NET_PLMN_SEL_AUTO;
        message->act = IPC_NET_ACCESS_TECHNOLOGY_UNKNOWN;
    }
    else if (mode == IPC_NET_PLMN_SEL_MANUAL)
    {
        plmn_len = strlen(plmn);

        // Only copy the first (6) bytes if there are more
        if(plmn_len > message_plmn_len)
            plmn_len = message_plmn_len;

        strncpy(message->plmn, plmn, plmn_len);

        // If there are less (5 is the usual case) PLMN bytes, fill the rest with '#'
        if (plmn_len < message_plmn_len)
            memset((void*) (message->plmn + plmn_len), '#', message_plmn_len - plmn_len);

        message->mode = IPC_NET_PLMN_SEL_MANUAL;
        message->act = act;
    }
}

// vim:ts=4:sw=4:expandtab
