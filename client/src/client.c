#include "../includes/client.h"

#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define SUCCESS 1
#define FILEPATH_CSV "user_info.csv"
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

void send_message(user_info to_send)
{
    int size_of_int = sizeof(int);
    send(client_id, &size_of_int, sizeof(int), 0);
    sleep(1);
    send(client_id, &to_send, sizeof(to_send), 0);
}

void write_user_to_file(user_info to_write)
{
    char string_to_write[1000] = {"\0"};
    int fd = 0;
    fd = open(FILEPATH_CSV, O_WRONLY | O_CREAT);
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

void print_user_info(user_info *user1)
{
    printf("USER INFO:\n"
           "name: %s\n"
           "id: %d\n"
           "street number: %d\n"
           "street name: %s\n"
           "city: %s\n"
           "postal code: %s\n"
           "province: %s\n"
           "country: %s\n"
           "____________________________________\n",
           user1->name,
           user1->id,
           user1->street_num,
           user1->street_name,
           user1->city,
           user1->postal_code,
           user1->province,
           user1->country);
}

void query_data_base(int id)
{
    user_info to_print;
    int size_of_int = sizeof(int);
    send(client_id, &size_of_int, sizeof(int), 0);
    sleep(1);
    send(client_id, &id, sizeof(int), 0);
    recv(client_id, &to_print, sizeof(user_info), 0);

    print_user_info(&to_print);
}

void read_user_file(user_info *read_user)
{
    char string_to_read[1000];
    char split_string[100];
    int fd =0;
    fd = open(FILEPATH_CSV, O_RDONLY);
    read(fd,string_to_read,sizeof(string_to_read));
    strcpy(read_user->name, strtok(string_to_read, ","));
    read_user->id = atoi(strtok(NULL, ","));
    read_user->street_num = atoi(strtok(NULL, ","));
    strcpy(read_user->street_name, strtok(NULL, ","));
    strcpy(read_user->city, strtok(NULL, ","));
    strcpy(read_user->postal_code, strtok(NULL, ","));
    strcpy(read_user->province, strtok(NULL, ","));
    strcpy(read_user->country, strtok(NULL, ","));
    strncpy(read_user->country,read_user->country, strlen(read_user->country));
    close(fd);
}
