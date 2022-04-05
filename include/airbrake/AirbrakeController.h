#include "rtwtypes.h"
#include "rt_defines.h"
#include "RocketDeployment_types.h"
#include "RocketDeployment.h"
#include "broker/publisher.h"
#include "broker/subscriber.h"
#include "timer.h"

class AirbrakeController
{
public:
    AirbrakeController();
    ~AirbrakeController();

    void enableControl();
    void disableControl();

protected:
    Timer io_timer;

    pubsub::Subscriber<msg::real::ALTIMETER_COEFFS>* altimeter_coeffs;
    pubsub::Subscriber<msg::real::ALTIMETER_DATA>* altimeter_data;
    pubsub::Subscriber<msg::real::HUMIDITY_DATA>* humidity_data;
    pubsub::Subscriber<msg::real::BNO055_DATA_ACCEL>* accel_data;
}

void airbrake_controller_thread(union sigval data);