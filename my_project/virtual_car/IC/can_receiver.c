#include "ic_common.h"

// 가상 CAN 메시지 수신 태스크
TASK(Task_CAN_Receiver) {
    printf("[IC/CAN] 메시지 수신 태스크 시작\r\n");
    
    while(1) {
        // CAN 메시지 수신 (실제 구현)
        can_msg_t msg;
        int ret = can_recv(&msg);
        
        if (ret > 0) {
            can_msg_id = msg.id;
            memcpy(can_data, msg.data, 8);
            
            printf("[IC/CAN] 메시지 수신: ID=0x%X, 길이=%d\r\n", msg.id, msg.len);
            
            // CAN ID에 따라 다른 처리
            switch(can_msg_id) {
                case 0x100: // PCM 엔진 상태
                    engine_status = can_data[0];
                    engine_rpm = (can_data[1] << 8) | can_data[2];
                    printf("[IC/CAN] 엔진 상태 수신: %s, RPM: %d\r\n", 
                           engine_status ? "ON" : "OFF", engine_rpm);
                    break;
                    
                case 0x101: // PCM 속도, 기어
                    vehicle_speed = (can_data[0] << 8) | can_data[1];
                    gear_position = can_data[2];
                    printf("[IC/CAN] 속도/기어 수신: %d km/h, 기어: %c\r\n", 
                           vehicle_speed, gear_position);
                    break;
                    
                case 0x200: // BCM 방향지시등
                    turn_signal_status = can_data[0];
                    printf("[IC/CAN] 방향지시등 수신: %d\r\n", turn_signal_status);
                    break;
                    
                case 0x201: // BCM 도어 상태
                    door_status = can_data[0];
                    printf("[IC/CAN] 도어 상태 수신: %s\r\n", 
                           door_status ? "닫힘" : "열림");
                    break;
            }
            
            // 디스플레이 업데이트
            SetEvent(Task_Display_Update, Event_Display_Update);
        }
    }
}