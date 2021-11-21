#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include "functions.h"

int main(void) {
    char id[21], pw[21];
    struct User user;

    if (chdir("datas") == -1){
        mkdir("datas", 0755);
        chdir("datas");
    }

signin:
    printf("****************로그인****************\n");
    printf("*******회원가입은 \"signup\"입력********\n");
    printf("**********종료는 \"exit\"입력***********\n");
    printf("ID: ");
    scanf("%s", id);
    if (strcmp(id, "signup") == 0) {
        printf("\n");
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
    }
    
    int s = signin(id, pw, &user);
    if (s == 0)
        goto signin;
    printf("\n%s님 안녕하세요.\n\n", user.name); 

    while (1) {
        int menu;
        printf("***메뉴선택***\n");
        printf("1.메세지 보내기\n2.메세지 확인하기\n3.로그아웃\n번호입력: ");
        scanf("%d", &menu);
        if (menu == 1) 
            send_message(user);
        else if (menu == 2)
            check_message(user);
        else if (menu == 3){
            printf("\n");
            goto signin;
        }
        else {
            printf("\n");
            continue;
        }
    }




    return 0;
}

//디렉토리를 하나 만들게 해서 거기다가 userlist랑 유저마다 메세지 관리 파일 하나씩 만들게 해야할 듯
