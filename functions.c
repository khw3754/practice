#include "functions.h"

char * pathname = "./userlist.txt";

void signup(){
    printf("*****사용자 등록*****\n");
    struct User user;
    printf("이름 (10자이내): ");
    scanf("%s", user.name);
    printf("ID (20자이내): ");
    scanf("%s", user.id);
    printf("PW (20자이내): ");
    scanf("%s", user.pw);

    int fd = open(pathname, O_CREAT | O_APPEND |O_RDWR, 0666);
    if (fd == -1){
        perror("open() error!");
        exit(-1);
    }

    write(fd, &user, sizeof(struct User));
    close(fd);
}

int signin(char id[], char pw[], struct User *result){
    int fd;
    fd = open(pathname, O_RDONLY, 0666);
    struct User user;

    int i;
    do {
        i = read(fd, &user, sizeof(struct User));
        //printf("%s, %s, %s\n", user.name, user.id, user.pw);                     여기수정
        if (strcmp(user.id, id) == 0 && strcmp(user.pw, pw) == 0)
            break;
    } while(i > 0);
    if (i == 0){
        printf("없는 사용자입니다.\n\n");
        return 0;
    }
    
    *result = user; 
    return 1;
}

