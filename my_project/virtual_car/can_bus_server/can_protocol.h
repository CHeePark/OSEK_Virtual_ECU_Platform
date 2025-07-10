#ifndef CAN_PROTOCOL_H
#define CAN_PROTOCOL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // read, write
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>

#define PORT 9000
#define MAX_CLIENTS 10  // MAX ECU 수
#define CAN_MSG_MAX_LEN 8

typedef struct {
    int id;             // CAN 메시지 ID
    int len;            // 데이터 길이
    unsigned char data[CAN_MSG_MAX_LEN];
} can_msg_t;

#endif