add_executable(
    unitTest
    test-IOInterface.cpp
    test-Main.cpp
    test-MessageHandler.cpp
    test-Messages.cpp
    test-PubSub.cpp
    test-StaticQueue.cpp
    test-Subscriber.cpp
    test-DataLogger.cpp
)

target_link_libraries(
    unitTest 
    Timer
    DataLogger
    gtest_main 
    pubsub
    IO
)

#gtest_discover_tests(tests)