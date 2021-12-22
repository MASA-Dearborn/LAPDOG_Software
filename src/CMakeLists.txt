add_library(
    pubsub
    broker/subscriber.cpp
    broker/broker.cpp
    broker/publisher.cpp
)

add_library(
    datalogger
    datalogger/dataLogger.cpp
    datalogger/fileHandler.cpp
    datalogger/fileWriter.cpp
)