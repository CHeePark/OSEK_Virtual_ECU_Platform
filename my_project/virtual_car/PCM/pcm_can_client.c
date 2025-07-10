#include "pcm_common.h"

int can_sock;
struct sockaddr_in serv_addr;

void can_client_init(const char* server_ip, int port) {
    can_sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, server_ip, &serv_addr.sin_addr);
    
    if (connect(can_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("CAN 서버 연결 실패");
    
}
}

void can_send(const can_msg_t* msg) {
    write(can_sock, msg, sizeof(can_msg_t));
}

int can_recv(can_msg_t* msg) {
    return read(can_sock, msg, sizeof(can_msg_t));
}