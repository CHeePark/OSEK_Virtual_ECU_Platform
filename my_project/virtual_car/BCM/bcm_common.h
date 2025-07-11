#ifndef BCM_COMMON_H
#define BCM_COMMON_H

#include "tpl_os.h" // trampoline OS 관련 선언 사용 위해 포함
#include <stdio.h>
#include <stdbool.h>

#include "../can_bus_server/can_protocol.h" // CAN 프로토콜 정의 포함
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

//--bcm_global_variable--//
extern int turn_signal_status;
extern bool lock_status; 
extern bool door_status;

extern int can_sock;
extern struct sockaddr_in serv_addr;

//function 선언
void handle_turn_signal(char input);
void handle_door_lock(char input);
void handle_door(char input);
void send_turn_signal_status(void);
// CAN 클라이언트 함수 선언
void can_client_init(const char* server_ip, int port);
void can_client_close(); 
void can_send(const can_msg_t* msg);
int can_recv(can_msg_t* msg);   

//task, event 선언
DeclareTask(Task_Driver_Input);
DeclareTask(Task_TurnSignal_Control);
DeclareEvent(Event_TurnSignal_Request);
DeclareTask(Task_Door_Control);
DeclareEvent(Event_DoorLock_Request);

#endif