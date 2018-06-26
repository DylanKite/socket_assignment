#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "../includes/host.h"

/*
 * Argument List:
 * argv[0]: address
 * argv[1]: port
 */
int main(int argc, char *argv[])
{
    unsigned port = 0;
	port = atoi(argv[2]);
	printf("starting connecton at ip: %s and port %d\n", argv[1], port);
	init_host(argv[1], port);
    return 0;
}
