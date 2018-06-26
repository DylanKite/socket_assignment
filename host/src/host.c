#include "../includes/host.h"
#include "../../client/includes/client.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

static int connected_socket = 0;

#define SUCCESS 1
#define FAILURE 0

int init_host(char incoming_addr[], unsigned int port)
{
    int sock_id;
    struct sockaddr_in addr;
    struct sockaddr_storage addr_storage;
    socklen_t sock_size;

    sock_id = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_id  == -1) {
        printf("%s: error creating new socket", __func__);
        return FAILURE;
    }
    printf("%s: socket_id: %d\n", __func__, sock_id);

    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(incoming_addr);
    addr.sin_port = htons(port);
    memset(addr.sin_zero, '\0', sizeof addr.sin_zero);

    bind(sock_id, (struct sockaddr *) &addr, sizeof(addr));

    if(listen(sock_id,1)==0) {
        printf("Listening\n");
    }
      else {
        printf("Error\n");
    }

    sock_size = sizeof(addr_storage);
    printf("%s: done listening", __func__);
    connected_socket = accept(sock_id,(struct sockaddr *) &addr_storage, &sock_size);
    printf("%s: connection successful\n", __func__);
    return SUCCESS;
}

int read_socket(user_info *incoming_info)
{
	int incoming_message_size = 0;
	int query_id =0;
	recv(connected_socket, &incoming_message_size, sizeof(int), 0);
	if (incoming_message_size == sizeof(int)) {
		recv(connected_socket, &query_id, sizeof(int), 0);
		return query_id;
	}
	printf("incoming message size %d\n", incoming_message_size);
	recv(connected_socket, incoming_info, incoming_message_size, 0);
	return 0;
}

void host_write_user_to_file(user_info to_write)
{
	char string_to_write[1000] = {"\0"};
	char file_name[100];
	int fd = 0;
	sprintf(file_name, "%d.csv", to_write.id);
	fd = open(file_name, O_WRONLY | O_CREAT);
	if(fd < 0) {
		printf("issue writing to file");
	}
	snprintf(string_to_write,sizeof(to_write), "%s, %d, %d, %s, %s, %s, %s, %s",
			to_write.name,
			to_write.id,
			to_write.street_num,
			to_write.street_name,
			to_write.city,
			to_write.postal_code,
			to_write.province,
			to_write.country);
	printf("%s writing to file %s\n",__func__, string_to_write);

	write(fd, string_to_write, strlen(string_to_write));
	close(fd);
}

void query_database(int id)
{
	char file_name[100];
	char string_to_read[1000];
	sprintf(file_name, "%d.csv", id);
	user_info read_user;
	int fd;

	fd = open(file_name, O_RDONLY);
	read(fd,string_to_read,sizeof(string_to_read));
	strcpy(read_user.name, strtok(string_to_read, ","));
	read_user.id = atoi(strtok(NULL, ","));
	read_user.street_num = atoi(strtok(NULL, ","));
	strcpy(read_user.street_name, strtok(NULL, ","));
	strcpy(read_user.city, strtok(NULL, ","));
	strcpy(read_user.postal_code, strtok(NULL, ","));
	strcpy(read_user.province, strtok(NULL, ","));
	strcpy(read_user.country, strtok(NULL, ","));
	strncpy(read_user.country,read_user.country, strlen(read_user.country));

	send(connected_socket, &read_user, sizeof(read_user), 0);

	close(fd);
}
