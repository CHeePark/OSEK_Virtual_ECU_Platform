#ifndef BCM_COMMON_H
#define BCM_COMMON_H

#include "tpl_os.h" // trampoline OS 관련 선언 사용 위해 포함
#include <stdio.h>
#include <stdbool.h>

//--trun_signal_global_variable--//
extern int turn_signal_status;


//--door_lock_global_variable--//
extern bool lock_status; 
extern bool door_status;

//function 선언
void handle_turn_signal(char input);
void handle_door_lock(char input);
void handle_door(char input);

//task, event 선언
DeclareTask(Task_Driver_Input);
DeclareTask(Task_TurnSignal_Control);
DeclareEvent(Event_TurnSignal_Request);
DeclareTask(Task_Door_Control);
DeclareEvent(Event_DoorLock_Request);

#endif