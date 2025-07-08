#ifndef BCM_COMMON_H
#define BCM_COMMON_H

#include "tpl_os.h" // OS 관련 선언을 사용하기 위해 포함
#include <stdio.h>

//turn_signal.c
#include <unistd.h>

extern int turn_signal_status;

DeclareTask(Task_TurnSignal_Control);
DeclareEvent(Event_TurnSignal_Request);

#endif