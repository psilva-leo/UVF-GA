#include "timer.hh"

Timer::Timer() {
    clock_gettime(CLOCK_REALTIME, &_time1);
    clock_gettime(CLOCK_REALTIME, &_time2);
}

void Timer::start() {
    clock_gettime(CLOCK_REALTIME, &_time1);
}

void Timer::stop() {
    clock_gettime(CLOCK_REALTIME, &_time2);
}

double Timer::timesec() {
    return timensec()/1E9;
}

double Timer::timemsec()   {
    return timensec()/1E6;
}

double Timer::timeusec()   {
    return timensec()/1E3;
}

double Timer::timensec()   {
    return (_time2.tv_sec*1E9 + _time2.tv_nsec) - (_time1.tv_sec*1E9 + _time1.tv_nsec);
}
