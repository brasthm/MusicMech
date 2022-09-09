cmake_minimum_required(VERSION 3.17)
project(MusicMech_Server)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE MusicMech_SRC CONFIGURE_DEPENDS "../src/*.h" "../src/*.cpp")
add_executable(MusicMech_Server
        ${MusicMech_SRC} main.cpp)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(MusicMech_Server ${SFML_LIBRARIES} Threads::Threads)
endif()


