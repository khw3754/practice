#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

struct User {
    char name[21];
    char id[21];
    char pw[21];
};

struct Message {
    char message[1024];
    char sender[21];
    char time[20];
};

void signup();
int signin(char i[], char p[], struct User *result);

void send_message(struct User sender);
void check_message(struct User user);