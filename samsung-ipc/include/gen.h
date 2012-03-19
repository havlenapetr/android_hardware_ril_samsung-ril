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

#ifndef __GEN_H__
#define __GEN_H__

#if defined(DEVICE_IPC_V4)
#include "device/ipc-v4/gen.h"
#elif defined(DEVICE_H1)
#include "device/h1/gen.h"
#endif

#define IPC_GEN_PHONE_RES               0x8001

int ipc_gen_phone_res_check(struct ipc_gen_phone_res *res);

#endif

// vim:ts=4:sw=4:expandtab
