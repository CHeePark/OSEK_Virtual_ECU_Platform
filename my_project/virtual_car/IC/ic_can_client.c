#include "ic_common.h"

int can_sock;
struct sockaddr_in serv_addr;
uint8_t can_data[8]; // CAN 메시지 데이터 버퍼
int can_msg_id; // 수신된 CAN 메시지 ID

void can_client_init(const char* server_ip, int port) {
    can_sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &serv_addr.sin_addr);
    
    if (connect(can_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("CAN 서버 연결 실패\r\n");
    } 
    
    else {
        printf("[IC/CAN] 서버 연결 성공\r\n");
    }
}

void can_send(const can_msg_t* msg) {
    int ret=write(can_sock, msg, sizeof(can_msg_t));
    if(ret<0){
        printf("[IC/CAN] CAN 메시지 전송 실패\r\n");
    }
}

int can_recv(can_msg_t* msg) {
    int ret = read(can_sock, msg, sizeof(can_msg_t));
    if(ret<0){
        printf("[IC/CAN] CAN 메시지 수신 실패\r\n");
    }
    return ret; 
}