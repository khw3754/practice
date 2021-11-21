#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "functions.h"

int main(void) {
    int fd;
    char * pathname = "./userlist.txt";
    char id[21], pw[21];
    struct User user;

signin:
    printf("****************로그인****************\n");
    printf("*******회원가입은 \"signup\"입력********\n");
    printf("**********종료는 \"exit\"입력***********\n");
    printf("ID: ");
    scanf("%s", id);
    if (strcmp(id, "signup") == 0) {
        signup();

        goto signin;
    }
    else if (strcmp(id, "exit") == 0){
	printf("프로그램을 종료합니다.\n"); 
	return 0;
    }
    else {
        printf("PW: ");
        scanf("%s", pw);
        /*int i = 0;
        while (1){
            pw[i] = getch();
            putch('*');
            if (pw[i++] == '\n')
                break;
        }*/
    }
    
    int s = signin(id, pw, &user);
    if (s == 0)
        goto signin;
    printf("\n%s님 안녕하세요.\n", user.name); 

    return 0;
}

//디렉토리를 하나 만들게 해서 거기다가 userlist랑 유저마다 메세지 관리 파일 하나씩 만들게 해야할 듯
