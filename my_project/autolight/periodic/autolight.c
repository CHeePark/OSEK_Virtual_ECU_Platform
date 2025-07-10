#include "tpl_os.h"
#include <stdio.h>

// 전역 변수 선언
int g_light_level = 100;
int g_headlight_status = 0;
int cnt_=5;
// StartupHook 함수
void StartupHook(void) {
  printf("오토라이트 ECU 시작.");
}

// Task_Read_Light_Sensor 로직
TASK(Task_Read_Light_Sensor) {

  g_light_level = (g_light_level > 20) ? (g_light_level - 20) : 100;
  printf("💡 밝기 센서: %d", g_light_level);
  SetEvent(Task_Control_Headlight, Event_Sensor_Read_Done);
  //SetEvent(이벤트 받을 태스크, 보낼 이벤트); 
  TerminateTask();
}

// Task_Control_Headlight 로직
TASK(Task_Control_Headlight)
// 헤드라이트 제어 태스크 정의
{
  while(cnt_ > 0) {
    cnt_--;
    printf("🚗 헤드라이트 제어 태스크 실행 중...\n");
    WaitEvent(Event_Sensor_Read_Done);
    //evenet를 기다리는 함수
    ClearEvent(Event_Sensor_Read_Done);
    // event를 지우는 함수(event 도착 시 이벤트 비트를 초기화)
    
    if (g_light_level < 50) {
      if (g_headlight_status == 0) {
        g_headlight_status = 1;
        printf("🚗 제어 로직: 어두움 감지. 헤드라이트 ON!\n");
      }
    } else {
      if (g_headlight_status == 1) {
        g_headlight_status = 0;
        printf("🚗 제어 로직: 밝음 감지. 헤드라이트 OFF!\n");
      }
    }
  }
  // cnt_ == 0이 되면 OS를 종료
  ShutdownOS(E_OK);
  TerminateTask();
}

// main 함수 (프로그램의 시작점)
// 이 부분이 추가되었습니다!
int main(void)
{
  // AUTOSAR OS를 시작합니다. APPMODE는 .oil 파일에 정의된 stdAppmode 입니다.
  StartOS(stdAppmode); 
  return 0;
}