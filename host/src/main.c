#include <stdlib.h>
#include <stdio.h>
#include "../includes/host.h"

/*
 * Argument List:
 * argv[0]: address
 * argv[1]: port
 */
int main(int argc, char *argv[])
{
    unsigned port = 0;

    port = atoi(argv[1]);
    init_host(argv[0], port);
    return 0;
}
