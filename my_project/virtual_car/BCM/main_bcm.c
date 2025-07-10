#include"bcm_common.h"


//-- 공용 Task: 운전자의 키보드 입력을 처리 --//
TASK(Task_Driver_Input) {
    printf("BCM 통합 제어 시스템\r\n");
     printf("[방향지시등]   s:좌측, d:끄기, f:우측\r\n");
    printf("[도어]          l:잠금, u:해제, o:문열기, c:문닫기\r\n");
    printf("[종료] q 또는 a\r\n\r\n");

    while(1) {
        int input = getchar();

        switch(input) {
            case 's': case 'f': case 'd':
                handle_turn_signal(input); 
                break;
            case 'l': case 'u':
                handle_door_lock(input);
                break;
            case 'o': case 'c':
                handle_door(input);
                break;
            case 'q': case 'a':
                printf("BCM 시스템 종료...\r\n");
                ShutdownOS(E_OK); 
                return; 
            default:
                printf("[BCM/입력 오류] 잘못된 입력입니다.\r\n");
                break;
        } 
    }
    //TerminateTask();
}

//-- main --//
int main(void) {
     // CAN 클라이언트 초기화
    printf("BCM CAN 클라이언트 초기화 중...\r\n");
    can_client_init("127.0.0.1", 9000); //로컬로 연결
    printf("BCM CAN 클라이언트 초기화 완료\r\n");
    
    printf("BCM(Body Control Module) 시스템 부팅...\r\n\r\n");
    StartOS(stdAppmode);
    return 0;
}

void handle_turn_signal(char input) {
    switch(input) {
        case 's':
            turn_signal_status = 1; // 좌측 
            break;
        case 'f':
            turn_signal_status = 2; // 우측
            break;
        case 'd':
            turn_signal_status = 0; // OFF
            break;
        default:
            printf("[ERROR in turn_signal]\r\n");
            break;
    }
    SetEvent(Task_TurnSignal_Control, Event_TurnSignal_Request);
}

void handle_door_lock(char input) {
    switch(input) {
        case 'l':
            lock_status = true; // lock
            break;
        case 'u':
            lock_status = false; // unlock
            break;
        default:
            printf("[ERROR in door_lock]\r\n");
            break;
    }
    SetEvent(Task_Door_Control, Event_DoorLock_Request);
}

void handle_door(char input) {
    switch(input) {
        case 'o':
            door_status = false; // open
            break;
        case 'c':
            door_status = true; // close
            break;
        default:
            printf("[ERROR in door]\r\n");
            break;
    }
    SetEvent(Task_Door_Control, Event_DoorLock_Request);
}