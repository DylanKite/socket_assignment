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
