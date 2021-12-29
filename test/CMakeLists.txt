add_executable(
    tests
    test-StaticQueue.cpp
    test-Subscriber.cpp
    test-PubSub.cpp
    test-Main.cpp
)

target_link_libraries(
    tests 
    gtest_main 
    pubsub
)

#gtest_discover_tests(tests)