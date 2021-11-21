#include "functions.h"

char * pathname = "./userlist.txt";

void signup() {
    printf("*****사용자 등록*****\n");
    struct User user;
    printf("이름 (20자이내): ");
    scanf("%s", user.name);
    printf("ID (20자이내): ");
    scanf("%s", user.id);
    printf("PW (20자이내): ");
    scanf("%s", user.pw);
    printf("\n");

    int fd = open(pathname, O_CREAT | O_APPEND |O_RDWR, 0666);
    if (fd == -1){
        perror("open() error!");
        exit(-1);
    }

    creat(user.name, 0666);

    write(fd, &user, sizeof(struct User));
    close(fd);
}

int signin(char id[], char pw[], struct User *result) {
    int fd;
    fd = open(pathname, O_CREAT | O_RDONLY, 0666);
    struct User user;

    int i = read(fd, &user, sizeof(struct User));
    while (i > 0) {
        if (strcmp(user.id, id) == 0 && strcmp(user.pw, pw) == 0)
            break;
        i = read(fd, &user, sizeof(struct User));
    }
    if (i == 0){
        printf("없는 사용자입니다.\n\n");
        return 0;
    }
    
    *result = user; 
    return 1;
}

void send_message(struct User sender) {
    int fd, count = 1, index;
    fd = open(pathname, O_RDONLY, 0666);
    struct User receiver;

    printf("\n***수신자 선택***\n");
    int i = read(fd, &receiver, sizeof(struct User));
    while (i > 0) {
        if (strcmp(receiver.name, sender.name) != 0)
            printf("%d.%s\n", count++, receiver.name);
        i = read(fd, &receiver, sizeof(struct User));
    }
    printf("%d.뒤로가기\n", count);
choose:
    printf("번호입력: ");
    scanf("%d", &index);
    if(index == count){
        printf("\n");
        return;
    }

    lseek(fd, 0, SEEK_SET);
    count = 1;
    i = read(fd, &receiver, sizeof(struct User));
    while (i > 0) {
        if (strcmp(receiver.name, sender.name) != 0){
            if (count == index)
                break;
            count++;
            i = read(fd, &receiver, sizeof(struct User));
            continue;
        }
        i = read(fd, &receiver, sizeof(struct User));
    }
    if (i == 0){
        printf("잘못 선택하셨습니다.\n\n");
	goto choose;
    }
    close(fd);

    struct Message msg;
    printf("\n%s에게 보낼 메세지를 작성하세요.(한글 340자 제한)\n>>", receiver.name);
    scanf(" %[^\n]s", msg.message);
    strcpy(msg.sender, sender.name);
    time_t t = time(NULL);
    struct tm *now = localtime(&t);
    strftime(msg.time, sizeof(msg.time), "%m월%d일 %H:%M\n", now);

    fd = open(receiver.name, O_WRONLY | O_APPEND, 0666);
    if (write(fd, &msg, sizeof(struct Message)) == -1)
        perror("write() error!\n");
    printf("메세지를 보냈습니다.\n\n");
    close(fd);
}

void check_message(struct User user) {
    int fd;
    struct Message msg[10];
    fd = open(user.name, O_RDONLY, 0666);

    int i;
    for (i = 1; i <= 10; i++){
        if(lseek(fd, -i * sizeof(struct Message), SEEK_END) == -1)
            break;
        read(fd, &msg[i-1], sizeof(struct Message));
    }

    printf("\n***받은 메세지 출력***\n");
    printf("(최근 10개의 메세지가 출력됩니다.)\n\n");
    for(int j = 0; j < i-1; j++) {
        printf("내용: %s\n보낸사람: %s\n%s\n\n", msg[j].message, msg[j].sender, msg[j].time);
    }
    if (i == 1)
        printf("메세지가 없습니다.\n\n");

    close(fd);
}
