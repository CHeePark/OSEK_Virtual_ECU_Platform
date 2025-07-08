#include"bcm_common.h"
//#include"turn_signal.c"
int turn_signal_status=0;

// --- 공용 Task: 운전자의 키보드 입력을 처리 ---
TASK(Task_Driver_Input) {
    printf("BCM 통합 제어 시스템 v1.0\r\n");
    printf("✨방향지시등 조작: s: 좌측 ON, d: 끄기, f: 우측 ON\r\n");
    printf("q 또는 a: 프로그램 종료\r\n\r\n");

    while(1) {
        int input = getchar();
        
        int prev_status = turn_signal_status;

        switch(input) {
            case 's':
                turn_signal_status = 1; // 상태를 '좌측'으로 변경
                SetEvent(Task_TurnSignal_Control, Event_TurnSignal_Request);
                break;
            case 'f':
                turn_signal_status = 2; // 상태를 '우측'으로 변경
                SetEvent(Task_TurnSignal_Control, Event_TurnSignal_Request);
                break;
            case 'd':
                turn_signal_status = 0; // 상태를 '끔'으로 변경
                SetEvent(Task_TurnSignal_Control, Event_TurnSignal_Request);
                break;
            default:
                break;
        }       
    }
    //TerminateTask();
}


// --- 프로그램의 시작점 ---
int main(void) {
    printf("BCM(차체 제어 모듈) 시스템 부팅...\r\n\r\n");
    StartOS(stdAppmode);
    return 0;
}