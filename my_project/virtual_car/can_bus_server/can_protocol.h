#ifndef CAN_PROTOCOL_H
#define CAN_PROTOCOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // read, write
#include <sys/socket.h> // socket, bind, listen, accept
#include <sys/types.h> // socket, fd_set
#include <netinet/in.h> //sockaddr_in
#include <arpa/inet.h> // inet_pton, htons
#include <sys/select.h> // select, fd_isset
#include <errno.h>
#include <fcntl.h>

#define PORT 9000
#define MAX_CLIENTS 10  // MAX ECU 수
#define CAN_MSG_MAX_LEN 8

typedef struct {
    int id;             // CAN 메시지 ID
    int len;            // 데이터 길이
    unsigned char data[CAN_MSG_MAX_LEN]; //CAN 최대 8바이트 지원
} can_msg_t;

#endif