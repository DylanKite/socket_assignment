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
	user_info user;
    unsigned port = 0;
	int read_return_val;
	port = atoi(argv[2]);
	printf("starting connecton at ip: %s and port %d\n", argv[1], port);
	init_host(argv[1], port);
	for(;;)
	{
		read_return_val = read_socket(&user);
        host_write_user_to_file(user);
	}
    return 0;
}
