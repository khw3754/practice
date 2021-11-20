#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(void) {
    int fd;
    char * pathname = "./userlist.txt";
    char id[21];
    char pw[21];

//id,pw chatgi?
signin:
    printf("****************로그인****************\n");
    printf("*******회원가입은 \"signup\"입력********\n");
    printf("ID: ");
    scanf("%s", id);
    if (strcmp(id, "signup") == 0) {
	printf("*****사용자 등록*****\n");
        char addlist[51];
        printf("이름 (10자이내): ");
        scanf("%s", addlist);
        printf("ID (20자이내): ");
        scanf("%s", id);
        printf("PW (20자이내): ");
        scanf("%s", pw);

        fd = open(pathname, O_CREAT | O_APPEND |O_RDWR, 0666);
        if (fd == -1){
            perror("open() error!");
            exit(-1);
        }

        strcat(addlist, " : ");
        strcat(addlist, id);
        strcat(addlist, " : ");
        strcat(addlist, pw);

        write(fd, addlist, strlen(addlist));
        close(fd);

        goto signin;
    }
    else {
        printf("PW: ");
        scanf("%s", pw);
    }
    
    


    return 0;
}
