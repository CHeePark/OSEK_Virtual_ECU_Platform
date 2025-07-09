#include "ic_common.h"

// 차량 상태 정보 변수 (실제로는 CAN 통신으로 수신)
int vehicle_speed = 0;       // 차량 속도
int engine_rpm = 0;          // 엔진 RPM
bool engine_status = false;  // 엔진 상태
int turn_signal_status = 0;  // 방향지시등 상태
bool door_status = false;         // 도어 상태
char gear_position = 'p';    // 기어 위치

TASK(Task_Driver_Input) {
    printf("IC(계기판) 제어 시스템\r\n");
    printf("  [디스플레이] d: 계기판 상태 업데이트\r\n");
    printf("  [종료] q 또는 a\r\n\r\n");

    while(1) {
        int input = getchar();

        switch(input) {
            case 'd':
                // 계기판 상태 업데이트 요청
                SetEvent(Task_Display_Update, Event_Display_Update);
                break;
            case 'q': case 'a':
                printf("IC 시스템 종료...\r\n");
                ShutdownOS(E_OK);
                return;
            default:
                printf("[IC/입력 오류] 잘못된 입력입니다.\r\n");
                break;
        }
    }
}

// 메인 함수
int main(void) {
    printf("IC(계기판) 시스템 부팅...\r\n\r\n");
    StartOS(stdAppmode);
    return 0;
}
