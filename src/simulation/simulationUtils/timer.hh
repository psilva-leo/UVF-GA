#ifndef TIMER_HH
#define TIMER_HH

#include <ctime>

class Timer {
private:
    timespec _time1, _time2;

public:
    Timer();

    // Timer control
    void start();
    void stop();

    // Timer getters
    double timesec();
    double timemsec();
    double timeusec();
    double timensec();
};

#endif // Timer_HH
