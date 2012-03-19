/**
 * This file is part of samsung-ril.
 *
 * Copyright (C) 2010-2011 Joerie de Gram <j.de.gram@gmail.com>
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

#include <stdio.h>
#include <string.h>

#define LOG_TAG "RIL-UTIL"
#include <utils/Log.h>

/**
 * Converts a hexidecimal string to binary
 */
void hex2bin(const char *data, int length, unsigned char *buf)
{
	int i = 0;
	char b = 0;
	unsigned char *p = buf;

	length ^= 0x01;

	while(i < length) {
		b = 0;

		if(data[i] - '0' < 10)
			b = data[i] - '0';
		else if(data[i] - 'a' < 7)
			b = data[i] - 'a' + 10;
		else if(data[i] - 'A' < 7)
			b = data[i] - 'A' + 10;
		i++;

		b = (b << 4);

		if(data[i] - '0' < 10)
			b |= data[i] - '0';
		else if(data[i] - 'a' < 7)
			b |= data[i] - 'a' + 10;
		else if(data[i] - 'A' < 7)
			b |= data[i] - 'A' + 10;
		i++;

		*p++ = b;
	}
}

/**
 * Converts binary data to a hexidecimal string
 */
void bin2hex(const unsigned char *data, int length, char *buf)
{
	int i;
	char b;
	char *p = buf;

	for(i = 0; i < length; i++) {
		b = 0;

		b = (data[i] >> 4 & 0x0f);
		b += (b < 10) ? '0' : ('a' - 10);
		*p++ = b;

		b = (data[i] & 0x0f);
		b += (b < 10) ? '0' : ('a' - 10);
		*p++ = b;
	}

	*p = '\0';
}

/**
 * Converts GSM7 (8 bits) data to ASCII (7 bits)
 */
int gsm72ascii(unsigned char *data, char **data_dec, int length)
{
	int t, u, d, o = 0;
	int i;

	int dec_length;
	char *dec;

	dec_length = ((length * 8) - ((length * 8) % 7) ) / 7;
	dec = malloc(dec_length);

	memset(dec, 0, dec_length);

	for(i=0 ; i < length ; i++)
	{
		d = 7 - i % 7;
		if(d == 7 && i != 0)
			o++;

		t = (data[i] - (((data[i] >> d) & 0xff) << d));
		u = (data[i] >> d) & 0xff;

		dec[i+o]+=t << (i + o) % 8;

		if(u)
			dec[i+1+o]+=u;
	}

	*data_dec = dec;
	
	return dec_length;
}

/**
 * Converts ASCII (7 bits) data to GSM7 (8 bits)
 */
int ascii2gsm7(char *data, unsigned char **data_enc, int length)
{
	int d_off, d_pos, a_off, a_pos = 0;
	int i;

	int enc_length;
	unsigned char *enc;

	enc_length = ((length * 7) - (length * 7) % 8) / 8;
	enc_length += (length * 7) % 8 > 0 ? 1 : 0;

	enc = malloc(enc_length);
	memset(enc, 0, enc_length);

	for(i=0 ; i < length ; i++)
	{
		// offset from the right of data to keep
		d_off = i % 8;

		// position of the data we keep
		d_pos = ((i * 7) - (i * 7) % 8) / 8;
		d_pos += (i * 7) % 8 > 0 ? 1 : 0;

		// adding the data with correct offset
		enc[d_pos] |= data[i] >> d_off;

		// numbers of bits to omit to get data to add another place
		a_off = 8 - d_off;
		// position (on the encoded feed) of the data to add
		a_pos = d_pos - 1;

		// adding the data to add at the correct position
		enc[a_pos] |= data[i] << a_off;
	}

	*data_enc = enc;
	
	return enc_length;
}

void hex_dump(void *data, int size)
{
	/* dumps size bytes of *data to stdout. Looks like:
	 * [0000] 75 6E 6B 6E 6F 77 6E 20
	 *				  30 FF 00 00 00 00 39 00 unknown 0.....9.
	 * (in a single line of course)
	 */

	unsigned char *p = data;
	unsigned char c;
	int n;
	char bytestr[4] = {0};
	char addrstr[10] = {0};
	char hexstr[ 16*3 + 5] = {0};
	char charstr[16*1 + 5] = {0};
	for(n=1;n<=size;n++) {
		if (n%16 == 1) {
			/* store address for this line */
			snprintf(addrstr, sizeof(addrstr), "%.4x",
			   ((unsigned int)p-(unsigned int)data) );
		}

		c = *p;
		if (isalnum(c) == 0) {
			c = '.';
		}

		/* store hex str (for left side) */
		snprintf(bytestr, sizeof(bytestr), "%02X ", *p);
		strncat(hexstr, bytestr, sizeof(hexstr)-strlen(hexstr)-1);

		/* store char str (for right side) */
		snprintf(bytestr, sizeof(bytestr), "%c", c);
		strncat(charstr, bytestr, sizeof(charstr)-strlen(charstr)-1);

		if(n%16 == 0) {
			/* line completed */
			LOGD("[%4.4s]   %-50.50s  %s", addrstr, hexstr, charstr);
			hexstr[0] = 0;
			charstr[0] = 0;
		} else if(n%8 == 0) {
			/* half line: add whitespaces */
			strncat(hexstr, "  ", sizeof(hexstr)-strlen(hexstr)-1);
			strncat(charstr, " ", sizeof(charstr)-strlen(charstr)-1);
		}
		p++; /* next byte */
	}

	if (strlen(hexstr) > 0) {
		/* print rest of buffer if not empty */
		LOGD("[%4.4s]   %-50.50s  %s\n", addrstr, hexstr, charstr);
	}
}
