cmake_minimum_required(VERSION 3.17)
project(MusicMech_Server)

set(CMAKE_CXX_STANDARD 20)

add_executable(MusicMech_Server
        main.cpp                ../src/main.h
        ../src/Server.cpp       ../src/Server.h
        ../src/UDP_Port.cpp     ../src/UDP_Port.h
        ../src/Utils.cpp        ../src/Utils.h ../src/Random.h ../src/PlayerInfo.h ../src/Lobby.h ../src/Lobby.cpp)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(MusicMech_Server ${SFML_LIBRARIES})
endif()