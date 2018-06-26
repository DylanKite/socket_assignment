#pragma once

#include "../../client/includes/client.h"

int init_host(char incoming_addr[], unsigned int port);
int read_socket(user_info *incoming_info);
void host_write_user_to_file(user_info to_write);
void query_database(int id);
