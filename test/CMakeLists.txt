add_executable(
    tests
    test-IOInterface.cpp
    test-Main.cpp
    test-MessageHandler.cpp
    test-Messages.cpp
    test-PubSub.cpp
    test-StaticQueue.cpp
    test-Subscriber.cpp
)

target_link_libraries(
    tests 
    gtest_main 
    pubsub
    IO
)

#gtest_discover_tests(tests)