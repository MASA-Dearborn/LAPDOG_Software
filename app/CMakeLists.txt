
add_executable(main main.cpp)
target_link_libraries(main PUBLIC pubsub IO pthread DataLogger)
