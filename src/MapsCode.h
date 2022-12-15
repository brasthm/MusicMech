#ifndef MUSICMECH_CLIENT_MAPSCODE_H
#define MUSICMECH_CLIENT_MAPSCODE_H


#include "Mechanics/Mechanic.h"
#include "Mechanics/ZoomArena.h"
#include "Mechanics/RotateArena.h"
#include "Mechanics/MoveArena.h"
#include "Mechanics/SnapArena.h"
#include "Mechanics/AddArena.h"
#include "Mechanics/RemoveArena.h"
#include "Mechanics/Donut.h"
#include "Mechanics/Spread.h"
#include "Mechanics/NopeZone.h"
#include "Mechanics/Cone.h"
#include "Mechanics/ActivateTotem.h"
#include "Mechanics/MoveEntity.h"
#include "Mechanics/Tether.h"
#include "Mechanics/ApplyDebuff.h"
#include "Mechanics/DisplayImage.h"
#include "Mechanics/ClearArenaa.h"
#include "Mechanics/EndMap.h"
#include "Mechanics/TetherIndicator.h"
#include "Mechanics/TextIndicator.h"
#include "System/Song.h"

void getMechsFromCode(const std::string &id, std::vector<Mechanic*>& mechanics, Song& song, sf::Music &music, EntityManager &em);



void hystericNightGirl(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em);
void cloudNine(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em);
void adieu(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em);
void metal(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em);
void oblivion(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em);
void gas(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em);
void aiKotoba(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em);
void doggyGodStreet(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em);
void intoYou(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em);
void itte(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em);
void furachi(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em);
void lazySong(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em);
void thirdeye(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em);




#endif
