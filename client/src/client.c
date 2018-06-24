#include "../includes/client.h"

#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SUCCESS 1

static int client_id =0;

int init_client(char IP_address[], unsigned int port)
{
    int rtnValue;
        struct sockaddr_in serverAddr;
        socklen_t addr_size;

        client_id =  socket(PF_INET, SOCK_STREAM, 0);
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        serverAddr.sin_addr.s_addr = inet_addr(IP_address);
        printf("%s ip address: %s\n", __func__, IP_address);
        memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

        addr_size = sizeof serverAddr;

        rtnValue = connect(client_id, (struct sockaddr *) &serverAddr, addr_size);
        if (rtnValue == -1) {
            printf("%s: error connecting errno: %s\n", __func__, strerror(errno));
        }
        printf("%s: client id: %d", __func__, client_id);
        return SUCCESS;
}

