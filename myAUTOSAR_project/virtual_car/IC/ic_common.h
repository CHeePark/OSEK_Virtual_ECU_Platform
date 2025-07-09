#ifndef IC_COMMON_H
#define IC_COMMON_H

#include "tpl_os.h"
#include <stdio.h>
#include <stdbool.h>

// 다른 ECU에서 수신한 정보 저장 변수
extern int vehicle_speed;       // 차량 속도
extern int engine_rpm;          // 엔진 RPM
extern bool engine_status;      // 엔진 상태
extern int turn_signal_status;  // 방향지시등 상태
extern bool door_status;         // 도어 상태
extern char gear_position;      // 기어 위치

// function 선언
void update_dashboard_display(void);

// task, event 선언
DeclareTask(Task_Driver_Input);
DeclareTask(Task_Display_Update);
DeclareEvent(Event_Display_Update);


#endif