#ifndef PCM_COMMON_H
#define PCM_COMMON_H

#include "tpl_os.h" // trampoline OS 관련 선언 사용 위해 포함
#include <stdio.h>
#include <stdbool.h>

#include "../can_bus_server/can_protocol.h" // CAN 프로토콜 정의 포함
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

//--pcm_global_variable--//
extern bool engine_on;
extern int rpm;
extern char gear_pos; 
extern int acceleration; 

extern int can_sock;
extern struct sockaddr_in serv_addr;

//function 선언
void handle_engine(char input);
void send_engine_status(void);
void send_gear_status(void);
// CAN 클라이언트 함수 선언
void can_client_init(const char* server_ip, int port);
void can_client_close(void);
void can_send(const can_msg_t* msg);
int can_recv(can_msg_t* msg);


//task, event 선언
DeclareTask(Task_Driver_Input);
DeclareTask(Task_Engine_Control);
DeclareEvent(Event_Engine_Change_Request);
DeclareTask(Task_Gear_Control);
DeclareEvent(Event_Gear_Change_Request);

#endif