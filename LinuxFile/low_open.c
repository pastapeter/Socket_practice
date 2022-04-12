// 파일 열기
/*
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    int open(const cahr *path, int flag);
    성공시 파일 디스크립터, 실패시 -1 반환

*/

// 파일 닫기
/*
    #include <unistd.h>
    int close (int fd);
*/

// 파일에 데이터 쓰기 - 파일에 데이터를 출력(전송) 하는 함수, 소켓을 통해서 다른 컴퓨터에 데이터를 전송할떄 함수를 쓴다.
/*
    #inclue <unistd.h>
    ssize_t write(int fd, const void* buf, size_t nbytes);

    여기서 fd 는 데이터 전송 대상을 나타냄, buf - 전송할 데이터가 저장된 버퍼의 주소값, nbytes - 전송할 데이터의 바이트 수
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
void error_handling(char* message);

int main() {
    int fd;
    char buf[] = "Let's go!\n";

    fd = open("data.txt", O_CREAT|O_WRONLY|O_TRUNC);
    if (fd == -1) {
        error_handling("open() error!");
    }
    printf("file descriptor : %d\n", fd);

    if(write(fd, buf, sizeof(buf)) == -1) error_handling("write error");
    close(fd);
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
