#include "bcm_common.h"  

bool lock_status = false; // 문 잠금 요청 (false:unlock, true:lock) 
bool door_status = false; // 차량 도어 상태 (false:open, true:close)

// 방향지시등 램프를 제어하는 Task
TASK(Task_Door_Control) {
    while(1){
        //Wait를 통한 이벤트 대기
        WaitEvent(Event_DoorLock_Request);
        ClearEvent(Event_DoorLock_Request);
        
         printf("[BCM/입력] 현재 상태: \r\n");
        printf("도어 잠금 요청: %s\r\n", lock_status ? "잠금 요청" : "해제 요청");
        printf("도어 상태: %s\r\n\r\n", door_status ? "닫힘" : "열림");      
        
        //[에러 상태]문 열림 && 잠금 명령
        if (door_status == false && lock_status == true) {
            printf("[BCM/도어] ⚠️ 문이 열려있어 잠글 수 없습니다!\r\n\r\n");
        }
        
        //[정상 상태] 문 닫힘 && 잠금 해제/명령
        else {
            if (lock_status == true) { //잠금 요청
                printf("[BCM/도어] 🔒 문이 잠겼습니다.\r\n\r\n");
            }
            else {
                printf("[BCM/도어] 🔓 문이 열렸습니다.\r\n\r\n");
            }
        } 
    }
}
