cmake_minimum_required(VERSION 3.17)
project(MusicMech_Server)

set(CMAKE_CXX_STANDARD 20)

add_executable(MusicMech_Server
        main.cpp                ../src/main.h
        ../src/Network/Server.cpp ../src/Network/Server.h
        ../src/Network/UDP_Port.cpp ../src/Network/UDP_Port.h
        ../src/System/Utils.cpp ../src/System/Utils.h ../src/System/Random.h ../src/Network/PlayerInfo.h ../src/Network/Lobby.h ../src/Network/Lobby.cpp)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(MusicMech_Server ${SFML_LIBRARIES})
endif()