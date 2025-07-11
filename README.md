# Trampoline


이 프로젝트는 Trampoline RTOS(실시간 운영체제, OSEK/VDX 호환)와 C언어를 기반으로, 자동차의 ECU 구조와 CAN 통신을 소프트웨어로 시뮬레이션한 파일입니다.

## 주요 특징
- **BCM, PCM, IC** 기능별 ECU 분산 구조
- **소켓 기반 가상 CAN 버스**: TCP/IP로 여러 ECU가 메시지를 주고받음
- **Trampoline RTOS**: 태스크, 이벤트, OIL 파일 기반 실시간 태스크 관리
- **모듈화된 코드**: 각 ECU별로 기능 파일 분리, 헤더/구현 파일 분리

## virtual_car 프로젝트
`my_project/virtual_car/` 폴더에는 가상 차량 ECU 시뮬레이터가 구현되어 있습니다. 
자세한 내용은 해당 폴더의 README.md를 참고하세요.

---
## Building ViPER on UNIX shell:
```
$ cd viper
$ make
$ export VIPER_PATH=`pwd`
```
It is recommended to get the path to ViPER in the environment variables, and define in the ~/.bashrc or ~/.profile the command:

```
$ export VIPER_PATH=PATH_TO_TRAMPOLINE/viper
```

For example, add this command in bashrc
```
$ export VIPER_PATH="/home/CHeePark/trampoline_project/viper"

```
