add_library(
    pubsub
    broker/subscriber.cpp
    broker/publisher.cpp
    broker/broker.cpp
)

add_library(
    IO
    IO/IOInterface.cpp
)