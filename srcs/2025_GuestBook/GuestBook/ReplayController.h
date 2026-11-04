#pragma once
#include <vector>
#include <WINDOWS.h>
#include <thread>
#include <functional>
#include <atomic>
#include <condition_variable>
#include <mutex>
#include "Stroke.h"

using OnReplayFinishedCallback = std::function<void(const std::vector<Stroke>&)>;

enum class ReplayState {
	Stopped,  // 완전 멈춤 (초기 상태)
	Running,  // 재생 중
	Paused,   // 일시정지
	Stopping  // 중단 요청 (Clear 버튼)
};

class ReplayController
{
public:
	  ~ReplayController() {
		  StopReplay();
	  }
	void StartReplay(HWND drawWindowHwnd, std::vector<Stroke> copyStroke);
	bool IsReplaying() const { return r_state != ReplayState::Stopped;}
	ReplayState GetState() const { return r_state; }
	void ToggleReplay();
	void StopReplay();

private:

	std::thread replayThread;
	std::condition_variable m_cv;
	std::mutex m_cvMutex;
	std::vector<Stroke> replayStrokes;

	std::atomic<ReplayState> r_state = ReplayState::Stopped;
	bool isPaused = false;
	bool stopRequested = false;
};