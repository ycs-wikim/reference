#include "framework.h"
#include "sockettestclnt.h"

// 디버그 메시지 출력 여부, 언더바 지우면 출력
#define SHOW_DEBUG_LOG _

// 메시지 처리를 위한 버퍼
WCHAR buf[MAX];

// winsock2.h 사용을 위해 초기화
WSADATA wsaData;

// 클라이언트 소켓
SOCKET hSocket;

// 소켓 주소
SOCKADDR_IN servAddr;

// 소켓 변화 감지를 위한 set와 원본 훼손 방지를 위한 cpset
fd_set set, cpset;

// app_print 함수에서 문자열 출력할 좌표
int t_y;

// 각각 select와 recv 함수 반환값 저장
int fd_num, chk_conn;

// 클라이언트 접속 여부
bool clntConnected;

// 접속할 IP 주소
char connIP[] = "127.0.0.1";

// 접속할 포트 번호
int connPort = 10000;

// 버퍼 출력 함수
void app_print(HWND hWnd, HDC hdc, const wchar_t* str, POINT* pos);

// 연결 종료 함수
void termConn(HWND hWnd, HDC hdc);

DWORD WINAPI connServ(LPVOID Param)
{
    // Param을 HWND로 변환 및 저장
    HWND hWnd = (HWND)Param;
    // Device Context 할당
    HDC hdc = GetDC(hWnd);
    // select 함수에서 사용할 타임아웃
    timeval timeout;

    POINT apos[2] = {
    {310, 10},
    {SC_WIDTH - 390, 80}
    };

    // 그리기 영역 바탕을 투명하게 설정
    SetBkMode(hdc, TRANSPARENT);
    InvalidateRect(hWnd, NULL, 1);
    
    // winsock 초기화 실패 시
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        // 실패 메시지 버퍼에 입력
        wsprintf(buf, L"Winsock initialize failed.");

#ifdef SHOW_DEBUG_LOG
        app_print(hWnd, hdc, buf, &apos[0]); // SHOW_DEBUG_LOG 정의되었다면 출력
#endif

        // 스레드 종료
        termConn(hWnd, hdc);
    }
    else
        wsprintf(buf, L"Winsock initialize succeed.");

#ifdef SHOW_DEBUG_LOG
    app_print(hWnd, hdc, buf, &apos[0]);
#endif

    // 소켓 할당
    hSocket = socket(PF_INET, SOCK_STREAM, 0);
    // 소켓 할당 실패 시
    if (hSocket == INVALID_SOCKET)
    {
        // 실패 메시지 버퍼에 입력
        wsprintf(buf, L"Failed to create socket.");
#ifdef SHOW_DEBUG_LOG
        app_print(hWnd, hdc, buf, &apos[0]);
#endif
        termConn(hWnd, hdc);
    }
    else // 아니라면 성공 메시지 버퍼에 입력
        wsprintf(buf, L"Successfully created socket.");

#ifdef SHOW_DEBUG_LOG
    app_print(hWnd, hdc, buf, &apos[0]);
#endif

    // 메모리 초기화
    memset(&servAddr, 0x00, sizeof(servAddr));
    // IPv4 주소체계
    servAddr.sin_family = AF_INET;
    // char 문자열로 입력된 주소를 바이너리 형태로 저장
    inet_pton(AF_INET, connIP, &servAddr.sin_addr.s_addr);
    // htons == host to network small, 2바이트 호스트 방식 정렬 데이터를 네트워크 주소 방식 정렬
    // 포트번호를 portNumber 변수로 초기화
    servAddr.sin_port = htons(connPort);

#ifdef SHOW_DEBUG_LOG
    wsprintf(buf, L"Trying to connect...");
    app_print(hWnd, hdc, buf, &apos[0]);
#endif

    //연결 실패 시
    if (connect(hSocket, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
    {
        #ifdef SHOW_DEBUG_LOG
            wsprintf(buf, L"Connection failed.");
            app_print(hWnd, hdc, buf, &apos[0]);
        #endif
        // 스레드 종료
        termConn(hWnd, hdc);
    }
    else
    {
    #ifdef SHOW_DEBUG_LOG
        wsprintf(buf, L"Connection Succeed.");
        app_print(hWnd, hdc, buf, &apos[0]);
    #endif

        // fd_set 초기화
        FD_ZERO(&set);
        // fd_set에 hSocket 할당
        FD_SET(hSocket, &set);
        
        // 타임아웃 멤버 설정
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;

        while (1) {
            // 연결 상태가 0이라면 while문 탈출 및 스레드 종료
            if (clntConnected == 0)
                break;

            // fd_set의 원형 유지를 위한 복사
            cpset = set;
            // select문을 통한 변화 감지
            fd_num = select(set.fd_count, &cpset, 0, 0, &timeout);

            // 오류 발생 시 while문 탈출, 서버와 스레드 종료
            if (fd_num == -1)
                break;
            // 변화값이 없을 경우 처리하지 않고 반복
            else if (fd_num == 0)
                continue;
            
            // 소켓에 변화가 있을 경우(해당 if문은 없어도 될 것 같음)
            if (FD_ISSET(hSocket, &cpset)) {
                // 서버로부터 메시지 수신
                chk_conn = recv(hSocket, (char*)buf, MAX, 0);
                // 오류 발생 시
                if (chk_conn <= 0)
                {
                #ifdef SHOW_DEBUG_LOG
                    if (clntConnected) {
                        wsprintf(buf, L"Server error occurred.");
                        app_print(hWnd, hdc, buf, &apos[0]);
                    }
                #endif
                    break;
                }
                else // 정상적인 메시지 수신 시
                {
                    // 해당 메시지 출력
                    app_print(hWnd, hdc, buf, &apos[0]);
                }
            }
        }
    }
    wsprintf(buf, L"Disconnected.");
    app_print(hWnd, hdc, buf, &apos[0]);
    termConn(hWnd, hdc);
    return 0;
}

void app_print(HWND hWnd, HDC hdc, const wchar_t* str, POINT* pos)
{
    TextOut(hdc, pos->x, pos->y, str, lstrlenW(str));
    pos->y += 20;

    InvalidateRect(hWnd, NULL, 0);
}

void termConn(HWND hWnd, HDC hdc) {
    ReleaseDC(hWnd, hdc);
    closesocket(hSocket);
    WSACleanup();
    clntConnected = false;
    ExitThread(0);
}