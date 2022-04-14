add_library(
    pubsub
    broker/subscriber.cpp
    broker/publisher.cpp
    broker/broker.cpp
)

add_library(
    IO
    IO/MessageHandler.cpp
    IO/IOInterface.cpp
    IO/CAN.cpp
    IO/TCP.cpp
    IO/I2C_Operations.cpp
    IO/I2C_UserOperations.cpp
    IO/I2C.cpp
    IO/SPI_Operations.cpp
    IO/SPI_UserOperations.cpp
    IO/SPI.cpp
    IO/UART.cpp
)
target_link_libraries(IO PUBLIC pubsub Timer)

add_library(
    Timer
    timer.cpp
)
target_link_libraries(Timer PUBLIC rt)

add_library(
    DataLogger
    datalogger/dataLogger.cpp
    datalogger/fileWriter.cpp
)
target_link_libraries(DataLogger PUBLIC pubsub Timer)

add_library(
    AirbrakeModule
    airbrake/RocketDeployment_data.cpp
    airbrake/RocketDeployment.cpp
    airbrake/AirbrakeController.cpp
)