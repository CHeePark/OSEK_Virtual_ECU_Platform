#ifndef IC_COMMON_H
#define IC_COMMON_H

#include "tpl_os.h"
#include <stdio.h>
#include <stdbool.h>

#include "../can_bus_server/can_protocol.h" // CAN 프로토콜 정의 포함
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

// 다른 ECU에서 수신한 정보 저장 변수
extern int vehicle_speed;       // 차량 속도
extern int engine_rpm;          // 엔진 RPM
extern bool engine_status;      // 엔진 상태
extern int turn_signal_status;  // 방향지시등 상태
extern bool door_status;         // 도어 상태
extern bool lock_status;         // 잠금 상태
extern char gear_position;      // 기어 위치

extern int can_sock;
extern struct sockaddr_in serv_addr;
extern uint8_t can_data[8];
extern int can_msg_id;

// function 선언
void update_dashboard_display(void);
void can_client_init(const char* server_ip, int port);
void can_send(const can_msg_t* msg);
int can_recv(can_msg_t* msg);

// task, event 선언
DeclareTask(Task_Display_Update);
DeclareTask(Task_CAN_Receiver);
DeclareEvent(Event_Display_Update);


#endif