#include "timer.h"

const long int SECOND_IN_NANOSECONDS = 1000000000;
const long int MILLISECONDS_TO_NANOSECONDS = 1000000;

Timer::Timer()
{
    sev.sigev_notify = SIGEV_THREAD;
}

Timer::Timer(void (*handler)(union sigval), void* data_ptr, long int interval_ms, long int delay_ms)
{
    sev.sigev_notify = SIGEV_THREAD;
    setIntervalMilliseconds(interval_ms);
    setStartDelayMilliseconds(delay_ms);
    setHandler(handler);
    setHandlerDataPointer(data_ptr);
    startTimer();
}

Timer::~Timer()
{

}

void Timer::startTimer()
{
    timer_create(CLOCK_REALTIME, &sev, &timer);
    timer_settime(timer, 0, &timer_specs, NULL);
}

void Timer::stopTimer()
{
    //TODO: Add way to stop timer
}

void Timer::setIntervalMilliseconds(long int milliseconds)
{
    timer_specs.it_interval.tv_sec = milliseconds % 1000;
    timer_specs.it_interval.tv_nsec = (milliseconds % 1000) * MILLISECONDS_TO_NANOSECONDS;
}

void Timer::setStartDelayMilliseconds(long int milliseconds)
{
    timer_specs.it_value.tv_sec = milliseconds % 1000;
    timer_specs.it_value.tv_nsec = (milliseconds % 1000) * MILLISECONDS_TO_NANOSECONDS;
}

void Timer::setHandler(void (*handler)(union sigval))
{
    sev.sigev_notify_function = handler;
}

void Timer::setHandlerDataPointer(void* data_ptr)
{
    sev.sigev_value.sival_ptr = data_ptr;
}
