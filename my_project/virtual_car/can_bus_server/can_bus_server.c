#include "can_protocol.h"

int main() {
    int server_fd, client_fd, max_fd, activity, i, valread, sd, new_socket;
    
    int client_socket[MAX_CLIENTS] = {0};
    // socket을 최대 MAX_CLIENTS까지 수용, 0 초기화는 socket 번호가 0보다 큼 
    struct sockaddr_in address;
    
    /* sockaddr은 IPv4 주소 표현
    IPv6는 IPv4의 주소부족 문제 해결위해 등장
    struct sockaddr_in {
    sa_family_t    sin_family;   // 주소 체계 (AF_INET)
    in_port_t      sin_port;     // 포트 번호
    struct in_addr sin_addr;     // IP 주소
    unsigned char  sin_zero[8];  // 패딩
    };
    */
    
    fd_set readfds;
    can_msg_t msg;

    /* fd_set: 소켓 집합 구조체
    사용 함수
    FD_ZERO(&readfds);            // readfds 초기화 (모든 비트 0으로)
    FD_SET(server_fd, &readfds);  // server_fd 소켓을 집합에 추가
    FD_CLR(sock, &readfds);       // sock를 집합에서 제거
    FD_ISSET(sock, &readfds);     // sock를 집합에 있는지 확인
    */

    server_fd = socket(AF_INET, SOCK_STREAM, 0); // 소켓 생성, IPv4프로토콜, SOCK_STREAM = TCP 소켓
    address.sin_family = AF_INET; //sin_family(주소체계 지정) = IPV4 
    address.sin_addr.s_addr = INADDR_ANY; // 서버 IP주소 지정 = (0.0.0.0) 
                                          // INADDR_ANY는 서버가 인터페이스에서 들어오는 모든 연결 요청을 수락(금지된 ip가 없다는 뜻)    
    address.sin_port = htons(PORT); // 서버가 사용할 포트 지정 = 9000
    
    bind(server_fd, (struct sockaddr *)&address, sizeof(address)); // 소켓에 주소 바인딩
    listen(server_fd, 3); // 
    //소켓 수신 대기 상태, 최대 3개의 연결 대기(임의로 숫자 바꿔도됨)
    /* TCP/IP 연결과정
    소켓 생성 → bind() → listen() → accept()
    */
    printf("CAN 버스 서버 시작 (포트 %d)\n", PORT);

    while(1) {
        FD_ZERO(&readfds);  // readfds 초기화, 모든 비트 0으로 설정
        FD_SET(server_fd, &readfds); //server_fd 소켓을 readfds에 추가, 해당 위치 비트 1
        max_fd = server_fd; //select()에 전달할 최대 소켓 번호 저장

        //최대 소켓 번호 갱신 및 클라이언트 소켓 readfds 추가
        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_socket[i];
            if (sd > 0) FD_SET(sd, &readfds); //client 소켓이 유효하면 readfds에 추가(해당 sd위치 비트 1로 만듦)
            if (sd > max_fd) max_fd = sd; // 최대 소켓 번호 갱신
        }

        activity = select(max_fd + 1, &readfds, NULL, NULL, NULL); //max_fd+1이유는 socket이 0부터 할당되는 것이 아님, 여러 소켓 모니터링
        //select()는 readfds에 설정된 소켓들 중 이벤트가 발생한 소켓의 비트를 1로 나머지는 0으로 만듦
        if(activity<0){ //activity(반환값)= select()가 감지한 이벤트 수
            printf("select 오류 발생\r\n");
            break;
        }                                                           
        
        //서버에 이벤트 발생 여부 확인(새로운 client 연결)
        if (FD_ISSET(server_fd, &readfds)) { //server_fd에 이벤트 발생(비트 1)시, 반환값=true(해당 소켓 위치 비트가 1=server_fd가 비트가 1, false는 server_fd가 비트가 0)
        // 서버 소켓에 이벤트 발생 = 새 클라이언트 연결 요청이 있는가?
            int addrlen = sizeof(address); //server_fd의 주소 길이
            new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen); //반환 값은 새로운 소켓 파일 번호(new_socket)
            //new socket 생성, 연결 수락
            for (i = 0; i < MAX_CLIENTS; i++) {
                if (client_socket[i] == 0) {
                    client_socket[i] = new_socket;
                    break;
                }
            }
        }

        // 데이터 수신 및 브로드캐스트
        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_socket[i];
            if (FD_ISSET(sd, &readfds)) { // sd(클라이언트 소켓)에 이벤트 발생(데이터 도착) 여부 확인
                valread = read(sd, &msg, sizeof(msg)); //sd로부터 데이터 msg에 저장
                if (valread == 0) { //varlead는 read()가 읽은 바이트 수, 성공시 > 0, 실패시 < 0, 연결 종료시 0
                    close(sd);
                    client_socket[i] = 0; //연결 종료했으므로 cient_socket[i] 비우기
                } 
                else if(valread < 0) {
                    printf("read 오류\r\n");
                }
                else { // 데이터가 성공적으로 읽혔을 브로드캐스트
                    for (int j = 0; j < MAX_CLIENTS; j++) {
                        if (client_socket[j] != 0 && j != i) { // j!=i는 자신에게는 보내지 않음
                            // 유효한 다른 클라이언트 소켓이면
                            // 다른 클라이언트에게 메시지 전송
                            int write_ret= write(client_socket[j], &msg, sizeof(msg));
                            if(write_ret < 0) {
                                printf("클라이언트 %d로 메시지 전송 실패\r\n", j);
                            }
                        }
                    }
                }
            }
        }
    }
}