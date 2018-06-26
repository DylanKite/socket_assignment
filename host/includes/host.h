#pragma once

#include "../../client/includes/client.h"

int init_host(char incoming_addr[], unsigned int port);
void read_socket(user_info *incoming_info);
