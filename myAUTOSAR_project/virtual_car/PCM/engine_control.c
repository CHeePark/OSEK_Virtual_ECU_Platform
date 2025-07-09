#include "pcm_common.h"

bool engine_on = false; // 엔진 상태 (true: On, false: Off) 
int rpm = 0; // 엔진 RPM
extern char gear_pos; 
extern int acceleration; 

TASK(Task_Engine_Control) {
    while(1) {
        WaitEvent(Event_Engine_Change_Request);
        ClearEvent(Event_Engine_Change_Request);
        
        if (engine_on==true && rpm < 800) {
            rpm = 800; // 시동이 켜지면 기본 아이들링 RPM 설정
        } 
        else if (engine_on==false) {
            rpm = 0; // 시동이 꺼지면 RPM 0으로 설정
        }
        
        if (acceleration==1 && engine_on==true) {
                if(rpm < 6000 && gear_pos == 'd') 
                    rpm += 200; // 가속

                else if(rpm >= 6000 && gear_pos == 'd') {
                    rpm = 6000; // 최대 RPM 유지
                    printf("[PCM/엔진] ⚠️ 최대 RPM에 도달했습니다.\r\n");
                }
                else
                    printf("[PCM/엔진] ⚠️ 가속은 D 기어에서만 가능합니다.\r\n");

        }
        
        else if(acceleration==2 && engine_on==true) {
                if(rpm > 800 && gear_pos == 'd') 
                    rpm -= 200; // 감속

                else if(rpm <= 800 && gear_pos == 'd') {
                    rpm = 800; // 최소 RPM 유지
                    printf("[PCM/엔진] ⚠️ 최소 RPM에 도달했습니다.\r\n");
                }
                else
                    printf("[PCM/엔진] ⚠️ 감속은 D 기어에서만 가능합니다.\r\n");
        }

        else if(acceleration==0 && engine_on==true) { 
            printf("[PCM/엔진] ⚙️ 엔진이 켜졌습니다. 현재 RPM: %d\r\n", rpm);
            //continue; 
        }
        else {
            printf("[PCM/엔진] ⚠️ 엔진이 꺼졌습니다. 'e'를 눌러 엔진을 켜주세요.\r\n");
            
        }
        printf("[PCM/엔진] ⚙️ RPM: %d  Engine 점화: %s \r\n", rpm,engine_on ? "ON" : "OFF");
    }
    TerminateTask();
}