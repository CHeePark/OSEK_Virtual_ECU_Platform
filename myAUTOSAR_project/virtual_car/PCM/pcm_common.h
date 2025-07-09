#ifndef PCM_COMMON_H
#define PCM_COMMON_H

#include "tpl_os.h" // trampoline OS 관련 선언 사용 위해 포함
#include <stdio.h>
#include <stdbool.h>

//--engine_control_global_variable--//
extern bool engine_on;
extern int rpm;
extern char gear_pos; 
extern int acceleration; 

//function 선언
void handle_engine(char input);

//task, event 선언
DeclareTask(Task_Driver_Input);
DeclareTask(Task_Engine_Control);
DeclareEvent(Event_Engine_Change_Request);
DeclareTask(Task_Gear_Control);
DeclareEvent(Event_Gear_Change_Request);

#endif