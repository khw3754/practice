#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

struct User {
    char name[11];
    char id[21];
    char pw[21];
};

void signup();

int signin(char i[], char p[], struct User *result);