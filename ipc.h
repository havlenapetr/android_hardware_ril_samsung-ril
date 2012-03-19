/**
 * This file is part of samsung-ril.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
 * Copyright (C) 2011 Paul Kocialkowski <contact@oaulk.fr>
 *
 * samsung-ril is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * samsung-ril is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with samsung-ril.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _SAMSUNG_RIL_IPC_H_
#define _SAMSUNG_RIL_IPC_H_

#include "samsung-ril.h"

#define ipc_fmt_send_get(command, mseq) \
	ipc_fmt_send(command, IPC_TYPE_GET, NULL, 0, mseq)

#define ipc_fmt_send_set(command, mseq, data, length) \
	ipc_fmt_send(command, IPC_TYPE_SET, data, length, mseq)

#define ipc_fmt_send_exec(command, mseq) \
	ipc_fmt_send(command, IPC_TYPE_EXEC, NULL, 0, mseq)

struct ipc_client_object {
	struct ipc_client *ipc_client;
	int ipc_client_fd;
};

extern struct ril_client_funcs ipc_fmt_client_funcs;
extern struct ril_client_funcs ipc_rfs_client_funcs;

void ipc_fmt_send(const unsigned short command, const char type, unsigned char *data, const int length, unsigned char mseq);

#endif
