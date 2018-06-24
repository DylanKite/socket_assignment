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
            "11 Send Info\n");
}

/*
 * Argument List:
 * argv[0]: address
 * argv[1]: port
 */
int main(int argc, char *argv[])
{
    char name[50] = {' '};
    int id = 0;
    int street_num = 0;
    char street_name[60] = {' '};
    char city[25] = {' '};
    char postal_code[10] = {' '};
    char province[20] = {' '};
    char country[20] = {' '};

    int port = atoi(argv[1]);
    init_client(argv[0], port);

    int choice = 0;
    help();
    for(;;) {
        scanf("%i", &choice);
        switch(choice) {
        case 1: {
            printf("enter name\n");
            scanf("%s", name);
            break;
        }
        case 2: {
            printf("enter ID\n");
            scanf("%i", &id);
            break;
        }
        case 3: {
            printf("enter street number\n");
            scanf("%i", &street_num);
            break;
        }
        case 4: {
            printf("enter street name\n");
            scanf("%s", street_name);
            break;
        }
        case 5: {
            printf("enter city\n");
            scanf("%s", city);
            break;
        }
        case 6: {
            printf("enter postal code\n");
            scanf("%s", postal_code);
            break;
        }
        case 7: {
            printf("enter province\n");
            scanf("%s", province);
            break;
        }
        case 8: {
            printf("enter country\n");
            scanf("%s", country);
            break;
        }
        case 9: {
            break;
        }
        case 10: {
            break;
        }
        case 11: {
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

