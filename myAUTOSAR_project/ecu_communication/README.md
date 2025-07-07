🔧 계층별 상세 설명

### **MCAL/ECU Abstraction Layer (Priority 1)**
- **Task**: `Task_CanIf_RxIndication`
- **역할**: CAN 인터페이스 - 하드웨어로부터 CAN 메시지 수신
- **동작**:
  - 알람에 의해 100ms마다 활성화
  - CAN 메시지 수신 시뮬레이션
  - 상위 계층(PduR)에 PDU 수신 이벤트 전달

### **📦 BSW - PduR Layer (Priority 2)**
- **Task**: `Task_PduR_RxIndication`
- **역할**: PDU Router - 수신된 PDU를 분석하여 신호 추출
- **동작**:
  - PDU 수신 이벤트 대기
  - 수신된 PDU에서 의미있는 신호 데이터 처리
  - 애플리케이션 계층에 신호 처리 완료 이벤트 전달

### **🎯 ASW - Application Layer (Priority 3)**
- **Task**: `Task_Application_Process`
- **역할**: 최종 사용자 애플리케이션 로직
- **동작**:
  - 신호 처리 완료 이벤트 대기
  - 엔진 RPM, 온도 등 실제 차량 데이터 획득
  - 제어 로직 실행 (현재는 데이터 출력만)


## ⚡ 이벤트 기반 동기화

- **Event_PDU_Received**: CanIf → PduR 통신
- **Event_Signal_Available**: PduR → Application 통신
- **Alarm_Simulate_CAN_Rx**: 100ms 주기로 CAN 메시지 수신 시뮬레이션
