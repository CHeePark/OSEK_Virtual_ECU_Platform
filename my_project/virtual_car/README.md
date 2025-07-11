# Trampoline 기반 가상 차량 ECU 시뮬레이터 (virtual_car)

이 프로젝트는 Trampoline RTOS(실시간 운영체제, OSEK/VDX 호환)와 C언어를 기반으로, 자동차의 ECU 구조와 CAN 통신을 소프트웨어로 시뮬레이션한 파일입니다.

## 주요 특징
- **BCM, PCM, IC** 기능별 ECU 분산 구조
- **소켓 기반 가상 CAN 버스**: TCP/IP로 여러 ECU가 메시지를 주고받음
- **Trampoline RTOS**: 태스크, 이벤트, OIL 파일 기반 실시간 태스크 관리
- **모듈화된 코드**: 각 ECU별로 기능 파일 분리, 헤더/구현 파일 분리

## 폴더 구조
```
virtual_car/
├── BCM/   # 바디 제어(도어, 방향지시등)
├── PCM/   # 파워트레인 제어(엔진 점화 여부, rpm, 기어)
├── IC/    # 계기판(BCM 및 PCM data 표시)
└── can_bus_server/  # 가상 CAN 버스 서버 (TCP/IP)
```

## 실행 방법

### 1. 가상 CAN 버스 서버 실행
```bash
cd can_bus_server
gcc -o can_bus_server can_bus_server.c
./can_bus_server
```

### 2. 각 ECU(BCM, PCM, IC) 빌드 및 실행
각 ECU 폴더에서 다음을 실행:
```bash
cd virtual_car/PCM   # 또는 BCM, IC
goil --target=posix/linux  --templates=../../../goil/templates/ main_pcm.oil  #main_bcm.oil 또는 main_ic.oil
./make.py -s  # OIL 파일 기반 빌드
./car_pcm_exe   # 또는 car_bcm_exe, car_ic_exe 를 통한 실행
```

### 3. 시뮬레이션 동작
- 각 ECU는 서버에 연결되어 CAN 메시지를 IC파일에 송신
- ex) PCM에서 엔진 상태 변경 → IC에서 실시간 RPM/상태 표시

## 주요 파일 설명
- `can_bus_server.c` : 가상 CAN 버스 서버(TCP/IP, 브로드캐스트)
- `can_protocol.h`   : CAN 메시지 구조체 및 상수 정의
- `main_*.c` 등   : 각 ECU의 메인 진입점, RTOS 태스크/이벤트 관리
- `engine_control.c` 등 : 각 ECU의 기능별 구현
- `main_*.oil`       : 태스크/이벤트/소스 파일 지정 OIL 설정
- `*_can_client.c` : 각 ECU의 CAN 버스 클라이언트 함수
