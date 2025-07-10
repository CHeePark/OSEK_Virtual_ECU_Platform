#include "ic_common.h"

// 차량 상태 정보 변수 (실제로는 CAN 통신으로 수신)
int vehicle_speed = 0;       // 차량 속도
int engine_rpm = 0;          // 엔진 RPM
bool engine_status = false;  // 엔진 상태
int turn_signal_status = 0;  // 방향지시등 상태
bool door_status = false;         // 도어 상태
bool lock_status = false;         // 잠금 상태
char gear_position = 'p';    // 기어 위치

int main(void) {
    
    printf("IC CAN 클라이언트 초기화 중...\n");
    can_client_init("127.0.0.1", 9000);
    printf("IC CAN 클라이언트 초기화 완료\n");

    printf("IC(계기판) 시스템 부팅...\r\n\r\n");
    printf("  [종료] q 또는 a\r\n\r\n");

    StartOS(stdAppmode);
    return 0;
}
