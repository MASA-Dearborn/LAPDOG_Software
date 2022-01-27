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
    IO/I2C.cpp
    IO/I2C_Operations.cpp
    IO/SPI.cpp
    IO/UART.cpp
)
target_link_libraries(IO PUBLIC pubsub)