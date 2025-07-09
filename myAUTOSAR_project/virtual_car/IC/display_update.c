#include "ic_common.h"

TASK(Task_Display_Update) {
    while(1) {

        WaitEvent(Event_Display_Update);
        ClearEvent(Event_Display_Update);
        
  
        printf("\r\n===== 계기판 상태 업데이트 =====\r\n");
        update_dashboard_display();
        printf("==============================\r\n\r\n");
    }
}

//계기판 update function
void update_dashboard_display(void) {
  
     // read BCM data
    printf("[IC/방향지시등] 상태: ");
    if(turn_signal_status == 1) printf("좌측 깜빡임\r\n");
    else if(turn_signal_status == 2) printf("우측 깜빡임\r\n");
    else printf("꺼짐\r\n");
    printf("[IC/도어] 상태: %s\r\n\r\n", door_status ? "닫힘" : "열림");
    
    // read PCM data
    printf("[IC/속도계] 현재 속도: %d km/h\r\n", vehicle_speed);
    printf("[IC/RPM] 현재 엔진 RPM: %d\r\n", engine_rpm);
    printf("[IC/엔진] 엔진 상태: %s\r\n", engine_status ? "켜짐" : "꺼짐");
    printf("[IC/기어] 현재 기어: %c\r\n", gear_position);
    
    
}