cmake_minimum_required(VERSION 3.17)
project(MusicMech_Client)

set(CMAKE_CXX_STANDARD 20)

add_executable(MusicMech_Client
        main.cpp                ../src/main.h
        ../src/Network/Server.cpp ../src/Network/Server.h
        ../src/Network/UDP_Port.cpp ../src/Network/UDP_Port.h
        ../src/System/Utils.cpp ../src/System/Utils.h
        ../src/System/Random.h
        ../src/Game.cpp         ../src/Game.h
        ../src/Network/Client.cpp ../src/Network/Client.h
        ../src/Entity/Joueur.cpp ../src/Entity/Joueur.h
        ../src/System/Song.cpp ../src/System/Song.h
        ../src/Graphics/RingShape.cpp ../src/Graphics/RingShape.h
        ../src/System/RessourceLoader.cpp ../src/System/RessourceLoader.h
        ../src/Mechanics/Mechanic.cpp ../src/Mechanics/Mechanic.h
        ../src/System/DJ.h
        ../src/Graphics/PlayerIndicator.cpp ../src/Graphics/PlayerIndicator.h
        ../src/Mechanics/Spread.cpp ../src/Mechanics/Spread.h
        ../src/LobbyMenu.cpp     ../src/LobbyMenu.h
        ../src/Network/Lobby.cpp ../src/Network/Lobby.h
        ../src/Mechanics/Tether.cpp ../src/Mechanics/Tether.h
        ../src/Graphics/ShiftColor.cpp ../src/Graphics/ShiftColor.h
        ../src/Graphics/ArrowShape.cpp ../src/Graphics/ArrowShape.h ../src/Entity/Entity.cpp ../src/Entity/Entity.h ../src/Entity/Totem.cpp ../src/Entity/Totem.h ../src/Mechanics/ActivateTotem.cpp ../src/Mechanics/ActivateTotem.h ../src/Mechanics/MoveEntity.cpp ../src/Mechanics/MoveEntity.h ../src/Entity/EntityManager.cpp ../src/Entity/EntityManager.h ../src/System/Debuff.cpp ../src/System/Debuff.h ../src/Mechanics/ApplyDebuff.cpp ../src/Mechanics/ApplyDebuff.h)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(MusicMech_Client ${SFML_LIBRARIES})
endif()