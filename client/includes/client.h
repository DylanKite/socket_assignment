#pragma once

typedef struct {
	char name[50];
	int id;
	int street_num;
	char street_name[60];
	char city[25];
	char postal_code[10];
	char province[20];
	char country[20];
} user_info;

int init_client(char IP_address[], unsigned int port);

void send_message(user_info to_send);

void write_user_to_file(user_info to_write);
void read_user_file(user_info *read_user);

void print_user_info(user_info *user1);
void query_data_base(int id);
