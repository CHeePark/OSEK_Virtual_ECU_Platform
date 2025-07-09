#include "bcm_common.h"  

int g_lock_status = 0; // 문 잠금 요청 (0:unlock, 1:lock) 
int g_door_status = 0; // 차량 도어 상태 (0:close, 1:opene)

// 방향지시등 램프를 제어하는 Task
TASK(Task_Door_Control) {
    while(1){
        //Wait를 통한 이벤트 대기
        WaitEvent(Event_DoorLock_Request);
        ClearEvent(Event_DoorLock_Request);
        
        //[에러 상태]문 열림 && 잠금 명령
        if (g_door_status == 1 && g_lock_status == 1) {
            printf("[BCM/도어] ⚠️ 문이 열려있어 잠글 수 없습니다!\r\n\r\n");
        }
        
        //[정상 상태] 문 닫힘 && 잠금 해제/명령
        else {
            if (g_lock_status == 1) { //잠금 요청
                g_door_status = 0; 
                printf("[BCM/도어] 🔒 문이 잠겼습니다.\r\n\r\n");
            }
            else {
                g_door_status = 1; 
                printf("[BCM/도어] 🔓 문이 열렸습니다.\r\n\r\n");
            }
        } 
    }
}
