
add_executable(main main.cpp)
target_link_libraries(main PUBLIC pubsub IO pthread DataLogger)

add_executable(i2c_app i2c_app.cpp)
target_link_libraries(i2c_app PUBLIC pubsub IO pthread DataLogger)

add_executable(can_app can_app.cpp)
target_link_libraries(can_app PUBLIC pubsub IO pthread DataLogger)

add_executable(spi_app spi_app.cpp)
target_link_libraries(spi_app PUBLIC pubsub IO pthread DataLogger)
