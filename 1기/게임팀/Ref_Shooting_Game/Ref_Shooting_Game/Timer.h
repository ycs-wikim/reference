#pragma once

#include "windows.h"
#include <functional>

using namespace std;


template <typename T>
struct TimerStruct
{
    T& Object;
    int sec;
    function<void(T&)> func;
};


template <typename T>
class Timer
{
public:
    static DWORD WINAPI TimerTR(LPVOID Param);
    HANDLE TimerStart(T& Object, int sec, function<void(T&)> func);

};

template <typename T>
DWORD WINAPI Timer<T>::TimerTR(LPVOID Param)
{
    TimerStruct<T>* ts = (TimerStruct<T>*)Param;

    Sleep(ts->sec);
    ts->func(ts->Object);

    delete ts;
    return 0;
}

template <typename T>
HANDLE Timer<T>::TimerStart(T& object, int sec, function<void(T&)> func)
{
    TimerStruct<T>* ts = new TimerStruct<T>{ object,sec,func };
    return CreateThread(NULL, 0, Timer::TimerTR, ts, 0, NULL);
}
