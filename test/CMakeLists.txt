add_executable(
    tests
    test-StaticQueue.cpp
)

target_link_libraries(tests gtest_main)

gtest_discover_tests(tests)