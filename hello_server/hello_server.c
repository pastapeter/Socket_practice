//
//  main.c
//  hello_server
//
//  Created by Jung peter on 2022/04/11.
//

// socket 생성 성공시 0, 실패시 -1
//int socket(int domain, int type, int protocol);

// 소켓에 IP와 포트번호 부여받기 성공시 0, 실패시 -1
//int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);

// 케이블 연결시켜서 전화가 걸려오기를 기다리기 성공시 0, 실패시 -1
//int listen(int sockfd, int backlog);

// 전화벨소리가울렸을떄, 연결요청에 대한 수락
// int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char* message);

int main(int argc, const char * argv[]) {
  int serv_sock;
  int clnt_sock;
  
  struct sockaddr_in serv_addr;
  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_size;
  
  char message[] = "Hello world";
  
  if(argc!=2) {
    printf("usage : %s <port>\n", argv[0]);
    exit(1);
  }
  
  // 소켓 생성중
  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if(serv_sock == -1) error_handling("socket() error");
  
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port=htons(atoi(argv[1]));
  
  // bind 함수를 통해서 IP주소와 PORT 번호 요청
  if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
    error_handling("bind() error");
  }
  
  // listen함수를 호출한다. -> 소켓요청을 방아들일 수 있는 상태가 된다.
  if(listen(serv_sock, 5) == -1) {
    error_handling("listen() error");
  }
  
  clnt_addr_size = sizeof(clnt_addr);
  // 연결요청 수락을 위한 accept 함수 호출, 연결 요청이 없는 상태에서 이함수 호출되면, 연결 요청이 있을때까지 함수 반환하지 않는다.
  clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
  if (clnt_sock == -1) error_handling("accept() error");
  
  // write 함수는 데이터를 전송하는 기능의 함수 
  write(clnt_sock, message, sizeof(message));
  close(clnt_sock);
  close(serv_sock);
  return 0;
}

void error_handling(char* message) {
  fputs(message, stderr);
  fputc('\n', stderr);
  exit(1);
}
