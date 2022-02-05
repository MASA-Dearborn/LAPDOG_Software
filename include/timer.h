#include <time.h>
#include <signal.h>
#include <errno.h>

class Timer
{
public:
    Timer();
    Timer(void (*handler)(union sigval), void* data_ptr, long int interval_ms, long int delay_ms);
    ~Timer();

    void startTimer();
    void stopTimer();

    void setIntervalMilliseconds(long int milliseconds);
    void setStartDelayMilliseconds(long int milliseconds);
    void setHandler(void (*handler)(union sigval));
    void setHandlerDataPointer(void* data_ptr);

private:
    timer_t timer = {0};
    struct itimerspec timer_specs = {0};
    struct sigevent sev = {0};

};