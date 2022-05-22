cmake_minimum_required(VERSION 3.17)
project(MusicMech_Client)

set(CMAKE_CXX_STANDARD 20)

add_executable(MusicMech_Server
        main.cpp                ../src/main.h
        ../src/Server.cpp       ../src/Server.h
        ../src/UDP_Port.cpp     ../src/UDP_Port.h
        ../src/Utils.cpp        ../src/Utils.h
                                ../src/Random.h
        ../src/Game.cpp         ../src/Game.h
        ../src/Client.cpp       ../src/Client.h
        ../src/Joueur.cpp       ../src/Joueur.h ../src/Song.cpp ../src/Song.h ../src/RingShape.cpp ../src/RingShape.h ../src/RessourceLoader.cpp ../src/RessourceLoader.h ../src/Mechanic.cpp ../src/Mechanic.h ../src/Tower.cpp ../src/Tower.h)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(MusicMech_Server ${SFML_LIBRARIES})
endif()