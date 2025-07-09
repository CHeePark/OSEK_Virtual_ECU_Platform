#include "ic_common.h"

// 가상 CAN 메시지 수신 태스크
TASK(Task_CAN_Receiver) {
    while(1) {
        // CAN 메시지 대기 (가상)
        WaitEvent(Event_CAN_Message);
        ClearEvent(Event_CAN_Message);
        
        // CAN ID에 따라 다른 처리
        switch(can_msg_id) {
            case 0x100: // PCM 엔진 상태
                g_engine_status = can_data[0];
                g_engine_rpm = (can_data[1] << 8) | can_data[2];
                break;
            case 0x101: // PCM 속도, 기어
                g_vehicle_speed = (can_data[0] << 8) | can_data[1];
                g_gear_position = can_data[2];
                break;
            case 0x200: // BCM 방향지시등
                g_turn_signal_status = can_data[0];
                break;
            case 0x201: // BCM 도어 상태
                g_door_status = can_data[0];
                break;
        }
        
        // 디스플레이 업데이트
        SetEvent(Task_Display_Update, Event_Display_Update);
    }
}