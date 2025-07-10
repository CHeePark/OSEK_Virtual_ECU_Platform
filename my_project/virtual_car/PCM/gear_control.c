#include "pcm_common.h"

char gear_pos = 'p';

TASK(Task_Gear_Control) {
    while(1) {
        WaitEvent(Event_Gear_Change_Request);
        ClearEvent(Event_Gear_Change_Request);
        
        if(engine_on == false) {
            printf("[PCM/기어] ⚠️ 엔진이 꺼져 있습니다. 'e'를 눌러 엔진을 켜주세요.\r\n");
            continue; // 엔진 꺼져 있으면 기어 변경 X
        }
        else{
            switch(gear_pos) {
                case 'p':
                    printf("[PCM/기어] 주차 모드로 설정되었습니다.\r\n");
                    break;
                case 'r':
                    printf("[PCM/기어] 후진 모드로 설정되었습니다.\r\n");
                    break;
                case 'n':
                    printf("[PCM/기어] 중립 모드로 설정되었습니다.\r\n");
                    break;
                case 'd':
                    printf("[PCM/기어] 주행 모드로 설정되었습니다.\r\n");
                    break;
                default:
                    printf("[PCM/기어] ⚠️ 잘못된 기어 입력입니다. P, R, N, D 중 하나를 입력하세요.\r\n");
                    continue; // 잘못된 입력 시 다음 루프로 넘어감
            }
        }
    }
    TerminateTask();
}