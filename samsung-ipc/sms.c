/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2011 Simon Busch <morphis@gravedo.de>
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

#include <radio.h>
#include <string.h>
#include <assert.h>

unsigned char* ipc_sms_send_msg_pack(struct ipc_sms_send_msg *msg, char *smsc,
                                     unsigned char *pdu, int pdu_length)
{
    unsigned char *data = NULL, *p = NULL;
    unsigned int data_length = 0, smsc_len = 0;

    assert(smsc != NULL);
    assert(pdu != NULL);

    smsc_len = strlen(smsc);
    data_length = smsc_len + pdu_length + sizeof(struct ipc_sms_send_msg);
    data = (unsigned char*) malloc(sizeof(unsigned char) * data_length);
    memset(data, 0, data_length);

    p = data;
    memcpy(p, &msg, sizeof(struct ipc_sms_send_msg));
    p += sizeof(struct ipc_sms_send_msg);
    memcpy(p, (char*) (smsc + 1), smsc_len);
    p += smsc_len;
    memcpy(p, pdu, pdu_length);

    return data;
}


