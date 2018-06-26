#include <stdlib.h>
#include <stdio.h>
#include "../includes/client.h"



static void help()
{
    printf ("Options:\n"
            "1 Enter Name\n"
            "2 Enter ID\n"
            "3 Enter StreetNumber\n"
            "4 Enter StreetName\n"
            "5 Enter City\n"
            "6 Enter Postal Code\n"
            "7 Enter Province\n"
            "8 Enter Country\n"
            "9 Write To File\n"
            "10 Read From File\n"
            "11 Send Info\n"
            "12 Query Database\n"
            "13 Exit program\n");
}

/*
 * Argument List:
 * argv[0]: address
 * argv[1]: port
 */
int main(int argc, char *argv[])
{
    int port = atoi(argv[2]);
    int query_id =0;
    user_info user1 = {0};
    init_client(argv[1], port);

    int choice = 0;
    for(;;) {
        print_user_info(&user1);
        help();
        scanf("%i", &choice);
        switch(choice) {
        case 1: {
            printf("enter name\n");
            scanf("%s", user1.name);
            break;
        }
        case 2: {
            printf("enter ID\n");
            scanf("%i", &user1.id);
            break;
        }
        case 3: {
            printf("enter street number\n");
            scanf("%i", &user1.street_num);
            break;
        }
        case 4: {
            printf("enter street name\n");
            scanf("%s", user1.street_name);
            break;
        }
        case 5: {
            printf("enter city\n");
            scanf("%s", user1.city);
            break;
        }
        case 6: {
            printf("enter postal code\n");
            scanf("%s", user1.postal_code);
            break;
        }
        case 7: {
            printf("enter province\n");
            scanf("%s", user1.province);
            break;
        }
        case 8: {
            printf("enter country\n");
            scanf("%s", user1.country);
            break;
        }
        case 9: {
            write_user_to_file(user1);
            break;
        }
        case 10: {
            read_user_file(&user1);
            break;
        }
        case 11: {
            send_message(user1);
            break;
        }
        case 12: {
            printf("enter ID to query\n");
            scanf("%d", &query_id);
            query_data_base(query_id);
            break;
        }
        case 13: {
            exit(1);
            break;
        }
        default: {
            help();
            break;
        }
        }
    }
    return 1;
}

