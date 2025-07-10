// ECU_A.c - 자동차 ECU 통신 시뮬레이션 프로그램
#include "tpl_os.h"    // Trampoline OS API 
#include <stdio.h>     // 표준 입출력

//-- Com 모듈: PDU에서 실제 신호(Signal) 값을 추출하는 가상 함수들--//
//실제로는 Pdy의 data에서 rpm,EngineTemp 값 추출 해야함
void Com_ReceiveSignal_EngineRpm(unsigned int* value) {
    // pointer를 사용하여 원본 값 수정
    *value = 2000; 
}
void Com_ReceiveSignal_EngineTemp(unsigned char* value) {
    *value = 95;
}
//-- Com 모듈: PDU에서 실제 신호 값을 추출하는 가상 함수들--//

//-- ASW계층 --//
// 수신된 엔진 데이터 저장할 전역 변수 선언
unsigned int g_engineRpm = 0;    // 엔진 RPM (회전수)
unsigned char g_engineTemp = 0;  // 엔진 온도

// 3단계: Application Task (애플리케이션 계층 - 최종 사용자 로직)
// priority: 3
TASK(Task_Application_Process) {
    while(1) { 
        WaitEvent(Event_Signal_Available); // "신호 처리 완료" 이벤트가 올 때까지 대기
        ClearEvent(Event_Signal_Available); // 이벤트 비트 클리어 이유? 
        //사용 이유: 다음 event가 이전 event와 같은 bit임을 방지
        
        // Com 모듈로부터 Signal 값을 전역 변수로 받아옴
        Com_ReceiveSignal_EngineRpm(&g_engineRpm);   // 엔진 RPM 값 
        Com_ReceiveSignal_EngineTemp(&g_engineTemp); // 엔진 온도 값

        //-- 결과 출력 --// 
        printf("----------------------------------------\r\n");
        printf(">> [Application] 데이터 처리 완료!\r\n");
        printf(">> 현재 엔진 RPM: %u rpm\r\n", g_engineRpm);
        printf(">> 현재 엔진 온도: %u °C\r\n", g_engineTemp);
        printf("----------------------------------------\r\n\r\n");
        //-- 결과 출력 --// 
    }
    TerminateTask(); // 태스크 종료 (실제로는 while(1)로 인해 도달하지 않음)
}

//--- BSW 계층(PduR, Com 모듈 시뮬레이션) ---//
// priority: 2
TASK(Task_PduR_RxIndication) {
    while(1) { 
        WaitEvent(Event_PDU_Received); 
        ClearEvent(Event_PDU_Received); 
        
        printf("[PduR] CAN PDU 수신! Com 모듈에 신호 처리 요청...\r\n");
        
        SetEvent(Task_Application_Process, Event_Signal_Available);
        // Event_Signal_Available을 Task_Application_Process에 전달
    }
    TerminateTask();
}

//--- MCAL/ECU Abstraction 계층(CanIf 시뮬레이션) ---//
// priority : 1 
TASK(Task_CanIf_RxIndication) {
    printf("[CanIf] CAN 메시지 수신! PduR에 전달...\r\n");
    
    SetEvent(Task_PduR_RxIndication, Event_PDU_Received);
    // 의미: Event_PDU_Received을 Task_PduR_RxIndication에 전달

    TerminateTask(); // 한 번 실행 후 종료 (알람에 의해 주기적으로 활성화됨)
}

// main 함수: 프로그램 시작점
int main(void) {
    printf("ECU_A 부팅 완료. CAN 메시지 수신 대기...\r\n\r\n");
    
    StartOS(stdAppmode);
    
    return 0; // 실제로는 StartOS에서 제어권을 넘겼기에 이 line은 실행되지 않음
}