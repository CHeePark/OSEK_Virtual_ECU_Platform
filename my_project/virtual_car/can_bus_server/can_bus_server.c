#include "can_protocol.h"

int main() {
    int server_fd, client_fd, max_fd, activity, i, valread, sd, new_socket;
    
    int client_socket[MAX_CLIENTS] = {0}; 
    struct sockaddr_in address;
    fd_set readfds;
    can_msg_t msg;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    // 소켓 생성, IPv4프로토콜, TCP 소켓
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    //소켓 수신 대기 상태, 최대 3개의 연결 대기

    printf("CAN 버스 서버 시작 (포트 %d)\n", PORT);

    while(1) {
        FD_ZERO(&readfds); //readfds 초기화
        FD_SET(server_fd, &readfds); // 서버 소켓을 readfds에 추가
        max_fd = server_fd;

        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_socket[i];
            if (sd > 0) FD_SET(sd, &readfds);
            if (sd > max_fd) max_fd = sd;
        }

        activity = select(max_fd + 1, &readfds, NULL, NULL, NULL);
        //max_fd+1 왜??, 감시할 소켓=readfds
        if (FD_ISSET(server_fd, &readfds)) {
            int addrlen = sizeof(address);
            new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
            //new socket 생성, 연결 수락
            for (i = 0; i < MAX_CLIENTS; i++) {
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    break;
                }
            }
        }

        // 데이터 수신 및 브로드캐스트
        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_socket[i];
            if (FD_ISSET(sd, &readfds)) {
                valread = read(sd, &msg, sizeof(msg));
                if (valread == 0) {
                    close(sd);
                    client_socket[i] = 0;
                } else {
                    // 브로드캐스트
                    for (int j = 0; j < MAX_CLIENTS; j++) {
                        if (client_socket[j] != 0 && j != i) {
                            write(client_socket[j], &msg, sizeof(msg));
                        }
                    }
                }
            }
        }
    }
}