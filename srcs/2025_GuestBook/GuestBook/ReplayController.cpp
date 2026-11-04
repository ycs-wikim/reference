#include "ReplayController.h"
#include "Application.h"

void ReplayController::StartReplay(HWND hDrawWnd, vector<Stroke> copyStroke) {
    /// 리플레이 시작 시, 기존 스레드 완전 종료
    StopReplay();

    r_state = ReplayState::Running; // "재생 중"으로 상태 변경

    std::thread tempThread([=]() { // 'this' 캡처
        // ★★★ 1. 스레드 내부의 무한 루프 ★★★
        while (true) {

            // --- 2. 루프 시작 시 '중단' 확인 ---
            if (r_state == ReplayState::Stopped) {
                break; // 무한 루프 탈출
            }

            // --- 3. '일시정지' 확인 (대기 루프) ---
            while (r_state == ReplayState::Paused) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                // 일시정지 중에도 '중단' 요청은 확인해야 함
                if (r_state == ReplayState::Stopped) {
                    break;
                }
            }
            if (r_state == ReplayState::Stopped) {
                break; // 대기 루프 탈출 시 다시 확인
            }
            HDC hdc_clear = GetDC(hDrawWnd);
            if (hdc_clear) {
                RECT rc;
                GetClientRect(hDrawWnd, &rc);

                // (가장 간단한 방법: 윈도우 기본 배경색 브러시 사용)
                HBRUSH hBgBrush = (HBRUSH)(COLOR_WINDOW + 1);
                FillRect(hdc_clear, &rc, hBgBrush);

                ReleaseDC(hDrawWnd, hdc_clear);
            }
            // --- 4. 한 사이클 재생 (기존 로직) ---
            for (const auto& s : copyStroke) {
                for (size_t i = 1; i < s.points.size(); ++i) {

                    // ★ 5. 매 스텝마다 중단/일시정지 확인 (빠른 반응)
                    if (r_state == ReplayState::Stopped) break;
                    while (r_state == ReplayState::Paused) {
                        std::unique_lock<std::mutex> lock(m_cvMutex);
                        // 100ms 대기하되, Stopped 되면 즉시 깸
                        m_cv.wait_for(lock, std::chrono::milliseconds(100), [this] {
                            return r_state == ReplayState::Stopped; 
                            });
                        if (r_state == ReplayState::Stopped) break;
                    }
                    if (r_state == ReplayState::Stopped) break;

                    // (기존 GDI 로직)
                    Sleep(s.points[i].timestamp);
                        
                    HDC hdc = GetDC(hDrawWnd);
                    SetGraphicsMode(hdc, GM_ADVANCED); /// DASH, DOT 선 종류의 두께 1px이상 사용하기 위해 선언
                    LOGBRUSH lb = {};
                    lb.lbStyle = BS_SOLID;
                    lb.lbColor = s.color;
                    HPEN pen = ExtCreatePen(  /// 
                        PS_GEOMETRIC | s.penStyle,
                        s.penWidth,
                        &lb,
                        0, nullptr
                    );

                    HPEN oldPen = (HPEN)SelectObject(hdc, pen);

                    MoveToEx(hdc, s.points[i - 1].x, s.points[i - 1].y, nullptr);
                    LineTo(hdc, s.points[i].x, s.points[i].y);

                    SelectObject(hdc, oldPen);
                    DeleteObject(pen);
                    ReleaseDC(hDrawWnd, hdc);
                }
                if (r_state == ReplayState::Stopped) break; // 바깥쪽 for 루프 탈출
            }
            {
                std::unique_lock<std::mutex> lock(m_cvMutex);
                m_cv.wait_for(lock, std::chrono::milliseconds(2000), [this] { // Sleep 대체 대기하지만 stopped가 되면 넘어감
                    return r_state == ReplayState::Stopped;
                    });
            }

            // (한 사이클 재생 끝)
        }
        r_state = ReplayState::Stopped;
        });
    replayThread = std::move(tempThread);

}

void ReplayController::ToggleReplay() {
	
	if (r_state == ReplayState::Running) {
		r_state = ReplayState::Paused;
	}
	else if (r_state == ReplayState::Paused) {
		r_state = ReplayState::Running;
	}
	
}

void ReplayController::StopReplay() {
    if (r_state != ReplayState::Stopped) {
        r_state = ReplayState::Stopped;
        m_cv.notify_all(); // 깨우기
    }

    if (replayThread.joinable()) {
        replayThread.join(); // 종료대기
    }

    r_state = ReplayState::Stopped;
}