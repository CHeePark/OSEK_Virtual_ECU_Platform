#include "pcm_common.h"

int acceleration = 0; // (0: 정지, 1: 가속, 2: 감속)

TASK(Task_Driver_Input) {
    printf("PCM 통합 제어 시스템 \r\n");
    printf("  [엔진] e:시동 on/off, w:가속, s:감속\r\n");
    printf("  [기어] p, r, n, d \r\n");
    printf("  [종료] q 또는 a\r\n\r\n");

    while(1) {
        int input = getchar();

        switch(input) {
            case 'e': case 'w' : case 's':
                handle_engine(input);
                break;
               
            // 변속기 제어
            case 'p': case 'r': case 'n': case 'd':
                gear_pos = input;
                SetEvent(Task_Gear_Control, Event_Gear_Change_Request);
                break;
            
            case 'q' : case 'a':
                printf("PCM 시스템 종료...\r\n");
                ShutdownOS(E_OK); // OS 종료
                return; // 태스크 종료
            default:
                printf("[PCM/입력 오류] 잘못된 입력입니다.\r\n");
                break;
        }
    }
    //TerminateTask();
}

int main(void) {
    printf("PCM(파워트레인 제어 모듈) 시스템 부팅...\r\n\r\n");
    StartOS(stdAppmode);
    return 0;
}

void handle_engine(char input) {
    switch(input) {
        case 'e': // 시동 on/off
            engine_on = !engine_on;
            acceleration=0;
            break;
        case 'w': // 가속
            acceleration = 1; 
            break;
        case 's': // 감속
            acceleration = 2; 
            break;
        default:
            printf("[ERROR in engine_control]\r\n");
            break;
    }
    SetEvent(Task_Engine_Control, Event_Engine_Change_Request);
            

}