/**
 * This file is part of libsamsung-ipc.
 *
 * Copyright (C) 2012 Simon Busch <morphis@gravedo.de>
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
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <strings.h>
#include <getopt.h>

#define IOCTL_MODEM_SEND        _IO('o', 0x23)
#define IOCTL_MODEM_RECV        _IO('o', 0x24)

struct modem_io {
    uint32_t size;
    uint32_t id;
    uint32_t cmd;
    void *data;
};

void forward_data(int modem_fd, int remote_fd)
{
    fd_set rfds;
    int rc, max_fd;
    unsigned char buf[4096];

    max_fd = modem_fd > remote_fd ? modem_fd + 1 : remote_fd + 1;

    while(1) {
        FD_ZERO(&rfds);
        FD_SET(modem_fd, &rfds);
        FD_SET(remote_fd, &rfds);

        rc = select(max_fd, &rfds, NULL, NULL, NULL);
        if (rc == -1) {
            perror("select()");
            break;
        }
        else if (rc) {
            if (FD_ISSET(modem_fd, &rfds)) {
                rc = ioctl(modem_fd, IOCTL_MODEM_RECV, &buf);
                if (rc < 0)
                    break;
                ssize_t size = ((struct modem_io*) &buf)->size;
                printf("Sending from modem %ld\n", size);
                ssize_t written = write(remote_fd, &buf, size);
            }
            else if (FD_ISSET(remote_fd, &rfds)) {
                ssize_t size = read(remote_fd, &buf, sizeof(buf));
                if (size <= 0)
                    break;
                printf("Sending from destination %ld\n", size);
                ssize_t written = ioctl(modem_fd, IOCTL_MODEM_SEND, &buf);
            }
        }
    }
}

int init_network_connection(int port)
{
    int socket_fd = socket(PF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("Failed to create network socket");
        return EXIT_FAILURE;
    }

    int opt = 1;
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) == -1) {
        perror("Warning: can't set SO_REUSEADDR");
    }

    struct sockaddr_in addr = { 0, };
    addr.sin_family = PF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(socket_fd, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
        perror("Error while binding socket");
        goto socket_init_failed;
    }

    if (listen(socket_fd, 1) == -1) {
        perror("Error while started listing on socket");
        goto socket_init_failed;
    }

    return socket_fd;

socket_init_failed:
    close(socket_fd);
    return -1;
}

int main(int argc, char **argv)
{
    opterr = 0;
    int option_index;
    int chr;
    char serial_node[30] = "\0";
    int network_port;
    int show_help = 0;
    int modem_fd = 0, socket_fd = 0;

    struct option opts[] = {
        { "node", required_argument, 0, 'n' },
        { "port", required_argument, 0, 'p' },
        { "help", no_argument, 0, 'h' },
    };

    while (1) {
        option_index = 0;
        chr = getopt_long(argc, argv, "n:p:h", opts, &option_index);

        if (chr == -1)
            break;

        switch (chr) {
            case 'h':
                show_help = 1;
                break;
            case 'n':
                snprintf(serial_node, 30, "%s", optarg);
                break;
            case 'p':
                network_port = atoi(optarg);
                break;
            default:
                break;
        }
    }

    if (show_help || network_port == 0 || serial_node[0] == 0) {
        printf("usage: samsung_ipc_forward -n <device node> -p <network port>\n");
        exit(1);
    }

    socket_fd = init_network_connection(network_port);
    if (socket_fd < 0)
        return EXIT_FAILURE;

    modem_fd = open(serial_node, O_RDWR | O_NOCTTY | O_NONBLOCK);

    int connection_fd = -1;
    struct sockaddr_in addr = { 0, };
    socklen_t length = sizeof(addr);
    while ((connection_fd = accept(socket_fd, (struct sockaddr*) &addr, &length)) >= 0) {
        printf("New connection from: '%s'\n", inet_ntoa(addr.sin_addr));
        forward_data(modem_fd, connection_fd);
        close(connection_fd);
    }

    close(modem_fd);
    close(socket_fd);

    return 0;

socket_init_failed:
    close(socket_fd);
    return EXIT_FAILURE;
}
