#include "bcm_common.h"  

int turn_signal_status=0;

// 램프 제어 task
TASK(Task_TurnSignal_Control) {
    while(1){
        //Wait를 통한 이벤트 대기
        WaitEvent(Event_TurnSignal_Request);
        ClearEvent(Event_TurnSignal_Request);
    
        if (turn_signal_status == 1) {
            printf("[BCM/방향지시등] ✨ 왼쪽 램프 ON\r\n\r\n");
        } 
        else if (turn_signal_status == 2) {
            printf("[BCM/방향지시등] ✨ 오른쪽 램프 ON\r\n\r\n");
        }
        else {
             printf("[BCM/방향지시등] ✨ 모든 램프 OFF\r\n\r\n");
        }
    }
}