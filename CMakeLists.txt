cmake_minimum_required(VERSION 3.0.0)
project(lapdog VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_TOOLCHAIN_FILE TC-zynq.cmake)

add_compile_definitions(LISTEN_PORT=9015)

# Google Test Setup
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
include(CTest)
#enable_testing()

include_directories(include)
add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(test)

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)
