#include "bcm_common.h"

int can_sock;
struct sockaddr_in serv_addr;

void can_client_init(const char* server_ip, int port) {
    can_sock = socket(AF_INET, SOCK_STREAM, 0); //sock_stream=TCP 소켓 생성, 0은 기본 프로토콜
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &serv_addr.sin_addr); //inet_pton()는 문자열 IP주소를 이진 형식으로 변환
    // sin_addr 필드는 바이너리 형식 필요

    if (connect(can_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("CAN 서버 연결 실패\r\n");
    } 
    else {
        printf("[BCM/CAN] 서버 연결 성공\r\n");
    }
}

void can_send(const can_msg_t* msg) {
    int ret=write(can_sock, msg, sizeof(can_msg_t));
    if(ret<0){
        printf("[BCM] CAN 메시지 전송 실패\r\n");
    }
}

int can_recv(can_msg_t* msg) {
    int ret = read(can_sock, msg, sizeof(can_msg_t));
    if(ret<0){
        printf("[BCM] CAN 메시지 수신 실패\r\n");
    }
    return ret; 
}