#include "MapsCode.h"


void getMechsFromCode(const std::string& id, std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em)
{
	if (id == "0")
		hystericNightGirl(mechanics, song, music, em);
	if (id == "1790032")
		cloudNine(mechanics, song, music, em);
	if (id == "1252820")
		adieu(mechanics, song, music, em);
	if (id == "522233")
		metal(mechanics, song, music, em);
	if (id == "1343133")
		oblivion(mechanics, song, music, em);
	if (id == "826430")
		gas(mechanics, song, music, em);
	if (id == "1772712")
		aiKotoba(mechanics, song, music, em);
	if (id == "1742219")
		doggyGodStreet(mechanics, song, music, em);
	if (id == "301830")
		intoYou(mechanics, song, music, em);
	if (id == "1119169")
		itte(mechanics, song, music, em);
    if (id == "1493511")
        furachi(mechanics, song, music, em);
    if (id == "30328")
        lazySong(mechanics, song, music, em);
    if (id == "239584")
        thirdeye(mechanics, song, music, em);
}

void hystericNightGirl(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em)
{

    // Intro
    song.addCheckpoint(0, 0);
    mechanics.emplace_back(new MoveEntity(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_POS, { 200, 200 }), 700, true));
    mechanics.emplace_back(new MoveEntity(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_POS, { 200, 800 }), 700, true));
    mechanics.emplace_back(new MoveEntity(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_POS, { 800, 200 }), 700, true));
    mechanics.emplace_back(new MoveEntity(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_POS, { 800, 800 }), 700, true));
    mechanics.emplace_back(new ApplyDebuff(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DebuffType::DEBUFF_ROOT, 52));
    mechanics.emplace_back(new ApplyDebuff(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DebuffType::DEBUFF_ROOT, 52));
    mechanics.emplace_back(new ApplyDebuff(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), DebuffType::DEBUFF_ROOT, 52));
    mechanics.emplace_back(new ApplyDebuff(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), DebuffType::DEBUFF_ROOT, 52));

    mechanics.emplace_back(new DisplayImage(8, "Beatmaps/0/0.png", 8, Target(TARGET_POS, { 160, 400 })));
    mechanics.emplace_back(new DisplayImage(20, "Beatmaps/0/1.png", 12, Target(TARGET_POS, { 30, 250 })));
    mechanics.emplace_back(new DisplayImage(20, "Beatmaps/0/2.png", 8, Target(TARGET_POS, { 315, 450 })));
    mechanics.emplace_back(new DisplayImage(32, "Beatmaps/0/3.png", 12, Target(TARGET_POS, { 50, 250 })));
    mechanics.emplace_back(new DisplayImage(32, "Beatmaps/0/4.png", 8, Target(TARGET_POS, { 200, 540 })));


    // Note
    song.addCheckpoint(17, 33);
    mechanics.emplace_back(new Spread(64, 250, 4, 32, Target(TARGET_POS, { 500, 500 })));

    mechanics.emplace_back(new DisplayImage(64, "Beatmaps/0/5.png", 32, Target(TARGET_POS, { 270, 15 })));
    mechanics.emplace_back(new DisplayImage(64, "Beatmaps/0/6.png", 24, Target(TARGET_POS, { 480, 380 })));
    mechanics.emplace_back(new DisplayImage(64, "Beatmaps/0/7.png", 16, Target(TARGET_POS, { 250, 810 })));
    mechanics.emplace_back(new DisplayImage(64, "Beatmaps/0/8.png", 12, Target(TARGET_POS, { 15, 540 })));

    // Lien

    song.addCheckpoint(32, 64.1);

    mechanics.emplace_back(new ActivateTotem(64.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new ActivateTotem(64.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));

    mechanics.emplace_back(new MoveEntity(64.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 100, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(64.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 900, 500 }), 1000, true));

    mechanics.emplace_back(new MoveEntity(74, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 400, 500 }), 200, false));
    mechanics.emplace_back(new MoveEntity(74, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 600, 500 }), 200, false));

    mechanics.emplace_back(new Tether(80, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_TOTEMS, 1), 300, 16, true, false));

    mechanics.emplace_back(new DisplayImage(80, "Beatmaps/0/9.png", 16, Target(TARGET_POS, { 115, 200 })));
    mechanics.emplace_back(new DisplayImage(80, "Beatmaps/0/10.png", 8, Target(TARGET_POS, { 140, 600 })));

    mechanics.emplace_back(new MoveEntity(80, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 100, 100 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(80, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 900, 900 }), 1000, true));

    mechanics.emplace_back(new MoveEntity(82, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 400, 400 }), 200, false));
    mechanics.emplace_back(new MoveEntity(82, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 600, 600 }), 200, false));


    mechanics.emplace_back(new DisplayImage(96, "Beatmaps/0/12.png", 16, Target(TARGET_POS, { 115, 200 })));
    mechanics.emplace_back(new DisplayImage(96, "Beatmaps/0/13.png", 14, Target(TARGET_POS, { 615, 400 })));
    mechanics.emplace_back(new DisplayImage(96, "Beatmaps/0/11.png", 8, Target(TARGET_POS, { 300, 750 })));


    mechanics.emplace_back(new Tether(96, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_TOTEMS, 1), 400, 16, true, true));

    mechanics.emplace_back(new ActivateTotem(96, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));
    mechanics.emplace_back(new ActivateTotem(96, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false));



    // Note
    song.addCheckpoint(48, 97);

    mechanics.emplace_back(new DisplayImage(112, "Beatmaps/0/14.png", 16, Target(TARGET_POS, { 145, 35 })));
    mechanics.emplace_back(new DisplayImage(112, "Beatmaps/0/15.png", 12, Target(TARGET_POS, { 175, 840 })));

    mechanics.emplace_back(new NopeZone(112, 500, 500, 0, 16, Target(TARGET_POS, { 250, 250 })));

    mechanics.emplace_back(new DisplayImage(124, "Beatmaps/0/16.png", 12, Target(TARGET_POS, { 50, 290 })));
    mechanics.emplace_back(new DisplayImage(124, "Beatmaps/0/17.png", 8, Target(TARGET_POS, { 220, 600 })));

    // Mini situation

    song.addCheckpoint(57, 128);

    for (int i = 0; i < 8; i++) {
        if (i == 3) {
            mechanics.emplace_back(new Tether(136 + 8 * i, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_POS, { 500, 500 }), 400, 8, false, false));
            mechanics.emplace_back(new Tether(136 + 8 * i, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_POS, { 500, 500 }), 400, 8, false, false));
            mechanics.emplace_back(new Tether(136 + 8 * i, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_POS, { 500, 500 }), 400, 8, false, false));
            mechanics.emplace_back(new Tether(136 + 8 * i, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_POS, { 500, 500 }), 400, 8, false, false));

        }
        else if (i == 7) {
            mechanics.emplace_back(new Spread(132.5 + 8 * i, 150, 4, 4, Target(TARGET_POS, { 500, 500 })));
        }
        else {
            mechanics.emplace_back(new Spread(132 + 8 * i, 150, 1, 4, Target(TARGET_POS, { 200, 200 })));
            mechanics.emplace_back(new Spread(132 + 8 * i, 150, 1, 4, Target(TARGET_POS, { 200, 800 })));
            mechanics.emplace_back(new Spread(132 + 8 * i, 150, 1, 4, Target(TARGET_POS, { 800, 200 })));
            mechanics.emplace_back(new Spread(132 + 8 * i, 150, 1, 4, Target(TARGET_POS, { 800, 800 })));

            mechanics.emplace_back(new Spread(136 + 8 * i, 150, 2, 4, Target(TARGET_POS, { 300, 500 })));
            mechanics.emplace_back(new Spread(136 + 8 * i, 150, 2, 4, Target(TARGET_POS, { 700, 500 })));
        }

    }

    mechanics.emplace_back(new EndMap(200));

}

void cloudNine(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em)
{
    // Couplet 1
    song.addCheckpoint(0, 0);
    song.addCheckpoint(9, 16);
    mechanics.emplace_back(new Spread(20, 250, 1, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(28, 250, 2, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(37, 250, 3, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(44, 250, 4, 4, Target(TARGET_POS, { 500, 500 })));

    // Couplet 2
    song.addCheckpoint(33, 50);

    mechanics.emplace_back(new Tether(54, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW), 600, 4, false, false));
    mechanics.emplace_back(new Tether(54, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW), 600, 4, false, false));

    mechanics.emplace_back(new Tether(60, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW), 200, 4, true, false));
    mechanics.emplace_back(new Tether(60, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW), 200, 4, true, false));

    // Refrain

    song.addCheckpoint(43, 64);

    for (int ii = 0; ii < 8; ii++) {
        int i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(64 + 4 * i, 150 + 50 * i, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(65 + 4 * i, 150 + 50 * i, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(66 + 4 * i, 150 + 50 * i, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(67 + 4 * i, 150 + 50 * i, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    }

    // Couplet 1

    song.addCheckpoint(66, 96);


    mechanics.emplace_back(new Cone(100, 30, 1000, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(108, 30, 1000, 2, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(117, 30, 1000, 3, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(124, 30, 1000, 4, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));

    // Couplet 2

    song.addCheckpoint(90, 130);

    mechanics.emplace_back(new NopeZone(134, 500, 1000, 0, 4, Target(TARGET_POS, { 0, 0 })));
    mechanics.emplace_back(new NopeZone(142, 500, 1000, 0, 4, Target(TARGET_POS, { 500, 0 })));

    mechanics.emplace_back(new Tether(134, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW), 600, 4, false, false));
    mechanics.emplace_back(new Tether(134, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW), 600, 4, false, false));

    mechanics.emplace_back(new Tether(142, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW), 200, 4, true, false));
    mechanics.emplace_back(new Tether(142, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW), 200, 4, true, false));


    // Refrain 

    song.addCheckpoint(100, 144);

    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new Cone(144 + i * 4, 15 + 15 * i, 2000, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Cone(145 + i * 4, 15 + 15 * i, 2000, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Cone(146 + i * 4, 15 + 15 * i, 2000, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Cone(147 + i * 4, 15 + 15 * i, 2000, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    }

    // Couplet 1

    song.addCheckpoint(123, 176);

    mechanics.emplace_back(new Spread(180, 250, 1, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Cone(188, 30, 1000, 2, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(197, 250, 3, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Cone(204, 30, 1000, 4, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));

    // Couplet 2

    song.addCheckpoint(145, 208);

    mechanics.emplace_back(new NopeZone(212, 500, 1000, 0, 4, Target(TARGET_POS, { 0, 0 })));
    mechanics.emplace_back(new NopeZone(216, 1000, 500, 0, 4, Target(TARGET_POS, { 0, 0 })));
    mechanics.emplace_back(new NopeZone(220, 500, 1000, 0, 4, Target(TARGET_POS, { 500, 0 })));
    mechanics.emplace_back(new NopeZone(224, 1000, 500, 0, 4, Target(TARGET_POS, { 0, 500 })));

    mechanics.emplace_back(new Tether(212, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW), 600, 4, false, false));
    mechanics.emplace_back(new Tether(212, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW), 600, 4, false, false));

    mechanics.emplace_back(new Tether(216, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW), 200, 4, true, false));
    mechanics.emplace_back(new Tether(216, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW), 200, 4, true, false));


    mechanics.emplace_back(new Tether(220, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW), 600, 4, false, false));
    mechanics.emplace_back(new Tether(220, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW), 600, 4, false, false));

    mechanics.emplace_back(new Tether(224, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW), 200, 4, true, false));
    mechanics.emplace_back(new Tether(224, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW), 200, 4, true, false));


    // Refrain

    song.addCheckpoint(180, 256);

    mechanics.emplace_back(new NopeZone(268, 500, 1000, 0, 16, Target(TARGET_POS, { 0, 0 })));


    for (int i = 0; i < 3; i++) {
        mechanics.emplace_back(new Spread(256 + 4 * i, 150 + 30 * i, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(257 + 4 * i, 150 + 30 * i, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Cone(258 + i * 4, 15 + 15 * i, 2000, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Cone(259 + i * 4, 15 + 15 * i, 2000, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    }

    mechanics.emplace_back(new NopeZone(284, 500, 1000, 0, 16, Target(TARGET_POS, { 500, 0 })));

    for (int i = 0; i < 4; i++) {
        mechanics.emplace_back(new Spread(272 + 4 * i, 150 + 30 * i, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(273 + 4 * i, 150 + 30 * i, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
        mechanics.emplace_back(new Cone(274 + i * 4, 15 + 15 * i, 2000, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Cone(275 + i * 4, 15 + 15 * i, 2000, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    }



    mechanics.emplace_back(new Spread(292, 250, 4, 4, Target(TARGET_POS, { 300, 300 })));
    mechanics.emplace_back(new Spread(296, 200, 4, 4, Target(TARGET_POS, { 400, 400 })));
    mechanics.emplace_back(new Spread(300, 150, 4, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(304, 100, 4, 4, Target(TARGET_POS, { 600, 600 })));
    mechanics.emplace_back(new Spread(308, 50, 4, 4, Target(TARGET_POS, { 700, 700 })));

    mechanics.emplace_back(new EndMap(310));
}


void adieu(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em)
{
    // INTRO

    song.addCheckpoint(0, 0);

    mechanics.emplace_back(new ActivateTotem(0, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new MoveEntity(0, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 200 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(1, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanics.emplace_back(new MoveEntity(1, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 200 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanics.emplace_back(new MoveEntity(2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 200 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(3, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));
    mechanics.emplace_back(new MoveEntity(3, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 200 }), 1000, true));


    mechanics.emplace_back(new MoveEntity(4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 400 }), 400, false));
    mechanics.emplace_back(new MoveEntity(5, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 400 }), 400, false));
    mechanics.emplace_back(new MoveEntity(6, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 400 }), 400, false));
    mechanics.emplace_back(new MoveEntity(7, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 400 }), 400, false));

    mechanics.emplace_back(new MoveEntity(8, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 600 }), 400, false));
    mechanics.emplace_back(new MoveEntity(9, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 600 }), 400, false));
    mechanics.emplace_back(new MoveEntity(10, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 600 }), 400, false));
    mechanics.emplace_back(new MoveEntity(11, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 600 }), 400, false));


    mechanics.emplace_back(new MoveEntity(12, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 800 }), 400, false));
    mechanics.emplace_back(new MoveEntity(13, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 800 }), 400, false));
    mechanics.emplace_back(new MoveEntity(14, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 800 }), 400, false));
    mechanics.emplace_back(new MoveEntity(15, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 800 }), 400, false));

    mechanics.emplace_back(new Tether(32, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 200, 16, true, true));
    mechanics.emplace_back(new Tether(32, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 200, 12, true, true));
    mechanics.emplace_back(new Tether(32, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 200, 8, true, true));
    mechanics.emplace_back(new Tether(32, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 200, 4, true, true));



    // Couplet 1

    song.addCheckpoint(14, 31);

    mechanics.emplace_back(new ActivateTotem(31, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new MoveEntity(31, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 800 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(32, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanics.emplace_back(new MoveEntity(32, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 800 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(32, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanics.emplace_back(new MoveEntity(32, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 800 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(32, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));
    mechanics.emplace_back(new MoveEntity(32, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 800 }), 1000, true));


    for (int ii = 0; ii < 4; ii++) {
        float i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(32 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(33 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(34 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(35 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));

        if (i != 3) {
            mechanics.emplace_back(new MoveEntity(32 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 600 - i * 200 }), 400, false));
            mechanics.emplace_back(new MoveEntity(33 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 600 - i * 200 }), 400, false));
            mechanics.emplace_back(new MoveEntity(34 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 600 - i * 200 }), 400, false));
            mechanics.emplace_back(new MoveEntity(35 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 600 - i * 200 }), 400, false));
        }

    }

    for (int ii = 0; ii < 4; ii++) {
        float i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(48 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(49 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(50 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(51 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));

        if (i == 0) {
            mechanics.emplace_back(new MoveEntity(48 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 400 }), 400, false));
            mechanics.emplace_back(new MoveEntity(49 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 400 }), 400, false));
            mechanics.emplace_back(new MoveEntity(50 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 400 }), 400, false));
            mechanics.emplace_back(new MoveEntity(51 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 400 }), 400, false));
        }
        if (i == 1) {
            mechanics.emplace_back(new MoveEntity(48 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 600 }), 400, false));
            mechanics.emplace_back(new MoveEntity(49 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 200, 400 }), 400, false));
            mechanics.emplace_back(new MoveEntity(50 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 200 }), 400, false));
            mechanics.emplace_back(new MoveEntity(51 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 600 }), 400, false));
        }
        if (i == 2) {
            mechanics.emplace_back(new MoveEntity(48 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 800 }), 400, false));
            mechanics.emplace_back(new MoveEntity(49 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 200, 200 }), 400, false));
            mechanics.emplace_back(new MoveEntity(50 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 800, 200 }), 400, false));
            mechanics.emplace_back(new MoveEntity(51 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 800 }), 400, false));
        }

    }

    // Couplet 2 

    song.addCheckpoint(30, 64);

    mechanics.emplace_back(new ActivateTotem(64, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new MoveEntity(64, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 800 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(64, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanics.emplace_back(new MoveEntity(64, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 200, 200 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(64, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanics.emplace_back(new MoveEntity(64, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 800, 200 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(64, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));
    mechanics.emplace_back(new MoveEntity(64, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 800 }), 1000, true));


    mechanics.emplace_back(new Tether(68, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 100, 4, true, false));
    mechanics.emplace_back(new Tether(68, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 100, 4, true, false));
    mechanics.emplace_back(new Tether(68, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 100, 4, true, false));
    mechanics.emplace_back(new Tether(68, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 100, 4, true, false));

    mechanics.emplace_back(new Tether(72, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 100, 4, true, false));
    mechanics.emplace_back(new Tether(72, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 100, 4, true, false));
    mechanics.emplace_back(new Tether(72, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 100, 4, true, false));
    mechanics.emplace_back(new Tether(72, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 100, 4, true, false));

    mechanics.emplace_back(new Tether(76, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 100, 4, true, false));
    mechanics.emplace_back(new Tether(76, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 100, 4, true, false));
    mechanics.emplace_back(new Tether(76, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 100, 4, true, false));
    mechanics.emplace_back(new Tether(76, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 100, 4, true, false));

    mechanics.emplace_back(new Tether(80, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 100, 4, true, false));
    mechanics.emplace_back(new Tether(80, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 100, 4, true, false));
    mechanics.emplace_back(new Tether(80, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 100, 4, true, false));
    mechanics.emplace_back(new Tether(80, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 100, 4, true, false));



    // Refrain

    song.addCheckpoint(39, 79);

    mechanics.emplace_back(new ActivateTotem(79, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new MoveEntity(79, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 800 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(79, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanics.emplace_back(new MoveEntity(79, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 200, 200 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(79, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanics.emplace_back(new MoveEntity(79, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 800, 200 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(79, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));
    mechanics.emplace_back(new MoveEntity(79, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 800 }), 1000, true));

    for (int ii = 0; ii < 4; ii++) {
        float i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(80 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(81 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(82 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(83 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));

        if (ii < 2) {
            mechanics.emplace_back(new MoveEntity(80 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (i + 1) - 5 * PI / 4),  500 + 424 * std::sin(PI / 8 * (i + 1) - 5 * PI / 4) }), 400, false));
            mechanics.emplace_back(new MoveEntity(81 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (i + 1) - 3 * PI / 4),  500 + 424 * std::sin(PI / 8 * (i + 1) - 3 * PI / 4) }), 400, false));
            mechanics.emplace_back(new MoveEntity(82 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (i + 1) - 1 * PI / 4),  500 + 424 * std::sin(PI / 8 * (i + 1) - 1 * PI / 4) }), 400, false));
            mechanics.emplace_back(new MoveEntity(83 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (i + 1) - 7 * PI / 4),  500 + 424 * std::sin(PI / 8 * (i + 1) - 7 * PI / 4) }), 400, false));
        }
        else {
            mechanics.emplace_back(new MoveEntity(80 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (i - 1) - 5 * PI / 4),  500 + 424 * std::sin(PI / 8 * (i - 1) - 5 * PI / 4) }), 400, false));
            mechanics.emplace_back(new MoveEntity(81 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (i - 1) - 3 * PI / 4),  500 + 424 * std::sin(PI / 8 * (i - 1) - 3 * PI / 4) }), 400, false));
            mechanics.emplace_back(new MoveEntity(82 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (i - 1) - 1 * PI / 4),  500 + 424 * std::sin(PI / 8 * (i - 1) - 1 * PI / 4) }), 400, false));
            mechanics.emplace_back(new MoveEntity(83 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (i - 1) - 7 * PI / 4),  500 + 424 * std::sin(PI / 8 * (i - 1) - 7 * PI / 4) }), 400, false));
        }

    }

    for (int ii = 0; ii < 4; ii++) {
        float i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(96 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(97 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(98 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(99 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));

        if (ii < 2) {
            mechanics.emplace_back(new MoveEntity(96 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (2 - i - 1) - 5 * PI / 4),  500 + 424 * std::sin(PI / 8 * (2 - i - 1) - 5 * PI / 4) }), 400, false));
            mechanics.emplace_back(new MoveEntity(97 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (2 - i - 1) - 3 * PI / 4),  500 + 424 * std::sin(PI / 8 * (2 - i - 1) - 3 * PI / 4) }), 400, false));
            mechanics.emplace_back(new MoveEntity(98 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (2 - i - 1) - 1 * PI / 4),  500 + 424 * std::sin(PI / 8 * (2 - i - 1) - 1 * PI / 4) }), 400, false));
            mechanics.emplace_back(new MoveEntity(99 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (2 - i - 1) - 7 * PI / 4),  500 + 424 * std::sin(PI / 8 * (2 - i - 1) - 7 * PI / 4) }), 400, false));
        }
        else {
            mechanics.emplace_back(new MoveEntity(96 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (2 - i + 1) - 5 * PI / 4),  500 + 424 * std::sin(PI / 8 * (2 - i + 1) - 5 * PI / 4) }), 400, false));
            mechanics.emplace_back(new MoveEntity(97 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (2 - i + 1) - 3 * PI / 4),  500 + 424 * std::sin(PI / 8 * (2 - i + 1) - 3 * PI / 4) }), 400, false));
            mechanics.emplace_back(new MoveEntity(98 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (2 - i + 1) - 1 * PI / 4),  500 + 424 * std::sin(PI / 8 * (2 - i + 1) - 1 * PI / 4) }), 400, false));
            mechanics.emplace_back(new MoveEntity(99 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 500 + 424 * std::cos(PI / 8 * (2 - i + 1) - 7 * PI / 4),  500 + 424 * std::sin(PI / 8 * (2 - i + 1) - 7 * PI / 4) }), 400, false));
        }

    }

    // Couplet 1

    song.addCheckpoint(60, 112);

    mechanics.emplace_back(new ActivateTotem(112, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));
    mechanics.emplace_back(new ActivateTotem(113, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false));
    mechanics.emplace_back(new ActivateTotem(114, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), false));
    mechanics.emplace_back(new ActivateTotem(115, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), false));


    mechanics.emplace_back(new ActivateTotem(116, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new ActivateTotem(117, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanics.emplace_back(new ActivateTotem(118, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanics.emplace_back(new ActivateTotem(119, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));

    mechanics.emplace_back(new MoveEntity(116, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 200 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(116, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 200 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(116, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 200 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(116, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 200 }), 1000, true));

    for (int ii = 0; ii < 4; ii++) {
        float i = static_cast<float>(ii);
        if (ii == 0) {
            mechanics.emplace_back(new Spread(120 + i * 2, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
            mechanics.emplace_back(new Spread(121 + i * 2, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
            mechanics.emplace_back(new Spread(120 + i * 2, 100, 1, 2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
            mechanics.emplace_back(new Spread(121 + i * 2, 100, 1, 2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));
        }
        else {
            mechanics.emplace_back(new Spread(120 + i * 2, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
            mechanics.emplace_back(new Spread(121 + i * 2, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
            mechanics.emplace_back(new Spread(120 + i * 2, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
            mechanics.emplace_back(new Spread(121 + i * 2, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));
        }


        if (i != 3) {
            mechanics.emplace_back(new MoveEntity(120 + i * 2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 400 + i * 200 }), 400, false));
            mechanics.emplace_back(new MoveEntity(121 + i * 2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 400 + i * 200 }), 400, false));
            mechanics.emplace_back(new MoveEntity(120 + i * 2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 400 + i * 200 }), 400, false));
            mechanics.emplace_back(new MoveEntity(121 + i * 2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 400 + i * 200 }), 400, false));
        }

    }

    for (int ii = 0; ii < 4; ii++) {
        float i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(129 + i * 2, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(128 + i * 2, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(129 + i * 2, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(128 + i * 2, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));

        if (i != 3) {
            mechanics.emplace_back(new MoveEntity(129 + i * 2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 600 - i * 200 }), 400, false));
            mechanics.emplace_back(new MoveEntity(128 + i * 2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 600 - i * 200 }), 400, false));
            mechanics.emplace_back(new MoveEntity(129 + i * 2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 600 - i * 200 }), 400, false));
            mechanics.emplace_back(new MoveEntity(128 + i * 2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 600 - i * 200 }), 400, false));
        }

    }

    mechanics.emplace_back(new Spread(136, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(137, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(136, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(137, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));

    mechanics.emplace_back(new MoveEntity(136, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 400 }), 400, false));
    mechanics.emplace_back(new MoveEntity(137, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 400 }), 400, false));
    mechanics.emplace_back(new MoveEntity(136, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 400 }), 400, false));
    mechanics.emplace_back(new MoveEntity(137, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 400 }), 400, false));


    mechanics.emplace_back(new Spread(139, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(138, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(139, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(138, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));

    mechanics.emplace_back(new MoveEntity(139, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 600 }), 400, false));
    mechanics.emplace_back(new MoveEntity(138, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 600 }), 400, false));
    mechanics.emplace_back(new MoveEntity(139, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 600 }), 400, false));
    mechanics.emplace_back(new MoveEntity(138, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 600 }), 400, false));


    mechanics.emplace_back(new Spread(140, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(141, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(140, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(141, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));

    mechanics.emplace_back(new MoveEntity(140, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 800 }), 400, false));
    mechanics.emplace_back(new MoveEntity(141, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 800 }), 400, false));
    mechanics.emplace_back(new MoveEntity(140, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 800 }), 400, false));
    mechanics.emplace_back(new MoveEntity(141, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 800 }), 400, false));

    mechanics.emplace_back(new Spread(142, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(143, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(142, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(143, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));





    mechanics.emplace_back(new Spread(144, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(145, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(145, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(144, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));

    mechanics.emplace_back(new MoveEntity(144, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 600 }), 400, false));
    mechanics.emplace_back(new MoveEntity(145, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 600 }), 400, false));
    mechanics.emplace_back(new MoveEntity(145, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 600 }), 400, false));
    mechanics.emplace_back(new MoveEntity(144, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 600 }), 400, false));


    mechanics.emplace_back(new Spread(146, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(147, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(147, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(146, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));

    mechanics.emplace_back(new MoveEntity(146, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 400 }), 400, false));
    mechanics.emplace_back(new MoveEntity(147, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 400 }), 400, false));
    mechanics.emplace_back(new MoveEntity(147, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 400 }), 400, false));
    mechanics.emplace_back(new MoveEntity(146, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 400 }), 400, false));


    mechanics.emplace_back(new Spread(148, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(149, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(149, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(148, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));

    mechanics.emplace_back(new MoveEntity(148, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 301 }), 400, false));
    mechanics.emplace_back(new MoveEntity(149, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 154 }), 400, false));
    mechanics.emplace_back(new MoveEntity(149, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 154 }), 400, false));
    mechanics.emplace_back(new MoveEntity(148, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 301 }), 400, false));

    mechanics.emplace_back(new Spread(148, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(149, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(149, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(148, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(150, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(151, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(151, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(150, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));

    // Couplet 2

    song.addCheckpoint(76, 152);


    mechanics.emplace_back(new ActivateTotem(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new MoveEntity(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 301 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanics.emplace_back(new MoveEntity(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 154 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanics.emplace_back(new MoveEntity(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 154 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));
    mechanics.emplace_back(new MoveEntity(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 301 }), 1000, true));


    mechanics.emplace_back(new Tether(156, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 100, 4, true, false));
    mechanics.emplace_back(new Tether(156, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 100, 4, true, false));
    mechanics.emplace_back(new Tether(156, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 100, 4, true, false));
    mechanics.emplace_back(new Tether(156, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 100, 4, true, false));

    mechanics.emplace_back(new Tether(160, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 100, 4, true, false));
    mechanics.emplace_back(new Tether(160, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 100, 4, true, false));
    mechanics.emplace_back(new Tether(160, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 100, 4, true, false));
    mechanics.emplace_back(new Tether(160, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 100, 4, true, false));

    mechanics.emplace_back(new Tether(164, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 100, 4, true, false));
    mechanics.emplace_back(new Tether(164, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 100, 4, true, false));
    mechanics.emplace_back(new Tether(164, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 100, 4, true, false));
    mechanics.emplace_back(new Tether(164, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 100, 4, true, false));

    mechanics.emplace_back(new Tether(168, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 100, 4, true, false));
    mechanics.emplace_back(new Tether(168, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 100, 4, true, false));
    mechanics.emplace_back(new Tether(168, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 100, 4, true, false));
    mechanics.emplace_back(new Tether(168, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 100, 4, true, false));


    // Refrain

    song.addCheckpoint(85, 167);

    mechanics.emplace_back(new ActivateTotem(167, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new MoveEntity(167, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 301 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(168, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanics.emplace_back(new MoveEntity(168, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 154 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(168, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanics.emplace_back(new MoveEntity(168, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 154 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(168, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));
    mechanics.emplace_back(new MoveEntity(168, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 301 }), 1000, true));


    for (int ii = 0; ii < 8; ii++) {
        float i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(168 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(169 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(170 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(171 + i * 4, 100, 1, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3, TARGET_FOLLOW)));

        if (ii != 7) {
            if (ii % 2 == 0) {
                mechanics.emplace_back(new MoveEntity(168 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 800, 698 }), 400, false));
                mechanics.emplace_back(new MoveEntity(169 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 600, 846 }), 400, false));
                mechanics.emplace_back(new MoveEntity(170 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 400, 846 }), 400, false));
                mechanics.emplace_back(new MoveEntity(171 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 200, 698 }), 400, false));
            }
            else {
                mechanics.emplace_back(new MoveEntity(168 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 301 }), 400, false));
                mechanics.emplace_back(new MoveEntity(169 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 400, 154 }), 400, false));
                mechanics.emplace_back(new MoveEntity(170 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 600, 154 }), 400, false));
                mechanics.emplace_back(new MoveEntity(171 + i * 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 301 }), 400, false));
            }
        }
    }

    // Break 2

    song.addCheckpoint(103, 200);

    mechanics.emplace_back(new ActivateTotem(200, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new MoveEntity(200, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 800, 698 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(200, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanics.emplace_back(new MoveEntity(200, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 600, 846 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(200, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanics.emplace_back(new MoveEntity(200, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 400, 846 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(200, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));
    mechanics.emplace_back(new MoveEntity(200, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 200, 698 }), 1000, true));

    mechanics.emplace_back(new MoveEntity(208, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500, 500 }), 200, false));
    mechanics.emplace_back(new MoveEntity(208, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 500, 500 }), 200, false));
    mechanics.emplace_back(new MoveEntity(216, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 500, 500 }), 200, false));
    mechanics.emplace_back(new MoveEntity(224, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 500, 500 }), 100, false));

    // Yeah Oh-ho

    for (int ii = 0; ii < 4; ii++) {
        float i = static_cast<float>(ii);

        mechanics.emplace_back(new Spread(232 + 4 * i, 250, 4, 4, Target(TARGET_POS, { 500, 500 })));

        mechanics.emplace_back(new Tether(234 + 4 * i, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 250, 4, false, false));
        mechanics.emplace_back(new Tether(234 + 4 * i, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 250, 4, false, false));
        mechanics.emplace_back(new Tether(234 + 4 * i, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 250, 4, false, false));
        mechanics.emplace_back(new Tether(234 + 4 * i, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 250, 4, false, false));

    }


    mechanics.emplace_back(new ActivateTotem(248, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));
    mechanics.emplace_back(new ActivateTotem(248, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false));
    mechanics.emplace_back(new ActivateTotem(248, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), false));
    mechanics.emplace_back(new ActivateTotem(248, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), false));


    for (int ii = 0; ii < 4; ii++) {
        float i = static_cast<float>(ii);

        mechanics.emplace_back(new Spread(248 + 4 * i, 250, 4, 4, Target(TARGET_POS, { 500, 500 })));

        mechanics.emplace_back(new Tether(250 + 4 * i, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 250, 4, false, false));
        mechanics.emplace_back(new Tether(250 + 4 * i, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 250, 4, false, false));
        mechanics.emplace_back(new Tether(250 + 4 * i, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 250, 4, false, false));
        mechanics.emplace_back(new Tether(250 + 4 * i, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 250, 4, false, false));

        mechanics.emplace_back(new Spread(250 + 4 * i, 150, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(250 + 4 * i, 150, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(250 + 4 * i, 150, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(250 + 4 * i, 150, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    }


    // Couplet 2

    song.addCheckpoint(135, 264);


    mechanics.emplace_back(new ActivateTotem(264, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new MoveEntity(264, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 200 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(264, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanics.emplace_back(new MoveEntity(264, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 800, 200 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(264, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanics.emplace_back(new MoveEntity(264, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 500, 500 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(264, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));
    mechanics.emplace_back(new MoveEntity(264, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 500, 900 }), 1000, true));


    mechanics.emplace_back(new Tether(268, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 100, 4, true, false));
    mechanics.emplace_back(new Tether(268, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 100, 4, true, false));
    mechanics.emplace_back(new Tether(268, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 100, 4, true, false));
    mechanics.emplace_back(new Tether(268, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 100, 4, true, false));

    mechanics.emplace_back(new Tether(272, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 100, 4, true, false));
    mechanics.emplace_back(new Tether(272, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 100, 4, true, false));
    mechanics.emplace_back(new Tether(272, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 100, 4, true, false));
    mechanics.emplace_back(new Tether(272, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 100, 4, true, false));

    mechanics.emplace_back(new Tether(276, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 100, 4, true, false));
    mechanics.emplace_back(new Tether(276, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 100, 4, true, false));
    mechanics.emplace_back(new Tether(276, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 100, 4, true, false));
    mechanics.emplace_back(new Tether(276, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 100, 4, true, false));

    mechanics.emplace_back(new Tether(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 100, 4, true, false));
    mechanics.emplace_back(new Tether(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 100, 4, true, false));
    mechanics.emplace_back(new Tether(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 100, 4, true, false));
    mechanics.emplace_back(new Tether(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 100, 4, true, false));


    // Final

    song.addCheckpoint(144, 280);

    mechanics.emplace_back(new ActivateTotem(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new MoveEntity(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 200 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanics.emplace_back(new MoveEntity(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 800, 200 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanics.emplace_back(new MoveEntity(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 500, 500 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));
    mechanics.emplace_back(new MoveEntity(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 500, 900 }), 1000, true));


    mechanics.emplace_back(new ActivateTotem(284, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));
    mechanics.emplace_back(new ActivateTotem(288, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false));
    mechanics.emplace_back(new ActivateTotem(292, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), false));
    mechanics.emplace_back(new ActivateTotem(284, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), false));


    for (int ii = 0; ii < 4; ii++) {
        float i = static_cast<float>(ii);

        mechanics.emplace_back(new Spread(296 + i * 4, 100, 1, 4, Target(TARGET_POS, { 500 + 400 * std::cos(PI / 6 * (i + 4) - PI),  500 + 400 * std::sin(PI / 6 * (i + 4) - PI) })));
        mechanics.emplace_back(new Spread(297 + i * 4, 100, 1, 4, Target(TARGET_POS, { 500 + 400 * std::cos(PI / 6 * (i + 3) - PI),  500 + 400 * std::sin(PI / 6 * (i + 3) - PI) })));
        mechanics.emplace_back(new Spread(298 + i * 4, 100, 1, 4, Target(TARGET_POS, { 500 + 400 * std::cos(PI / 6 * (i + 2) - PI),  500 + 400 * std::sin(PI / 6 * (i + 2) - PI) })));
        mechanics.emplace_back(new Spread(299 + i * 4, 100, 1, 4, Target(TARGET_POS, { 500 + 400 * std::cos(PI / 6 * (i + 1) - PI),  500 + 400 * std::sin(PI / 6 * (i + 1) - PI) })));

    }

    for (int ii = 0; ii < 8; ii++) {
        float i = static_cast<float>(ii);

        mechanics.emplace_back(new Spread(312 + i * 4, 100, 1, 4, Target(TARGET_POS, { 500 + 400 * std::cos(PI / 6 * (i + 16 + 4) - PI),  500 + 400 * std::sin(PI / 6 * (i + 16 + 4) - PI) })));
        mechanics.emplace_back(new Spread(313 + i * 4, 100, 1, 4, Target(TARGET_POS, { 500 + 400 * std::cos(PI / 6 * (i + 16 + 3) - PI),  500 + 400 * std::sin(PI / 6 * (i + 16 + 3) - PI) })));
        mechanics.emplace_back(new Spread(314 + i * 4, 100, 1, 4, Target(TARGET_POS, { 500 + 400 * std::cos(PI / 6 * (i + 16 + 2) - PI),  500 + 400 * std::sin(PI / 6 * (i + 16 + 2) - PI) })));
        mechanics.emplace_back(new Spread(315 + i * 4, 100, 1, 4, Target(TARGET_POS, { 500 + 400 * std::cos(PI / 6 * (i + 16 + 1) - PI),  500 + 400 * std::sin(PI / 6 * (i + 16 + 1) - PI) })));
    }

    mechanics.emplace_back(new Spread(312, 400, 0, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(313, 400, 0, 0, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(314, 400, 0, 0, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(315, 400, 0, 0, Target(TARGET_POS, { 500, 500 })));

    mechanics.emplace_back(new Donut(320, 400, 1000, 0, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Donut(321, 400, 1000, 0, 0, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Donut(322, 400, 1000, 0, 0, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Donut(323, 400, 1000, 0, 0, Target(TARGET_POS, { 500, 500 })));

    mechanics.emplace_back(new Spread(328, 400, 0, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(329, 400, 0, 0, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(330, 400, 0, 0, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(331, 400, 0, 0, Target(TARGET_POS, { 500, 500 })));


    mechanics.emplace_back(new Donut(336, 400, 1000, 0, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Donut(337, 400, 1000, 0, 0, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Donut(338, 400, 1000, 0, 0, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Donut(339, 400, 1000, 0, 0, Target(TARGET_POS, { 500, 500 })));

    mechanics.emplace_back(new EndMap(344));
}

void metal(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em)
{
    int mode;

    song.addCheckpoint(0, 0);

    mode = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            float pad = (j + mode) % 2 == 0 ? 2 * i : 2 * i + 1;
            mechanics.emplace_back(new NopeZone(8, 250, 250, 0, 8, Target(TARGET_POS, { 250 * pad, 250 * (float)j })));
        }
    }

    mode = 1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            float pad = (j + mode) % 2 == 0 ? 2 * i : 2 * i + 1;
            mechanics.emplace_back(new NopeZone(16, 250, 250, 0, 8, Target(TARGET_POS, { 250 * pad, 250 * (float)j })));
        }
    }

    mechanics.emplace_back(new ActivateTotem(0, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new MoveEntity(0, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 250, 500 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(0, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanics.emplace_back(new MoveEntity(0, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 500, 750 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(0, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanics.emplace_back(new MoveEntity(0, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 750, 500 }), 1000, true));
    mechanics.emplace_back(new ActivateTotem(0, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));
    mechanics.emplace_back(new MoveEntity(0, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 500, 250 }), 1000, true));



    mechanics.emplace_back(new Tether(32, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 500, 16, true, true));
    mechanics.emplace_back(new Tether(32, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 500, 12, true, true));
    mechanics.emplace_back(new Tether(32, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 500, 8, true, true));
    mechanics.emplace_back(new Tether(32, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 500, 4, true, true));

    //Riff

    song.addCheckpoint(12, 32.1);


    mechanics.emplace_back(new ActivateTotem(32.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new ActivateTotem(32.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanics.emplace_back(new ActivateTotem(32.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanics.emplace_back(new ActivateTotem(32.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));
    mechanics.emplace_back(new MoveEntity(32.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 250, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(32.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 500, 750 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(32.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 750, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(32.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 500, 250 }), 1000, true));

    mechanics.emplace_back(new Tether(64, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 500, 32, true, true));
    mechanics.emplace_back(new Tether(64, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 500, 32, true, true));
    mechanics.emplace_back(new Tether(64, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 500, 32, true, true));
    mechanics.emplace_back(new Tether(64, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 500, 32, true, true));

    mode = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            float pad = (j + mode) % 2 == 0 ? 2 * i : 2 * i + 1;
            mechanics.emplace_back(new NopeZone(64, 250, 250, 0, 32, Target(TARGET_POS, { 250 * pad, 250 * (float)j })));
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            mechanics.emplace_back(new Spread(38 + 16 * i, 250, 1, 6, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_FOLLOW)));
        }
        for (int j = 0; j < 2; j++) {
            mechanics.emplace_back(new Spread(46 + 16 * i, 250, 2, 6, Target(TARGET_ENTITY, TARGET_PLAYERS, 2 * j, TARGET_FOLLOW)));
        }
    }

    // Couplet


    song.addCheckpoint(25, 64.1);


    mechanics.emplace_back(new ActivateTotem(64.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new ActivateTotem(64.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanics.emplace_back(new ActivateTotem(64.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanics.emplace_back(new ActivateTotem(64.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true, 0x0000ffff, 15));
    mechanics.emplace_back(new MoveEntity(64.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 250, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(64.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 500, 750 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(64.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 750, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(64.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 500, 250 }), 1000, true));

    mechanics.emplace_back(new Tether(128, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 500, 64, true, true));
    mechanics.emplace_back(new Tether(128, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 500, 64, true, true));
    mechanics.emplace_back(new Tether(128, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 500, 64, true, true));
    mechanics.emplace_back(new Tether(128, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 500, 64, true, true));


    mode = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            float pad = (j + mode) % 2 == 0 ? 2 * i : 2 * i + 1;
            mechanics.emplace_back(new NopeZone(128, 250, 250, 0, 64, Target(TARGET_POS, { 250 * pad, 250 * (float)j })));
        }
    }

    for (int i = 0; i < 4; i++) {
        mechanics.emplace_back(new Cone(72 + 8 * i, 30, 1500, 1, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 3 - i), Target(TARGET_ENTITY, TARGET_PLAYERS, 3 - i)));

        if (i >= 1) {
            mechanics.emplace_back(new ActivateTotem(64 + 8 * i, Target(TARGET_ENTITY, TARGET_TOTEMS, 3 - i + 1), true, 0xffffffff));
            mechanics.emplace_back(new ActivateTotem(64 + 8 * i, Target(TARGET_ENTITY, TARGET_TOTEMS, 3 - i), true, 0x0000ffff, 15));
        }
    }

    mechanics.emplace_back(new ActivateTotem(96, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xffffffff));
    mechanics.emplace_back(new ActivateTotem(96, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true, 0xff0000ff, 15));

    for (int i = 0; i < 4; i++) {
        mechanics.emplace_back(new Spread(104 + 8 * i, 500, 1, 0, Target(TARGET_ENTITY, TARGET_PLAYERS, 3 - i)));

        if (i >= 1) {
            mechanics.emplace_back(new ActivateTotem(96 + 8 * i, Target(TARGET_ENTITY, TARGET_TOTEMS, 3 - i + 1), true, 0xffffffff));
            mechanics.emplace_back(new ActivateTotem(96 + 8 * i, Target(TARGET_ENTITY, TARGET_TOTEMS, 3 - i), true, 0xff0000ff, 15));
        }
    }

    //Riff

    song.addCheckpoint(51, 128.1);


    mechanics.emplace_back(new ActivateTotem(128.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new ActivateTotem(128.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanics.emplace_back(new ActivateTotem(128.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanics.emplace_back(new ActivateTotem(128.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));
    mechanics.emplace_back(new MoveEntity(128.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 250, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(128.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 500, 750 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(128.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 750, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(128.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 500, 250 }), 1000, true));

    mechanics.emplace_back(new Tether(160, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 500, 32, true, true));
    mechanics.emplace_back(new Tether(160, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 500, 32, true, true));
    mechanics.emplace_back(new Tether(160, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 500, 32, true, true));
    mechanics.emplace_back(new Tether(160, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 500, 32, true, true));

    mode = 1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            float pad = (j + mode) % 2 == 0 ? 2 * i : 2 * i + 1;
            mechanics.emplace_back(new NopeZone(160, 250, 250, 0, 32, Target(TARGET_POS, { 250 * pad, 250 * (float)j })));
        }
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            mechanics.emplace_back(new Spread(134 + 16 * i, 250, 1, 6, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_FOLLOW)));
            mechanics.emplace_back(new Spread(142 + 16 * i, 250, 0, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_ONINIT)));
        }
        for (int j = 0; j < 2; j++) {
            mechanics.emplace_back(new Spread(142 + 16 * i, 250, 2, 6, Target(TARGET_ENTITY, TARGET_PLAYERS, 2 * j, TARGET_FOLLOW)));
            if (i != 1)
                mechanics.emplace_back(new Spread(150 + 16 * i, 250, 0, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_ONINIT)));
        }
    }

    //Riff

    song.addCheckpoint(64, 160.1);


    mechanics.emplace_back(new ActivateTotem(160.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));
    mechanics.emplace_back(new ActivateTotem(160.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));
    mechanics.emplace_back(new ActivateTotem(160.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));
    mechanics.emplace_back(new ActivateTotem(160.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true, 0x0000ffff, 15));
    mechanics.emplace_back(new MoveEntity(160.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 250, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(160.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 500, 750 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(160.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 750, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(160.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 500, 250 }), 1000, true));

    mechanics.emplace_back(new Tether(192, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 500, 32, true, true));
    mechanics.emplace_back(new Tether(192, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 500, 32, true, true));
    mechanics.emplace_back(new Tether(192, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 500, 32, true, true));
    mechanics.emplace_back(new Tether(192, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 500, 32, true, true));

    mode = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            float pad = (j + mode) % 2 == 0 ? 2 * i : 2 * i + 1;
            mechanics.emplace_back(new NopeZone(176, 250, 250, 0, 16, Target(TARGET_POS, { 250 * pad, 250 * (float)j })));
        }
    }

    mode = 1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            float pad = (j + mode) % 2 == 0 ? 2 * i : 2 * i + 1;
            mechanics.emplace_back(new NopeZone(192, 250, 250, 0, 16, Target(TARGET_POS, { 250 * pad, 250 * (float)j })));
        }
    }


    for (int i = 0; i < 8; i++) {

        if (i % 2 == 0) {
            mechanics.emplace_back(new Cone(164 + 4 * i, 30, 1500, 1, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, (7 - i) % 4), Target(TARGET_ENTITY, TARGET_PLAYERS, (7 - i) % 4)));

            if (i >= 1) {
                mechanics.emplace_back(new ActivateTotem(160 + 4 * i, Target(TARGET_ENTITY, TARGET_TOTEMS, (7 - i + 1) % 4), true, 0xffffffff));
                mechanics.emplace_back(new ActivateTotem(160 + 4 * i, Target(TARGET_ENTITY, TARGET_TOTEMS, (7 - i) % 4), true, 0x0000ffff, 15));
            }
        }
        else {
            mechanics.emplace_back(new Spread(164 + 4 * i, 500, 1, 0, Target(TARGET_ENTITY, TARGET_PLAYERS, (7 - i) % 4)));

            if (i >= 1) {
                mechanics.emplace_back(new ActivateTotem(160 + 4 * i, Target(TARGET_ENTITY, TARGET_TOTEMS, (7 - i + 1) % 4), true, 0xffffffff));
                mechanics.emplace_back(new ActivateTotem(160 + 4 * i, Target(TARGET_ENTITY, TARGET_TOTEMS, (7 - i) % 4), true, 0xff0000ff, 15));
            }
        }

    }

    // Refrain 2

    song.addCheckpoint(81, 192.1);


    mechanics.emplace_back(new ActivateTotem(192.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xff0000ff, 15));
    mechanics.emplace_back(new ActivateTotem(192.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, 0xff0000ff, 15));
    mechanics.emplace_back(new ActivateTotem(192.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true, 0xff0000ff, 15));
    mechanics.emplace_back(new ActivateTotem(192.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true, 0xff0000ff, 15));
    mechanics.emplace_back(new MoveEntity(192.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 250, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(192.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 500, 750 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(192.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 750, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(192.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 500, 250 }), 1000, true));

    mechanics.emplace_back(new Tether(256, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 500, 64, true, true));
    mechanics.emplace_back(new Tether(256, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 500, 64, true, true));
    mechanics.emplace_back(new Tether(256, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 500, 64, true, true));
    mechanics.emplace_back(new Tether(256, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 500, 64, true, true));

    mode = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            float pad = (j + mode) % 2 == 0 ? 2 * i : 2 * i + 1;
            mechanics.emplace_back(new NopeZone(224, 250, 250, 0, 32, Target(TARGET_POS, { 250 * pad, 250 * (float)j })));
        }
    }

    mode = 1;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            float pad = (j + mode) % 2 == 0 ? 2 * i : 2 * i + 1;
            mechanics.emplace_back(new NopeZone(256, 250, 250, 0, 32, Target(TARGET_POS, { 250 * pad, 250 * (float)j })));
        }
    }


    for (int j = 0; j < 4; j++) {
        mechanics.emplace_back(new Spread(208, 500, 1, 0, Target(TARGET_ENTITY, TARGET_PLAYERS, j)));
    }
    mechanics.emplace_back(new ActivateTotem(208, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xff0000ff, 15));
    mechanics.emplace_back(new ActivateTotem(208, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, 0x0000ffff, 15));
    mechanics.emplace_back(new ActivateTotem(208, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true, 0xffffffff));
    mechanics.emplace_back(new ActivateTotem(208, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true, 0xffffffff));

    mechanics.emplace_back(new Spread(224, 500, 1, 0, Target(TARGET_ENTITY, TARGET_PLAYERS, 0)));
    mechanics.emplace_back(new Cone(224, 30, 1500, 1, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1)));
    mechanics.emplace_back(new Spread(224, 250, 3, 16, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));


    mechanics.emplace_back(new ActivateTotem(224, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0x0000ffff, 15));
    mechanics.emplace_back(new ActivateTotem(224, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, 0xff0000ff, 15));
    mechanics.emplace_back(new ActivateTotem(224, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true, 0xff0000ff, 15));
    mechanics.emplace_back(new ActivateTotem(224, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true, 0x0000ffff, 15));

    mechanics.emplace_back(new Spread(240, 250, 2, 16, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(240, 30, 1500, 1, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0)));
    mechanics.emplace_back(new Cone(240, 30, 1500, 1, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 3)));
    mechanics.emplace_back(new Spread(240, 500, 1, 0, Target(TARGET_ENTITY, TARGET_PLAYERS, 1)));
    mechanics.emplace_back(new Spread(240, 500, 1, 0, Target(TARGET_ENTITY, TARGET_PLAYERS, 2)));


    mechanics.emplace_back(new ActivateTotem(240, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0x0000ffff, 15));
    mechanics.emplace_back(new ActivateTotem(240, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, 0x0000ffff, 15));
    mechanics.emplace_back(new ActivateTotem(240, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true, 0x0000ffff, 15));
    mechanics.emplace_back(new ActivateTotem(240, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true, 0x0000ffff, 15));

    mechanics.emplace_back(new Cone(256, 30, 1500, 1, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0)));
    mechanics.emplace_back(new Cone(256, 30, 1500, 1, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1)));
    mechanics.emplace_back(new Cone(256, 30, 1500, 1, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 2)));
    mechanics.emplace_back(new Cone(256, 30, 1500, 1, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 3)));

    mechanics.emplace_back(new Spread(256, 250, 2, 16, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(256, 250, 2, 16, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));


    // Outro
    song.addCheckpoint(106, 256.1);

    mechanics.emplace_back(new ActivateTotem(256.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xffffffff));
    mechanics.emplace_back(new ActivateTotem(256.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, 0xffffffff));
    mechanics.emplace_back(new ActivateTotem(256.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true, 0xffffffff));
    mechanics.emplace_back(new ActivateTotem(256.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true, 0xffffffff));
    mechanics.emplace_back(new MoveEntity(256.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 250, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(256.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 500, 750 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(256.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 750, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(256.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 500, 250 }), 1000, true));


    mode = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            float pad = (j + mode) % 2 == 0 ? 2 * i : 2 * i + 1;
            mechanics.emplace_back(new NopeZone(288, 250, 250, 0, 32, Target(TARGET_POS, { 250 * pad, 250 * (float)j })));
        }
    }

    mechanics.emplace_back(new Tether(286, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 500, 64, true, true));
    mechanics.emplace_back(new Tether(286, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 500, 64, true, true));
    mechanics.emplace_back(new Tether(286, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 500, 64, true, true));
    mechanics.emplace_back(new Tether(286, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 500, 64, true, true));

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            mechanics.emplace_back(new Spread(264 + 8 * i, 250, 1, 6, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_FOLLOW)));
            mechanics.emplace_back(new Spread(288, 250, 0, 24 - 8 * i, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_ONINIT)));
        }
    }

    mechanics.emplace_back(new Spread(286, 250, 4, 6, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));

    mechanics.emplace_back(new EndMap(290));
}

void oblivion(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em)
{
    // Intro
    song.addCheckpoint(0, 0);

    mechanics.emplace_back(new Tether(96, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 550, 64 + 32, false, true));
    mechanics.emplace_back(new Tether(96, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 550, 64 + 24, false, true));
    mechanics.emplace_back(new Tether(96, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 550, 64 + 16, false, true));
    mechanics.emplace_back(new Tether(96, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 550, 64 + 8, false, true));

    for (int ii = 0; ii < 8; ii++) {
        float i = static_cast<float>(ii);
        for (int j = 0; j < 4; j++)
            mechanics.emplace_back(new Spread(32 + 4 * i, 100, 1, 4, Target(TARGET_POS, { 500 + 400 * std::cos(PI / 8 * i + j * PI / 2), 500 + 400 * std::sin(PI / 8 * i + j * PI / 2) })));
    }

    for (int ii = 0; ii < 8; ii++) {
        float i = static_cast<float>(ii);
        for (int j = 0; j < 4; j++)
            mechanics.emplace_back(new Spread(64 + 4 * i, 100, 1, 4, Target(TARGET_POS, { 500 + 400 * std::cos(-PI / 8 * i + j * PI / 2), 500 + 400 * std::sin(-PI / 8 * i + j * PI / 2) })));
    }

    // Couplet
    song.addCheckpoint(40, 96.1);

    mechanics.emplace_back(new ActivateTotem(96.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xff0000ff));

    mechanics.emplace_back(new MoveEntity(96.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 700, 100 }), 1000, true));
    mechanics.emplace_back(new Cone(104, 20, 1500, 4, 7.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(104, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 300, 7.2, true, false));
    mechanics.emplace_back(new Spread(104, 200, 3, 7.2, Target(TARGET_POS, { 500, 700 })));

    mechanics.emplace_back(new MoveEntity(104, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 900, 400 }), 1000, false));
    mechanics.emplace_back(new Cone(112, 20, 1500, 4, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(112, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 300, 8, true, false));
    mechanics.emplace_back(new Spread(112, 200, 3, 8, Target(TARGET_POS, { 200, 500 })));

    mechanics.emplace_back(new MoveEntity(112, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 900 }), 1000, false));
    mechanics.emplace_back(new Cone(120, 20, 1500, 4, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(120, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 300, 8, true, false));
    mechanics.emplace_back(new Spread(120, 200, 3, 8, Target(TARGET_POS, { 500, 200 })));

    mechanics.emplace_back(new MoveEntity(120, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 100, 600 }), 1000, false));
    mechanics.emplace_back(new Cone(128, 20, 1500, 4, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(128, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 300, 8, true, false));
    mechanics.emplace_back(new Spread(128, 200, 3, 8, Target(TARGET_POS, { 700, 500 })));


    // -----------------------------

    mechanics.emplace_back(new MoveEntity(128, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 700, 100 }), 1000, true));
    mechanics.emplace_back(new Cone(136, 20, 1500, 4, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(136, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 300, 8, true, false));
    mechanics.emplace_back(new Spread(136, 200, 3, 8, Target(TARGET_POS, { 500, 700 })));

    mechanics.emplace_back(new MoveEntity(136, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 900, 400 }), 1000, false));
    mechanics.emplace_back(new Cone(144, 20, 1500, 4, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(144, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 300, 8, true, false));
    mechanics.emplace_back(new Spread(144, 200, 3, 8, Target(TARGET_POS, { 200, 500 })));

    // Refrain 
    song.addCheckpoint(66, 144.1);

    mechanics.emplace_back(new ActivateTotem(144.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false, 0xff0000ff));

    mechanics.emplace_back(new Tether(220, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 550, 76, false, true));
    mechanics.emplace_back(new Tether(220, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 550, 76, false, true));
    mechanics.emplace_back(new Tether(220, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 550, 76, false, true));
    mechanics.emplace_back(new Tether(220, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 550, 76, false, true));

    for (int ii = 0; ii < 8; ii++) {
        float i = static_cast<float>(ii);
        for (int j = 0; j < 2; j++) {
            if (ii == 0)
                mechanics.emplace_back(new Spread(160 + 4 * i, 150, 2, 16, Target(TARGET_POS, { 500 + 400 * std::cos(PI / 8 * i + j * PI), 500 + 400 * std::sin(PI / 8 * i + j * PI) })));
            else
                mechanics.emplace_back(new Spread(160 + 4 * i, 150, 2, 4, Target(TARGET_POS, { 500 + 400 * std::cos(PI / 8 * i + j * PI), 500 + 400 * std::sin(PI / 8 * i + j * PI) })));
        }

    }

    for (int ii = 0; ii < 8; ii++) {
        float i = static_cast<float>(ii);
        if (ii % 2 == 0) {
            for (int j = 0; j < 2; j++) {
                mechanics.emplace_back(new Spread(192 + 4 * i, 150, 2, 4, Target(TARGET_POS, { 500 + 400 * std::cos(-PI / 8 * i + j * PI), 500 + 400 * std::sin(-PI / 8 * i + j * PI) })));
            }
        }
        else {
            for (int j = 0; j < 2; j++) {
                mechanics.emplace_back(new Spread(192 + 4 * i, 150, 1, 4, Target(TARGET_POS, { 500 + 400 * std::cos(-PI / 8 * (i)+j * PI), 500 + 400 * std::sin(-PI / 8 * (i)+j * PI) })));
                mechanics.emplace_back(new Spread(192 + 4 * i, 150, 1, 4, Target(TARGET_POS, { 500 + 400 * std::cos(-PI / 8 * (i - 2) + j * PI), 500 + 400 * std::sin(-PI / 8 * (i - 2) + j * PI) })));
            }
        }

    }

    // HYPE ZONE

    song.addCheckpoint(100, 220.1);

    mechanics.emplace_back(new ActivateTotem(220.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xff0000ff));

    mechanics.emplace_back(new MoveEntity(220.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 300, 100 }), 1000, false));
    mechanics.emplace_back(new Cone(228, 20, 1500, 3, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(228, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 300, 8, true, false));
    mechanics.emplace_back(new Spread(228, 150, 2, 8, Target(TARGET_POS, { 300, 700 })));
    mechanics.emplace_back(new Spread(228, 150, 1, 8, Target(TARGET_POS, { 700, 700 })));

    mechanics.emplace_back(new MoveEntity(228, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 900, 700 }), 1000, false));
    mechanics.emplace_back(new Cone(236, 20, 1500, 2, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(236, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 300, 8, true, false));
    mechanics.emplace_back(new Spread(236, 150, 2, 8, Target(TARGET_POS, { 300, 700 })));
    mechanics.emplace_back(new Spread(236, 150, 1, 8, Target(TARGET_POS, { 300, 300 })));

    mechanics.emplace_back(new MoveEntity(236, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 700, 900 }), 1000, false));
    mechanics.emplace_back(new Cone(244, 20, 1500, 3, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(244, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 300, 8, true, false));
    mechanics.emplace_back(new Spread(244, 150, 2, 8, Target(TARGET_POS, { 700, 300 })));
    mechanics.emplace_back(new Spread(244, 150, 1, 8, Target(TARGET_POS, { 300, 300 })));


    mechanics.emplace_back(new MoveEntity(244, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 100, 400 }), 1000, false));
    mechanics.emplace_back(new Cone(252, 20, 1500, 3, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(252, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 300, 8, true, false));
    mechanics.emplace_back(new Spread(252, 150, 2, 8, Target(TARGET_POS, { 700, 300 })));
    mechanics.emplace_back(new Spread(252, 150, 1, 8, Target(TARGET_POS, { 700, 700 })));



    mechanics.emplace_back(new ActivateTotem(252, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, 0xff0000ff));

    mechanics.emplace_back(new MoveEntity(252, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 100, 900 }), 1000, false));
    mechanics.emplace_back(new MoveEntity(252, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 900, 900 }), 1000, false));
    mechanics.emplace_back(new Cone(260, 20, 1500, 2, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(260, 20, 1500, 2, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(260, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 300, 8, true, false));
    mechanics.emplace_back(new Tether(260, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 300, 8, true, false));
    mechanics.emplace_back(new Spread(260, 150, 1, 8, Target(TARGET_POS, { 300, 300 })));
    mechanics.emplace_back(new Spread(260, 150, 1, 8, Target(TARGET_POS, { 700, 300 })));


    mechanics.emplace_back(new Cone(268, 20, 1500, 3, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(268, 20, 1500, 2, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(268, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 300, 8, true, false));
    mechanics.emplace_back(new Tether(268, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 300, 8, true, false));
    mechanics.emplace_back(new Spread(268, 150, 2, 8, Target(TARGET_POS, { 500, 300 })));


    mechanics.emplace_back(new MoveEntity(268, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500, 900 }), 1000, false));
    mechanics.emplace_back(new MoveEntity(268, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 500, 900 }), 1000, false));
    mechanics.emplace_back(new Cone(276, 20, 1500, 2, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(276, 20, 1500, 2, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(276, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 300, 8, true, false));
    mechanics.emplace_back(new Tether(276, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 300, 8, true, false));
    mechanics.emplace_back(new Spread(276, 150, 1, 8, Target(TARGET_POS, { 300, 300 })));
    mechanics.emplace_back(new Spread(276, 150, 1, 8, Target(TARGET_POS, { 700, 300 })));


    mechanics.emplace_back(new Cone(284, 20, 1500, 4, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(284, 20, 1500, 2, 8, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(284, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 300, 8, true, false));
    mechanics.emplace_back(new Tether(284, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 300, 8, true, false));
    mechanics.emplace_back(new Spread(284, 150, 2, 8, Target(TARGET_POS, { 500, 300 })));

    mechanics.emplace_back(new ActivateTotem(284, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false, 0xff0000ff));
    mechanics.emplace_back(new ActivateTotem(284, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false, 0xff0000ff));

    // Riff

    song.addCheckpoint(130, 292);

    mechanics.emplace_back(new Tether(356, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 550, 72, false, true));
    mechanics.emplace_back(new Tether(356, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 550, 72, false, true));
    mechanics.emplace_back(new Tether(356, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 550, 72, false, true));
    mechanics.emplace_back(new Tether(356, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 550, 72, false, true));




    for (int ii = 0; ii < 16; ii++) {
        float i = static_cast<float>(ii);

        if (ii % 2 == 0) {
            int active = 4;
            if (ii == 0) {
                active = 8;
            }
            float n = ii % 4;
            mechanics.emplace_back(new Spread(292 + 4 * i, 150, 2, active, Target(TARGET_POS, { 500, 200 })));
            mechanics.emplace_back(new Spread(292 + 4 * i, 150, 2, active, Target(TARGET_POS, { 500, 800 })));

            mechanics.emplace_back(new Cone(292 + 4 * i, 45, 1500, 4, active, Target(TARGET_POS, { 500, 100 + 800 * n / 2 }),
                Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 500, 100 + 800 * n / 2 }), TARGET_FOLLOW)));

        }
        else {

            float x, y;
            if ((ii) % 8 == 1) {
                x = 100;
                y = 900;
            }
            if ((ii) % 8 == 3) {
                x = 900;
                y = 100;
            }
            if ((ii) % 8 == 5) {
                x = 900;
                y = 900;
            }
            if ((ii) % 8 == 7) {
                x = 100;
                y = 100;
            }

            mechanics.emplace_back(new Spread(292 + 4 * i, 150, 1, 4, Target(TARGET_POS, { 200, 200 })));
            mechanics.emplace_back(new Spread(292 + 4 * i, 150, 1, 4, Target(TARGET_POS, { 200, 800 })));
            mechanics.emplace_back(new Spread(292 + 4 * i, 150, 1, 4, Target(TARGET_POS, { 800, 200 })));
            mechanics.emplace_back(new Spread(292 + 4 * i, 150, 1, 4, Target(TARGET_POS, { 800, 800 })));

            mechanics.emplace_back(new Cone(292 + 4 * i, 45, 1500, 2, 4, Target(TARGET_POS, { x, y }),
                Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { x, y }), TARGET_FOLLOW)));

        }

    }

    mechanics.emplace_back(new EndMap(356));
}

void gas(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em)
{
    // Intro
    song.addCheckpoint(0, 0);
    mechanics.emplace_back(new AddArena(36, 0, 0, 500, 500));
    mechanics.emplace_back(new AddArena(44, 500, 0, 500, 500));
    mechanics.emplace_back(new AddArena(52, 500, 500, 500, 500));
    mechanics.emplace_back(new AddArena(60, 0, 500, 500, 500));

    mechanics.emplace_back(new Tether(40, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_POS, { 500, 500 }), 600, 8, false, false));
    mechanics.emplace_back(new Tether(48, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_POS, { 500, 500 }), 600, 8, false, false));
    mechanics.emplace_back(new Tether(56, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_POS, { 500, 500 }), 600, 8, false, false));
    mechanics.emplace_back(new Tether(64, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_POS, { 500, 500 }), 600, 8, false, false));

    mechanics.emplace_back(new Spread(48, 500, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(56, 500, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(64, 500, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(56, 500, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(64, 500, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(64, 500, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));


    mechanics.emplace_back(new Spread(68.5, 200, 4, 4, Target(TARGET_POS, { 500, 500 })));

    mechanics.emplace_back(new Spread(72.5, 200, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(72.5, 200, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(72.5, 200, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(72.5, 200, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new MoveEntity(72.5, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 1000, true));
    mechanics.emplace_back(new MoveEntity(72.5, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 1000, true));
    mechanics.emplace_back(new MoveEntity(72.5, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 1000, true));
    mechanics.emplace_back(new MoveEntity(72.5, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 1000, true));

    mechanics.emplace_back(new Spread(76.5, 200, 0, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 0)));
    mechanics.emplace_back(new Spread(76.5, 200, 0, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 1)));
    mechanics.emplace_back(new Spread(76.5, 200, 0, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 2)));
    mechanics.emplace_back(new Spread(76.5, 200, 0, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 3)));
    mechanics.emplace_back(new Spread(80.5, 200, 0, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 0)));
    mechanics.emplace_back(new Spread(80.5, 200, 0, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 1)));
    mechanics.emplace_back(new Spread(80.5, 200, 0, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 2)));
    mechanics.emplace_back(new Spread(80.5, 200, 0, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 3)));

    mechanics.emplace_back(new NopeZone(92, 1000, 360, 0, 8, Target(TARGET_POS, { 0, 0 })));
    mechanics.emplace_back(new NopeZone(92, 1000, 360, 0, 8, Target(TARGET_POS, { 0, 1000 - 360 })));

    mechanics.emplace_back(new NopeZone(92, 360, 1000, 0, 4, Target(TARGET_POS, { 0, 0 })));
    mechanics.emplace_back(new NopeZone(92, 360, 1000, 0, 4, Target(TARGET_POS, { 1000 - 360, 0 })));

    // Speed
    song.addCheckpoint(35, 92.1);
    mechanics.emplace_back(new ClearArena(92.2));
    mechanics.emplace_back(new AddArena(92.3, 360, 360, 280, 280));
    mechanics.emplace_back(new ZoomArena(92.3, 80, 1));
    mechanics.emplace_back(new SnapArena(132, 39.8, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new AddArena(92.3, 360 + 280, 360, 280, 280));
    mechanics.emplace_back(new NopeZone(100, 280, 280, 0, 8, Target(TARGET_POS, { 360, 360 })));
    mechanics.emplace_back(new AddArena(97, 360 + 280 * 2, 360, 280, 280));
    mechanics.emplace_back(new AddArena(98, 360 + 280 * 3, 360, 280, 280));
    mechanics.emplace_back(new AddArena(99, 360 + 280 * 4, 360, 280, 280));

    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new NopeZone(101 + i, 280, 280, 0, 1, Target(TARGET_POS, { 360 + 280 * (float)(i + 1), 360 })));
    }
    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new NopeZone(109 + i, 280, 280, 0, 1, Target(TARGET_POS, { 360 + 280 * (7 + 1), 360 + 280 * (float)(i + 1) })));
    }
    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new NopeZone(117 + i, 280, 280, 0, 1, Target(TARGET_POS, { 360 + 280 * (float)(6 + 1 - i), 360 + 280 * (float)(7 + 1) })));
    }
    for (int i = 0; i < 7; i++) {
        mechanics.emplace_back(new NopeZone(125 + i, 280, 280, 0, 1, Target(TARGET_POS, { 360, 360 + 280 * (float)(7 - i) })));
    }

    for (int i = 0; i < 4; i++) {
        mechanics.emplace_back(new AddArena(100 + i, 360 + 280 * (5 + i), 360, 280, 280));
        mechanics.emplace_back(new RemoveArena(100 + i, 0));

    }
    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new AddArena(104 + i, 360 + 280 * (5 + 3), 360 + 280 * (i + 1), 280, 280));
        mechanics.emplace_back(new RemoveArena(104 + i, 0));
    }
    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new AddArena(112 + i, 360 + 280 * (5 + 2 - i), 360 + 280 * (7 + 1), 280, 280));
        mechanics.emplace_back(new RemoveArena(112 + i, 0));
    }
    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new AddArena(120 + i, 360, 360 + 280 * (7 - i), 280, 280));
        mechanics.emplace_back(new RemoveArena(120 + i, 0));
    }
    mechanics.emplace_back(new RemoveArena(129, 0));
    mechanics.emplace_back(new RemoveArena(130, 0));
    mechanics.emplace_back(new RemoveArena(131, 0));
    mechanics.emplace_back(new RemoveArena(132, 0));
    mechanics.emplace_back(new NopeZone(132, 280, 280, 4, 1, Target(TARGET_POS, { 360, 360 })));




    // Speed
    song.addCheckpoint(48, 132.1);

    mechanics.emplace_back(new ClearArena(132.2));
    mechanics.emplace_back(new AddArena(132.3, 358, 358, 290, 290));
    mechanics.emplace_back(new AddArena(132.5, 360, 0, 280, 358));
    mechanics.emplace_back(new AddArena(132.5, 360, 1000 - 358, 280, 358));
    mechanics.emplace_back(new AddArena(132.5, 0, 360, 358, 280));
    mechanics.emplace_back(new AddArena(132.5, 1000 - 358, 360, 358, 280));

    mechanics.emplace_back(new RemoveArena(140, 0));

    mechanics.emplace_back(new Tether(140, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_POS, { 100, 500 }), 150, 8, true, false));
    mechanics.emplace_back(new Tether(140, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_POS, { 900, 500 }), 150, 8, true, false));
    mechanics.emplace_back(new Tether(140, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_POS, { 500, 100 }), 150, 8, true, false));
    mechanics.emplace_back(new Tether(140, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_POS, { 500, 900 }), 150, 8, true, false));


    mechanics.emplace_back(new Tether(148, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 300, 8, true, false));
    mechanics.emplace_back(new Tether(148, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 800, 8, false, false));



    mechanics.emplace_back(new Spread(156, 200, 3, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(156, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 500, 8, false, false));

    mechanics.emplace_back(new Spread(164, 250, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(164, 250, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Tether(164, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 300, 8, true, false));

    mechanics.emplace_back(new AddArena(164, 0, 0, 1000, 360));



    mechanics.emplace_back(new Cone(172, 60, 1500, 1, 8, Target(TARGET_POS, { 500, 0 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(172, 60, 1500, 1, 8, Target(TARGET_POS, { 500, 0 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(172, 60, 1500, 1, 8, Target(TARGET_POS, { 500, 0 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));



    // Speed
    song.addCheckpoint(70, 179);

    mechanics.emplace_back(new ClearArena(180));
    mechanics.emplace_back(new AddArena(180.05, 0, 0, 1000, 1000));

    mechanics.emplace_back(new AddArena(180.1, 0, 0, 1000, 260));
    mechanics.emplace_back(new AddArena(180.1, 0, 1000 - 260, 1000, 260));
    mechanics.emplace_back(new AddArena(180.1, 0, 0, 260, 1000));
    mechanics.emplace_back(new AddArena(180.1, 1000 - 260, 0, 260, 1000));
    mechanics.emplace_back(new AddArena(180.1, 360, 360, 280, 280));


    mechanics.emplace_back(new NopeZone(196, 480, 100, 0, 8, Target(TARGET_POS, { 260, 260 })));
    mechanics.emplace_back(new NopeZone(196, 480, 100, 0, 8, Target(TARGET_POS, { 260, 360 + 280 })));
    mechanics.emplace_back(new NopeZone(196, 100, 480, 0, 8, Target(TARGET_POS, { 260, 260 })));
    mechanics.emplace_back(new NopeZone(196, 100, 480, 0, 8, Target(TARGET_POS, { 360 + 280 , 260 })));

    mechanics.emplace_back(new RemoveArena(196, 0));

    mechanics.emplace_back(new Spread(196, 150, 1, 8, Target(TARGET_POS, { 500, 500 })));

    for (int i = 0; i < 2; i++) {
        mechanics.emplace_back(new Spread(196 + 32 * i, 150, 1, 8, Target(TARGET_POS, { 100, 500 })));
        mechanics.emplace_back(new Spread(196 + 32 * i, 150, 2, 8, Target(TARGET_POS, { 900, 500 })));

        mechanics.emplace_back(new Cone(199 + 32 * i, 60, 1500, i == 0 ? 2 : 3, 3, Target(TARGET_POS, { 500, 500 }), Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 500, 500 }), TARGET_FOLLOW)));

        mechanics.emplace_back(new Spread(204 + 32 * i, 150, 4, 5, Target(TARGET_POS, { 100, 100 })));
        mechanics.emplace_back(new Cone(204 + 32 * i, 60, 1500, 4, 5, Target(TARGET_POS, { 500, 500 }), Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 500, 500 }), TARGET_FOLLOW)));

        mechanics.emplace_back(new Spread(212 + 32 * i, 150, 1, 8, Target(TARGET_POS, { 900, 900 })));
        mechanics.emplace_back(new Spread(212 + 32 * i, 150, 2, 8, Target(TARGET_POS, { 100, 900 })));
        mechanics.emplace_back(new Cone(215 + 32 * i, 60, 1500, i == 0 ? 3 : 2, 3, Target(TARGET_POS, { 500, 500 }), Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 500, 500 }), TARGET_FOLLOW)));

        mechanics.emplace_back(new Spread(220 + 32 * i, 150, 4, 5, Target(TARGET_POS, { 900, 100 })));
        mechanics.emplace_back(new Cone(220 + 32 * i, 60, 1500, 4, 5, Target(TARGET_POS, { 500, 500 }), Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 500, 500 }), TARGET_FOLLOW)));

    }

    for (int i = 0; i < 8; i++) {
        float active = i == 0 ? 4 : 2;
        mechanics.emplace_back(new Spread(260 + 2 * i, 150, 1, active, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(260 + 2 * i, 150, 1, active, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(260 + 2 * i, 150, 1, active, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(260 + 2 * i, 150, 1, active, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));

        mechanics.emplace_back(new Spread(261 + 2 * i, 150, 0, 1, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
        mechanics.emplace_back(new Spread(261 + 2 * i, 150, 0, 1, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
        mechanics.emplace_back(new Spread(261 + 2 * i, 150, 0, 1, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_ONINIT)));
        mechanics.emplace_back(new Spread(261 + 2 * i, 150, 0, 1, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_ONINIT)));
    }

    mechanics.emplace_back(new EndMap(290));
}

void aiKotoba(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em)
{
    song.addCheckpoint(0, 0);
    song.addCheckpoint(18, 48);
    song.addCheckpoint(30, 78);
    song.addCheckpoint(44, 112);
    song.addCheckpoint(58, 140);
    song.addCheckpoint(89, 212);
    song.addCheckpoint(104, 248);
    song.addCheckpoint(120, 280);
    song.addCheckpoint(133, 308);
    song.addCheckpoint(146, 344);
    song.addCheckpoint(173, 412);


    mechanics.emplace_back(new Tether(15,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        300, 4, false, false));

    // INTRO
    for (int ii = 0; ii < 28; ii++) {
        auto i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(16 + i + 0.5f, 100, 1, 4,
            Target(TARGET_POS,
                { 500.f + 350.f * std::cos(2.f * i * PI / 16.f - PI / 4),
                 500.f + 350.f * std::sin(2.f * i * PI / 16.f - PI / 4) })));
        mechanics.emplace_back(new Spread(16 + i + 0.5f, 100, 1, 4,
            Target(TARGET_POS,
                { 500.f + 350.f * std::cos(PI + 2.f * i * PI / 16.f - PI / 4),
                 500.f + 350.f * std::sin(PI + 2.f * i * PI / 16.f - PI / 4) })));

    }

    mechanics.emplace_back(new Spread(44.5f, 100, 1, 4,
        Target(TARGET_POS,
            { 500.f + 350.f * std::cos(2.f * 28 * PI / 16.f - PI / 4),
             500.f + 350.f * std::sin(2.f * 28 * PI / 16.f - PI / 4) })));
    mechanics.emplace_back(new Spread(44.4f, 100, 1, 4,
        Target(TARGET_POS,
            { 500.f + 350.f * std::cos(PI + 2.f * 28 * PI / 16.f - PI / 4),
             500.f + 350.f * std::sin(PI + 2.f * 28 * PI / 16.f - PI / 4) })));

    mechanics.emplace_back(new Spread(45.5f, 100, 1, 4,
        Target(TARGET_POS,
            { 500.f + 300.f * std::cos(2.f * 28 * PI / 16.f - PI / 4),
             500.f + 300.f * std::sin(2.f * 28 * PI / 16.f - PI / 4) })));
    mechanics.emplace_back(new Spread(45.5f, 100, 1, 4,
        Target(TARGET_POS,
            { 500.f + 250.f * std::cos(PI + 2.f * 28 * PI / 16.f - PI / 4),
             500.f + 250.f * std::sin(PI + 2.f * 28 * PI / 16.f - PI / 4) })));

    mechanics.emplace_back(new Spread(46.5f, 100, 1, 4,
        Target(TARGET_POS,
            { 500.f + 200.f * std::cos(2.f * 28 * PI / 16.f - PI / 4),
             500.f + 200.f * std::sin(2.f * 28 * PI / 16.f - PI / 4) })));
    mechanics.emplace_back(new Spread(46.5f, 100, 1, 4,
        Target(TARGET_POS,
            { 500.f + 200.f * std::cos(PI + 2.f * 28 * PI / 16.f - PI / 4),
             500.f + 200.f * std::sin(PI + 2.f * 28 * PI / 16.f - PI / 4) })));

    mechanics.emplace_back(new Spread(47.5f, 100, 1, 4,
        Target(TARGET_POS,
            { 500.f + 150.f * std::cos(2.f * 28 * PI / 16.f - PI / 4),
             500.f + 150.f * std::sin(2.f * 28 * PI / 16.f - PI / 4) })));
    mechanics.emplace_back(new Spread(47.5f, 100, 1, 4,
        Target(TARGET_POS,
            { 500.f + 150.f * std::cos(PI + 2.f * 28 * PI / 16.f - PI / 4),
             500.f + 150.f * std::sin(PI + 2.f * 28 * PI / 16.f - PI / 4) })));


    // COUPLET 1

    mechanics.emplace_back(new Spread(48, 200, 2, 8,
        Target(TARGET_POS, { 500.f,500.f })));

    mechanics.emplace_back(new Tether(49.5,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        300, 4, false, false));

    mechanics.emplace_back(new Spread(51, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(51.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(52, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(52.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(53, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(53.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(54, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(55, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));

    mechanics.emplace_back(new Spread(51, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(51.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(52, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(52.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(53, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(53.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(54, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(55, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));




    mechanics.emplace_back(new Spread(56, 200, 2, 8,
        Target(TARGET_POS, { 500.f,500.f })));

    mechanics.emplace_back(new Tether(57.5,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        300, 4, false, false));

    mechanics.emplace_back(new Spread(59, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(59.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(60, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(60.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(61.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(62, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(63, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));

    mechanics.emplace_back(new Spread(59, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(59.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(60, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(60.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(61.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(62, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(63, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));



    mechanics.emplace_back(new Spread(64, 200, 2, 8,
        Target(TARGET_POS, { 500.f,500.f })));

    mechanics.emplace_back(new Tether(65.5,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        300, 4, false, false));

    mechanics.emplace_back(new Spread(67, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(67.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(68, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(68.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(69, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(69.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(70, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(71, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));

    mechanics.emplace_back(new Spread(67, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(67.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(68, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(68.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(69, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(69.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(70, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(71, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));



    mechanics.emplace_back(new Spread(72, 200, 2, 8,
        Target(TARGET_POS, { 500.f,500.f })));

    mechanics.emplace_back(new Tether(73.5,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        300, 4, false, false));

    mechanics.emplace_back(new Spread(75, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(75.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));

    mechanics.emplace_back(new Spread(75, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(75.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));


    // COUPLET 2

    mechanics.emplace_back(new Tether(88,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        500, 12, true, true));

    for (int i = 0; i < 4; i++) {
        mechanics.emplace_back(new Spread(80 + 2 * i, 150, 1, 4,
            Target(TARGET_POS, { 150.f + 87.5f * 2 * i, 250 })));
        mechanics.emplace_back(new Spread(80 + 2 * i, 150, 1, 4,
            Target(TARGET_POS, { 150.f + 87.5f * 2 * i, 750 })));
    }


    mechanics.emplace_back(new Tether(96,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        500, 8, false, true));

    for (int i = 0; i < 4; i++) {
        mechanics.emplace_back(new Spread(88 + 2 * i, 150, 1, 4,
            Target(TARGET_POS, { 850.f - 87.5f * 2 * i, 250 })));
        mechanics.emplace_back(new Spread(88 + 2 * i, 150, 1, 4,
            Target(TARGET_POS, { 850.f - 87.5f * 2 * i, 750 })));
    }


    mechanics.emplace_back(new Tether(104,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        500, 8, true, true));

    for (int i = 0; i < 4; i++) {
        mechanics.emplace_back(new Spread(96 + 2 * i, 150, 1, 4,
            Target(TARGET_POS, { 150.f + 87.5f * 2 * i, 250 })));
        mechanics.emplace_back(new Spread(96 + 2 * i, 150, 1, 4,
            Target(TARGET_POS, { 150.f + 87.5f * 2 * i, 750 })));
    }


    mechanics.emplace_back(new Tether(112,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        500, 8, false, true));

    for (int i = 0; i < 4; i++) {
        mechanics.emplace_back(new Spread(104 + 2 * i, 150, 1, 4,
            Target(TARGET_POS, { 850.f - 87.5f * 2 * i, 250 })));
        mechanics.emplace_back(new Spread(104 + 2 * i, 150, 1, 4,
            Target(TARGET_POS, { 850.f - 87.5f * 2 * i, 750 })));
    }


    // COUPLET 3

    for (int ii = 0; ii < 4; ii++) {
        auto i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(112 + 4 * i, 300, 1, 4,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(114 + 4 * i, 300, 0, 2,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
        mechanics.emplace_back(new Spread(112 + 4 * i, 300, 1, 4,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(114 + 4 * i, 300, 0, 2,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    }

    for (int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(128 + 2 * i, 100, 1, 2,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(129 + 2 * i, 100, 0, 1,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
        mechanics.emplace_back(new Spread(128 + 2 * i, 100, 1, 2,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(129 + 2 * i, 100, 0, 1,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    }


    // REFRAIN 1

    mechanics.emplace_back(new MoveEntity(140, Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        Target(TARGET_POS, { 500, 50 }), -1, true));
    mechanics.emplace_back(new ActivateTotem(140, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));

    mechanics.emplace_back(new MoveEntity(140, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        Target(TARGET_POS, { 500, 950 }), -1, true));
    mechanics.emplace_back(new ActivateTotem(140, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));

    mechanics.emplace_back(new Tether(144,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        300, 4, true, false));

    mechanics.emplace_back(new Tether(144,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        300, 4, true, false));


    mechanics.emplace_back(new Tether(148,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        800, 4, false, false));

    mechanics.emplace_back(new Tether(152,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        300, 4, true, false));

    mechanics.emplace_back(new Tether(156,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        800, 4, false, false));

    mechanics.emplace_back(new Tether(148,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        800, 4, false, false));

    mechanics.emplace_back(new Tether(152,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        300, 4, true, false));

    mechanics.emplace_back(new Tether(156,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        800, 4, false, false));



    for (int ii = 0; ii < 13; ii++) {
        auto i = static_cast<float>(ii);
        float ac = ii == 0 ? 4 : 1;
        mechanics.emplace_back(new MoveEntity(160 + i, Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
            Target(TARGET_POS, { 500.f + 450.f * std::cos(2.f * i * PI / 16.f - PI / 2),
                                      500.f + 450.f * std::sin(2.f * i * PI / 16.f - PI / 2) }), 500, false));

        mechanics.emplace_back(new Spread(160 + i, 200, 1, ac,
            Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));



        mechanics.emplace_back(new MoveEntity(160 + i, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
            Target(TARGET_POS, { 500.f + 450.f * std::cos(2.f * i * PI / 16.f + PI / 2),
                                      500.f + 450.f * std::sin(2.f * i * PI / 16.f + PI / 2) }), 500, false));

        mechanics.emplace_back(new Spread(160 + i, 200, 1, ac,
            Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    }


    mechanics.emplace_back(new Tether(176,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        300, 4, true, false));

    mechanics.emplace_back(new Tether(176,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        300, 4, true, false));

    mechanics.emplace_back(new Tether(180,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        800, 4, false, false));

    mechanics.emplace_back(new Tether(184,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        300, 4, true, false));

    mechanics.emplace_back(new Tether(188,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        800, 4, false, false));

    mechanics.emplace_back(new Tether(180,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        800, 4, false, false));

    mechanics.emplace_back(new Tether(184,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        300, 4, true, false));

    mechanics.emplace_back(new Tether(188,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        800, 4, false, false));



    for (int ii = 0; ii < 13; ii++) {
        auto i = static_cast<float>(ii);
        float ac = ii == 0 ? 4 : 1;
        mechanics.emplace_back(new MoveEntity(192 + i, Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
            Target(TARGET_POS, { 500.f + 450.f * std::cos(2.f * i * PI / 16.f + PI),
                                      500.f + 450.f * std::sin(2.f * i * PI / 16.f + PI) }), 500, false));

        mechanics.emplace_back(new Spread(192 + i, 200, 1, ac,
            Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));



        mechanics.emplace_back(new MoveEntity(192 + i, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
            Target(TARGET_POS, { 500.f + 450.f * std::cos(2.f * i * PI / 16.f),
                                      500.f + 450.f * std::sin(2.f * i * PI / 16.f) }), 500, false));

        mechanics.emplace_back(new Spread(192 + i, 200, 1, ac,
            Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    }



    mechanics.emplace_back(new Spread(208, 300, 2, 4,
        Target(TARGET_POS, { 500,500 })));


    mechanics.emplace_back(new ActivateTotem(212, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));
    mechanics.emplace_back(new ActivateTotem(212, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false));


    // COUPLET 1

    mechanics.emplace_back(new Spread(216, 200, 2, 8,
        Target(TARGET_POS, { 500.f,500.f })));

    mechanics.emplace_back(new Tether(217.5,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        300, 4, false, false));

    mechanics.emplace_back(new Spread(219, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(219.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(220, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(220.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(221, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(221.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(222, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(223, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));

    mechanics.emplace_back(new Spread(219, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(219.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(220, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(220.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(221, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(221.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(222, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(223, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));




    mechanics.emplace_back(new Spread(224, 200, 2, 8,
        Target(TARGET_POS, { 500.f,500.f })));

    mechanics.emplace_back(new Tether(225.5,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        300, 4, false, false));

    mechanics.emplace_back(new Spread(227, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(227.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(228, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(228.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(229.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(230, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(231, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));

    mechanics.emplace_back(new Spread(227, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(227.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(228, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(228.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(229.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(230, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(231, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));



    mechanics.emplace_back(new Spread(232, 200, 2, 8,
        Target(TARGET_POS, { 500.f,500.f })));

    mechanics.emplace_back(new Tether(233.5,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        300, 4, false, false));

    mechanics.emplace_back(new Spread(235, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(235.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(236, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(236.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(237, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(237.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(238, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(239, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));

    mechanics.emplace_back(new Spread(235, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(235.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(236, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(236.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(237, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(237.5, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(238, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(239, 70, 0, 1,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));



    mechanics.emplace_back(new Spread(240, 200, 2, 8,
        Target(TARGET_POS, { 500.f,500.f })));

    mechanics.emplace_back(new Spread(244, 300, 1, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(244, 300, 1, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(247.5, 300, 2, 3.5,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(247.5, 300, 2, 3.5,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));



    // COUPLET 3

    for (int ii = 0; ii < 3; ii++) {
        auto i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(252 + 4 * i, 300, 1, 4,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(254 + 4 * i, 300, 0, 2,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
        mechanics.emplace_back(new Spread(252 + 4 * i, 300, 1, 4,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(254 + 4 * i, 300, 0, 2,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    }

    for (int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(264 + 2 * i, 100, 1, 2,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(265 + 2 * i, 100, 0, 1,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
        mechanics.emplace_back(new Spread(264 + 2 * i, 100, 1, 2,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(265 + 2 * i, 100, 0, 1,
            Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    }


    mechanics.emplace_back(new Spread(278, 300, 2, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));


    mechanics.emplace_back(new Spread(280, 200, 1, 4,
        Target(TARGET_POS,
            { 500.f + 300.f * std::cos(2.f * PI / 16.f - PI / 4),
             500.f + 300.f * std::sin(2.f * PI / 16.f - PI / 4) })));
    mechanics.emplace_back(new Spread(280, 200, 1, 4,
        Target(TARGET_POS,
            { 500.f + 300.f * std::cos(PI + 2.f * PI / 16.f - PI / 4),
             500.f + 300.f * std::sin(PI + 2.f * PI / 16.f - PI / 4) })));




    // INTRO

    for (int ii = 0; ii < 26; ii++) {
        auto i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(282 + i + 0.5f, 100, 1, 4,
            Target(TARGET_POS,
                { 500.f + 350.f * std::cos(2.f * i * PI / 16.f - PI / 4),
                 500.f + 350.f * std::sin(2.f * i * PI / 16.f - PI / 4) })));
        mechanics.emplace_back(new Spread(282 + i + 0.5f, 100, 1, 4,
            Target(TARGET_POS,
                { 500.f + 350.f * std::cos(PI + 2.f * i * PI / 16.f - PI / 4),
                 500.f + 350.f * std::sin(PI + 2.f * i * PI / 16.f - PI / 4) })));

    }

    // RAMPUP

    mechanics.emplace_back(new MoveEntity(308, Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
        Target(TARGET_POS, { 300, 50 }), -1, true));
    mechanics.emplace_back(new ActivateTotem(308, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true));

    mechanics.emplace_back(new MoveEntity(308, Target(TARGET_ENTITY, TARGET_TOTEMS, 3),
        Target(TARGET_POS, { 700, 50 }), -1, true));
    mechanics.emplace_back(new ActivateTotem(308, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true));


    mechanics.emplace_back(new Tether(342,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
        300, 34, true, true));

    mechanics.emplace_back(new Tether(342,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 3),
        300, 34, true, true));

    mechanics.emplace_back(new Spread(312, 150, 2, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));

    mechanics.emplace_back(new MoveEntity(312, Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
        Target(TARGET_POS, { 300, 500 }), 200, false));

    mechanics.emplace_back(new MoveEntity(312, Target(TARGET_ENTITY, TARGET_TOTEMS, 3),
        Target(TARGET_POS, { 700, 500 }), 200, false));

    mechanics.emplace_back(new Spread(316, 150, 2, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(318, 150, 1, 2,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(318.5, 150, 1, 2.5,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));



    mechanics.emplace_back(new Spread(320, 150, 2, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));

    mechanics.emplace_back(new MoveEntity(320, Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
        Target(TARGET_POS, { 300, 950 }), 200, false));

    mechanics.emplace_back(new MoveEntity(320, Target(TARGET_ENTITY, TARGET_TOTEMS, 3),
        Target(TARGET_POS, { 700, 950 }), 200, false));

    mechanics.emplace_back(new Spread(324, 150, 2, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(326, 150, 1, 2,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(326.5, 150, 1, 2,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));




    mechanics.emplace_back(new Spread(328, 150, 2, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));

    mechanics.emplace_back(new MoveEntity(328, Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
        Target(TARGET_POS, { 50, 500 }), 300, false));

    mechanics.emplace_back(new MoveEntity(328, Target(TARGET_ENTITY, TARGET_TOTEMS, 3),
        Target(TARGET_POS, { 450, 500 }), 300, false));

    mechanics.emplace_back(new Spread(332, 150, 2, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));

    mechanics.emplace_back(new MoveEntity(332, Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
        Target(TARGET_POS, { 300, 50 }), 300, false));

    mechanics.emplace_back(new MoveEntity(332, Target(TARGET_ENTITY, TARGET_TOTEMS, 3),
        Target(TARGET_POS, { 700, 50 }), 300, false));

    mechanics.emplace_back(new Spread(336, 150, 2, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));

    mechanics.emplace_back(new MoveEntity(336, Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
        Target(TARGET_POS, { 550, 500 }), 300, false));

    mechanics.emplace_back(new MoveEntity(336, Target(TARGET_ENTITY, TARGET_TOTEMS, 3),
        Target(TARGET_POS, { 950, 500 }), 300, false));


    mechanics.emplace_back(new Spread(340, 150, 2, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(342, 150, 1, 2,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(342.5, 150, 1, 2,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));


    mechanics.emplace_back(new ActivateTotem(344, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), false));
    mechanics.emplace_back(new ActivateTotem(344, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), false));


    // REFRAIN 1

    mechanics.emplace_back(new MoveEntity(344, Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        Target(TARGET_POS, { 500, 50 }), -1, true));
    mechanics.emplace_back(new ActivateTotem(344, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true));

    mechanics.emplace_back(new MoveEntity(344, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        Target(TARGET_POS, { 500, 950 }), -1, true));
    mechanics.emplace_back(new ActivateTotem(344, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true));

    mechanics.emplace_back(new Tether(348,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        300, 4, true, false));

    mechanics.emplace_back(new Tether(348,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        300, 4, true, false));


    mechanics.emplace_back(new Tether(352,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        800, 4, false, false));

    mechanics.emplace_back(new Tether(356,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        300, 4, true, false));

    mechanics.emplace_back(new Tether(360,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        800, 4, false, false));

    mechanics.emplace_back(new Tether(352,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        800, 4, false, false));

    mechanics.emplace_back(new Tether(356,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        300, 4, true, false));

    mechanics.emplace_back(new Tether(360,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        800, 4, false, false));

    for (int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(348, 250, 0, 4,
            Target(TARGET_POS, { 750,i * 250 })));
    }

    for (int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(352, 250, 0, 4,
            Target(TARGET_POS, { 250,i * 250 })));
    }

    for (int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(356, 250, 0, 4,
            Target(TARGET_POS, { 750,i * 250 })));
    }

    for (int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(360, 250, 0, 4,
            Target(TARGET_POS, { 250,i * 250 })));
    }





    for (int ii = 0; ii < 13; ii++) {
        auto i = static_cast<float>(ii);
        float ac = ii == 0 ? 4 : 1;
        mechanics.emplace_back(new MoveEntity(364 + i, Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
            Target(TARGET_POS, { 500.f + 450.f * std::cos(2.f * i * PI / 16.f - PI / 2),
                                500.f + 450.f * std::sin(2.f * i * PI / 16.f - PI / 2) }), 500, false));

        mechanics.emplace_back(new Spread(364 + i, 200, 1, ac,
            Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));



        mechanics.emplace_back(new MoveEntity(364 + i, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
            Target(TARGET_POS, { 500.f + 450.f * std::cos(2.f * i * PI / 16.f + PI / 2),
                                500.f + 450.f * std::sin(2.f * i * PI / 16.f + PI / 2) }), 500, false));

        mechanics.emplace_back(new Spread(364 + i, 200, 1, ac,
            Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    }



    mechanics.emplace_back(new Tether(380,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        300, 4, true, false));

    mechanics.emplace_back(new Tether(384,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        800, 4, false, false));

    mechanics.emplace_back(new Tether(388,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        300, 4, true, false));

    mechanics.emplace_back(new Tether(392,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        800, 4, false, false));

    mechanics.emplace_back(new Tether(380,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
        300, 4, true, false));

    mechanics.emplace_back(new Tether(384,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        800, 4, false, false));

    mechanics.emplace_back(new Tether(388,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        300, 4, true, false));

    mechanics.emplace_back(new Tether(392,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1),
        Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        800, 4, false, false));

    for (int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(380, 250, 0, 4,
            Target(TARGET_POS, { i * 250, 250 + 500.f * (ii < 3) })));
    }

    for (int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(384, 250, 0, 4,
            Target(TARGET_POS, { i * 250, 250 + 500.f * (ii >= 3) })));
    }


    for (int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(388, 250, 0, 4,
            Target(TARGET_POS, { i * 250, 250 })));
    }

    for (int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(392, 250, 0, 4,
            Target(TARGET_POS, { i * 250, 750 })));
    }



    for (int ii = 0; ii < 13; ii++) {
        auto i = static_cast<float>(ii);
        float ac = ii == 0 ? 4 : 1;
        mechanics.emplace_back(new MoveEntity(396 + i, Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
            Target(TARGET_POS, { 500.f + 450.f * std::cos(2.f * i * PI / 16.f + PI),
                                500.f + 450.f * std::sin(2.f * i * PI / 16.f + PI) }), 500, false));

        mechanics.emplace_back(new Spread(396 + i, 200, 1, ac,
            Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW)));



        mechanics.emplace_back(new MoveEntity(396 + i, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
            Target(TARGET_POS, { 500.f + 450.f * std::cos(2.f * i * PI / 16.f),
                                500.f + 450.f * std::sin(2.f * i * PI / 16.f) }), 500, false));

        mechanics.emplace_back(new Spread(396 + i, 200, 1, ac,
            Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));
    }

    mechanics.emplace_back(new ActivateTotem(408, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));
    mechanics.emplace_back(new ActivateTotem(408, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false));



    // OUTRO

    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new Spread(412, 200, 0, 4,
            Target(TARGET_POS, { i * 200.f, 400.f })));

        mechanics.emplace_back(new Spread(412, 200, 0, 4,
            Target(TARGET_POS, { 400.f, i * 200.f })));
    }

    mechanics.emplace_back(new Spread(416, 200, 0, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(416, 200, 0, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new Spread(416, 200, 0, 4,
            Target(TARGET_POS, { i * 200.f, 600.f })));

        mechanics.emplace_back(new Spread(416, 200, 0, 4,
            Target(TARGET_POS, { 600.f, i * 200.f })));
    }

    mechanics.emplace_back(new Spread(420, 200, 0, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(420, 200, 0, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new Spread(420, 200, 0, 4,
            Target(TARGET_POS, { i * 200.f, 600.f })));

        mechanics.emplace_back(new Spread(420, 200, 0, 4,
            Target(TARGET_POS, { 400.f, i * 200.f })));
    }

    mechanics.emplace_back(new Spread(424, 224, 0, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(424, 224, 0, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new Spread(424, 200, 0, 4,
            Target(TARGET_POS, { i * 200.f, 400.f })));

        mechanics.emplace_back(new Spread(424, 200, 0, 4,
            Target(TARGET_POS, { 600.f, i * 200.f })));
    }

    mechanics.emplace_back(new Spread(428, 200, 0, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(428, 200, 0, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new Spread(428, 200, 0, 4,
            Target(TARGET_POS, { i * 200.f, i * 200.f })));

        mechanics.emplace_back(new Spread(428, 200, 0, 4,
            Target(TARGET_POS, { (5.f - i) * 200.f, i * 200.f })));
    }

    mechanics.emplace_back(new Spread(432, 200, 0, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(432, 200, 0, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new Spread(432, 200, 0, 4,
            Target(TARGET_POS, { i * 200.f, 500 })));

        mechanics.emplace_back(new Spread(432, 200, 0, 4,
            Target(TARGET_POS, { 500, i * 200.f })));
    }

    mechanics.emplace_back(new Spread(436, 200, 0, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(436, 200, 0, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new Spread(436, 200, 0, 4,
            Target(TARGET_POS, { i * 200.f, i * 200.f })));

        mechanics.emplace_back(new Spread(436, 200, 0, 4,
            Target(TARGET_POS, { (5.f - i) * 200.f, i * 200.f })));
    }

    mechanics.emplace_back(new Spread(440, 200, 0, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(440, 200, 0, 4,
        Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));

    for (int ii = 0; ii < 6; ii++) {
        auto i = static_cast<float>(ii);
        mechanics.emplace_back(new Spread(440, 200, 0, 4,
            Target(TARGET_POS, { i * 200.f, 500 })));

        mechanics.emplace_back(new Spread(440, 200, 0, 4,
            Target(TARGET_POS, { 500, i * 200.f })));
    }

    mechanics.emplace_back(new ApplyDebuff(440, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT), DEBUFF_ROOT, 4));

    for (int ii = 0; ii < 16; ii++) {
        auto i = static_cast<float>(ii);

        if (ii != 15)
            mechanics.emplace_back(new ApplyDebuff(444 + 2 * i, Target(TARGET_ENTITY, TARGET_PLAYERS, ii % 2, TARGET_ONINIT), DEBUFF_ROOT, 2));

        mechanics.emplace_back(new Spread(444 + 2 * i, 200, 1, 4,
            Target(TARGET_POS, { 500.f + 250.f * std::cos(2.f * i * PI / 4.f),
                                500.f + 250.f * std::sin(2.f * i * PI / 4.f) })));


    }

    mechanics.emplace_back(new Spread(476, 200, 2, 4,
        Target(TARGET_POS, { 500.f, 500.f })));

    mechanics.emplace_back(new EndMap(482));
}

void doggyGodStreet(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em)
{
    sf::Uint32 in = 0x0ED4B9FF, out = 0xFF7F11FF;

    // Intro

    song.addCheckpoint(0, 0);



    mechanics.emplace_back(new MoveEntity(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_POS, { 200, 200 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_POS, { 200, 800 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_POS, { 800, 200 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_POS, { 800, 800 }), 1000, true));



    // Couplet

    song.addCheckpoint(10, 27);

    /*mechanics.emplace_back(new MoveEntity(28, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_POS, {200, 200}), 1000, true));
    mechanics.emplace_back(new MoveEntity(28, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_POS, { 200, 800 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(28, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_POS, { 800, 200 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(28, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_POS, { 800, 800 }), 1000, true));
    mechanics.emplace_back(new Tether(28, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_POS, { 200, 200 }), 100, 4, true, false));
    mechanics.emplace_back(new Tether(28, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_POS, { 200, 800 }), 100, 4, true, false));
    mechanics.emplace_back(new Tether(28, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_POS, { 800, 200 }), 100, 4, true, false));
    mechanics.emplace_back(new Tether(28, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_POS, { 800, 800 }), 100, 4, true, false));*/


    mechanics.emplace_back(new Spread(28, 250, 1, 4, Target(TARGET_POS, { 200, 200 })));
    mechanics.emplace_back(new Spread(28, 250, 1, 4, Target(TARGET_POS, { 200, 800 })));
    mechanics.emplace_back(new Spread(28, 250, 1, 4, Target(TARGET_POS, { 800, 200 })));
    mechanics.emplace_back(new Spread(28, 250, 1, 4, Target(TARGET_POS, { 800, 800 })));

    mechanics.emplace_back(new Donut(32, 250, 707, 0, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(34, 250, 0, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(36, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(36, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(36, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(36, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(38, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(38, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(38, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(38, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_ONINIT)));

    mechanics.emplace_back(new Donut(40, 100, 500, 0, 4, Target(TARGET_POS, { 200, 500 })));
    mechanics.emplace_back(new Spread(42, 100, 0, 4, Target(TARGET_POS, { 200, 500 })));
    mechanics.emplace_back(new Donut(40, 100, 500, 0, 4, Target(TARGET_POS, { 800, 500 })));
    mechanics.emplace_back(new Spread(42, 100, 0, 4, Target(TARGET_POS, { 800, 500 })));
    mechanics.emplace_back(new Spread(44, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(44, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(44, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(44, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(46, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(46, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(46, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(46, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_ONINIT)));


    mechanics.emplace_back(new Donut(48, 100, 700, 0, 4, Target(TARGET_POS, { 200, 200 })));
    mechanics.emplace_back(new Spread(50, 100, 0, 4, Target(TARGET_POS, { 200, 200 })));
    mechanics.emplace_back(new Donut(48, 100, 700, 0, 4, Target(TARGET_POS, { 800, 800 })));
    mechanics.emplace_back(new Spread(50, 100, 0, 4, Target(TARGET_POS, { 800, 800 })));
    mechanics.emplace_back(new Spread(52, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(52, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(52, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(52, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(54, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(54, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(54, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(54, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_ONINIT)));


    mechanics.emplace_back(new Donut(56, 100, 700, 0, 4, Target(TARGET_POS, { 200, 800 })));
    mechanics.emplace_back(new Spread(58, 100, 0, 4, Target(TARGET_POS, { 200, 800 })));
    mechanics.emplace_back(new Donut(56, 100, 700, 0, 4, Target(TARGET_POS, { 800, 200 })));
    mechanics.emplace_back(new Spread(58, 100, 0, 4, Target(TARGET_POS, { 800, 200 })));
    mechanics.emplace_back(new Spread(60, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(60, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(60, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(60, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(62, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(62, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(62, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(62, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_ONINIT)));


    // Refrain

    song.addCheckpoint(25, 64);

    for (int i = 0; i < 7; i++) {
        mechanics.emplace_back(new Tether(68 + 4 * i, Target(TARGET_ENTITY, TARGET_PLAYERS, (i + 1) % 2), Target(TARGET_POS, { 200, 800 }), 100, 4, true, false));
        mechanics.emplace_back(new Tether(68 + 4 * i, Target(TARGET_ENTITY, TARGET_PLAYERS, (i + 1) % 2 + 2), Target(TARGET_POS, { 800, 200 }), 100, 4, true, false));
        mechanics.emplace_back(new Cone(68 + 4 * i, 120, 2500, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, i % 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Cone(68 + 4 * i, 120, 2500, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, i % 2 + 2, TARGET_FOLLOW)));

    }

    mechanics.emplace_back(new Tether(96, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_POS, { 200, 200 }), 100, 4, true, false));
    mechanics.emplace_back(new Tether(96, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_POS, { 200, 800 }), 100, 4, true, false));
    mechanics.emplace_back(new Tether(96, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_POS, { 800, 200 }), 100, 4, true, false));
    mechanics.emplace_back(new Tether(96, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_POS, { 800, 800 }), 100, 4, true, false));


    // Break

    song.addCheckpoint(40, 96.1);

    mechanics.emplace_back(new MoveEntity(96.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_POS, { 200, 200 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(96.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_POS, { 200, 800 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(96.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_POS, { 800, 200 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(96.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_POS, { 800, 800 }), 1000, true));

    mechanics.emplace_back(new Tether(112, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 100, 16, true, false));

    mechanics.emplace_back(new ActivateTotem(104, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, in));
    mechanics.emplace_back(new ActivateTotem(104, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, out));
    mechanics.emplace_back(new MoveEntity(104, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(104, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 800, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(108, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_ONINIT), Target(TARGET_ENTITY, TARGET_TOTEMS, 1), 1000, true));

    mechanics.emplace_back(new Tether(128, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 100, 16, true, false));
    mechanics.emplace_back(new MoveEntity(112, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 800, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(112, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 200, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(124, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_ONINIT), Target(TARGET_ENTITY, TARGET_TOTEMS, 1), 1000, true));



    mechanics.emplace_back(new ActivateTotem(128, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, in));
    mechanics.emplace_back(new ActivateTotem(128, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, out));
    mechanics.emplace_back(new ActivateTotem(128, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true, in));
    mechanics.emplace_back(new ActivateTotem(128, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true, out));
    mechanics.emplace_back(new MoveEntity(128, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 800, 400 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(128, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 200, 400 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(128, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 800, 600 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(128, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 200, 600 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(132, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_ONINIT), Target(TARGET_ENTITY, TARGET_TOTEMS, 1), 1000, true));
    mechanics.emplace_back(new MoveEntity(133, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW), TARGET_ONINIT), Target(TARGET_ENTITY, TARGET_TOTEMS, 3), 1000, true));

    mechanics.emplace_back(new ActivateTotem(132, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false, in));
    mechanics.emplace_back(new ActivateTotem(132, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false, out));
    mechanics.emplace_back(new ActivateTotem(133, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), false, in));
    mechanics.emplace_back(new ActivateTotem(133, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), false, out));

    mechanics.emplace_back(new Spread(136, 250, 4, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));


    mechanics.emplace_back(new Spread(140, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(140, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(140, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(140, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));

    mechanics.emplace_back(new Donut(144, 200, 1100, 0, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Donut(144, 200, 1100, 0, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Donut(144, 200, 1100, 0, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Donut(144, 200, 1100, 0, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));

    mechanics.emplace_back(new Cone(148, 60, 2500, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(148, 60, 2500, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(148, 60, 2500, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(148, 60, 2500, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));


    mechanics.emplace_back(new ActivateTotem(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, in));
    mechanics.emplace_back(new ActivateTotem(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, out));
    mechanics.emplace_back(new ActivateTotem(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true, in));
    mechanics.emplace_back(new ActivateTotem(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true, out));
    mechanics.emplace_back(new MoveEntity(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 400 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 800, 400 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 200, 600 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(152, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 600 }), 1000, true));

    mechanics.emplace_back(new MoveEntity(156, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_ONINIT), Target(TARGET_ENTITY, TARGET_TOTEMS, 1), 1000, true));
    mechanics.emplace_back(new MoveEntity(157, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW), TARGET_ONINIT), Target(TARGET_ENTITY, TARGET_TOTEMS, 3), 1000, true));

    mechanics.emplace_back(new ActivateTotem(156, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false, in));
    mechanics.emplace_back(new ActivateTotem(156, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false, out));
    mechanics.emplace_back(new ActivateTotem(157, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), false, in));
    mechanics.emplace_back(new ActivateTotem(157, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), false, out));

    mechanics.emplace_back(new Tether(160, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_POS, { 200, 200 }), 100, 12, true, false));
    mechanics.emplace_back(new Tether(160, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_POS, { 200, 800 }), 100, 12, true, false));
    mechanics.emplace_back(new Tether(160, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_POS, { 800, 200 }), 100, 12, true, false));
    mechanics.emplace_back(new Tether(160, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_POS, { 800, 800 }), 100, 12, true, false));


    // Couplet

    song.addCheckpoint(70, 160.1);

    mechanics.emplace_back(new MoveEntity(160.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_POS, { 200, 200 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(160.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_POS, { 200, 800 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(160.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_POS, { 800, 200 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(160.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_POS, { 800, 800 }), 1000, true));

    mechanics.emplace_back(new Donut(168, 250, 707, 0, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(170, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(170, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(170, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(170, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(172, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(172, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(172, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(172, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(174, 250, 4, 4, Target(TARGET_POS, { 500, 500 })));

    mechanics.emplace_back(new Donut(176, 100, 500, 0, 4, Target(TARGET_POS, { 200, 500 })));
    mechanics.emplace_back(new Donut(176, 100, 500, 0, 4, Target(TARGET_POS, { 800, 500 })));
    mechanics.emplace_back(new Spread(178, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(178, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(178, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(178, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(180, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(180, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(180, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(180, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(182, 100, 2, 4, Target(TARGET_POS, { 200, 500 })));
    mechanics.emplace_back(new Spread(182, 100, 2, 4, Target(TARGET_POS, { 800, 500 })));

    mechanics.emplace_back(new Donut(184, 100, 700, 0, 4, Target(TARGET_POS, { 200, 800 })));
    mechanics.emplace_back(new Donut(184, 100, 700, 0, 4, Target(TARGET_POS, { 800, 200 })));
    mechanics.emplace_back(new Spread(186, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(186, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(186, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(186, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(188, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(188, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(188, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(188, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(190, 100, 2, 4, Target(TARGET_POS, { 200, 800 })));
    mechanics.emplace_back(new Spread(190, 100, 2, 4, Target(TARGET_POS, { 800, 200 })));


    // Refrain

    song.addCheckpoint(85, 192);


    for (int i = 0; i < 7; i++) {
        mechanics.emplace_back(new Tether(196 + 4 * i, Target(TARGET_ENTITY, TARGET_PLAYERS, (i + 1) % 2), Target(TARGET_POS, { 200, 800 }), 100, 4, true, false));
        mechanics.emplace_back(new Tether(196 + 4 * i, Target(TARGET_ENTITY, TARGET_PLAYERS, (i + 1) % 2 + 2), Target(TARGET_POS, { 800, 200 }), 100, 4, true, false));
        mechanics.emplace_back(new Cone(196 + 4 * i, 120, 2500, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, i % 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Cone(196 + 4 * i, 120, 2500, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, i % 2 + 2, TARGET_FOLLOW)));
        if (i < 4) {
            mechanics.emplace_back(new NopeZone(196 + 8 * i, 200, 500, 0, 8, Target(TARGET_POS, { 0 + 200 * (float)(i % 2), 500 })));
            mechanics.emplace_back(new NopeZone(196 + 8 * i, 200, 500, 0, 8, Target(TARGET_POS, { 600 + 200 * (float)(i % 2), 500 })));
        }

    }

    mechanics.emplace_back(new Tether(224, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_POS, { 200, 200 }), 100, 4, true, false));
    mechanics.emplace_back(new Tether(224, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_POS, { 200, 800 }), 100, 4, true, false));
    mechanics.emplace_back(new Tether(224, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_POS, { 800, 200 }), 100, 4, true, false));
    mechanics.emplace_back(new Tether(224, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_POS, { 800, 800 }), 100, 4, true, false));


    // Break

    song.addCheckpoint(100, 224.1);

    mechanics.emplace_back(new MoveEntity(224.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_POS, { 200, 200 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(224.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_POS, { 200, 800 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(224.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_POS, { 800, 200 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(224.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_POS, { 800, 800 }), 1000, true));

    mechanics.emplace_back(new Spread(232, 250, 3, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));

    mechanics.emplace_back(new ActivateTotem(224.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, in));
    mechanics.emplace_back(new ActivateTotem(224.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, out));
    mechanics.emplace_back(new MoveEntity(224.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(224.2, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 800, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(228, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_ONINIT), Target(TARGET_ENTITY, TARGET_TOTEMS, 1), 1000, true));
    mechanics.emplace_back(new ActivateTotem(228, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false, in));
    mechanics.emplace_back(new ActivateTotem(228, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false, out));


    mechanics.emplace_back(new NopeZone(240, 401, 1000, 0, 8, Target(TARGET_POS, { 0, 0 })));

    mechanics.emplace_back(new ActivateTotem(232, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, in));
    mechanics.emplace_back(new ActivateTotem(232, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, out));
    mechanics.emplace_back(new MoveEntity(232, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(232, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 800, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(236, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_ONINIT), Target(TARGET_ENTITY, TARGET_TOTEMS, 1), 1000, true));
    mechanics.emplace_back(new ActivateTotem(236, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false, in));
    mechanics.emplace_back(new ActivateTotem(236, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false, out));


    mechanics.emplace_back(new NopeZone(248, 401, 500, 0, 8, Target(TARGET_POS, { 600, 0 })));
    mechanics.emplace_back(new Spread(248, 500, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));

    mechanics.emplace_back(new ActivateTotem(240, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, in));
    mechanics.emplace_back(new ActivateTotem(240, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, out));
    mechanics.emplace_back(new MoveEntity(240, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 800, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(240, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 200, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(244, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_ONINIT), Target(TARGET_ENTITY, TARGET_TOTEMS, 1), 1000, true));
    mechanics.emplace_back(new ActivateTotem(244, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false, in));
    mechanics.emplace_back(new ActivateTotem(244, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false, out));

    mechanics.emplace_back(new NopeZone(256, 401, 500, 0, 8, Target(TARGET_POS, { 600, 0 })));
    mechanics.emplace_back(new Spread(256, 500, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));

    mechanics.emplace_back(new ActivateTotem(248, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, in));
    mechanics.emplace_back(new ActivateTotem(248, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, out));
    mechanics.emplace_back(new MoveEntity(248, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 800, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(248, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 200, 500 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(252, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_ONINIT), Target(TARGET_ENTITY, TARGET_TOTEMS, 1), 1000, true));
    mechanics.emplace_back(new ActivateTotem(252, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false, in));
    mechanics.emplace_back(new ActivateTotem(252, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false, out));


    mechanics.emplace_back(new ActivateTotem(256, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, in));
    mechanics.emplace_back(new ActivateTotem(256, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, out));
    mechanics.emplace_back(new ActivateTotem(256, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true, in));
    mechanics.emplace_back(new ActivateTotem(256, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true, out));
    mechanics.emplace_back(new MoveEntity(256, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 200, 400 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(256, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 800, 400 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(256, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 200, 600 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(256, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 800, 600 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(260, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_ONINIT), Target(TARGET_ENTITY, TARGET_TOTEMS, 1), 1000, true));
    mechanics.emplace_back(new MoveEntity(261, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW), TARGET_ONINIT), Target(TARGET_ENTITY, TARGET_TOTEMS, 3), 1000, true));

    mechanics.emplace_back(new ActivateTotem(260, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false, in));
    mechanics.emplace_back(new ActivateTotem(260, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false, out));
    mechanics.emplace_back(new ActivateTotem(261, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), false, in));
    mechanics.emplace_back(new ActivateTotem(261, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), false, out));

    mechanics.emplace_back(new Spread(264, 250, 4, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 4; j++) {
            mechanics.emplace_back(new Cone(268 + 2 * i, 30, 2500, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_FOLLOW)));
            if (i != 5)
                mechanics.emplace_back(new Spread(268 + 2 * (i + 1), 200, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_ONINIT)));
        }
    }

    mechanics.emplace_back(new ActivateTotem(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, in));
    mechanics.emplace_back(new ActivateTotem(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, out));
    mechanics.emplace_back(new ActivateTotem(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true, in));
    mechanics.emplace_back(new ActivateTotem(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), true, out));
    mechanics.emplace_back(new MoveEntity(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 800, 400 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 200, 400 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 800, 600 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(280, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), Target(TARGET_POS, { 200, 600 }), 1000, true));

    mechanics.emplace_back(new MoveEntity(284, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_ONINIT), Target(TARGET_ENTITY, TARGET_TOTEMS, 1), 1000, true));
    mechanics.emplace_back(new MoveEntity(285, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 2), TARGET_ONINIT), Target(TARGET_ENTITY, TARGET_TOTEMS, 3), 1000, true));

    mechanics.emplace_back(new ActivateTotem(284, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false, in));
    mechanics.emplace_back(new ActivateTotem(284, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false, out));
    mechanics.emplace_back(new ActivateTotem(285, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), false, in));
    mechanics.emplace_back(new ActivateTotem(285, Target(TARGET_ENTITY, TARGET_TOTEMS, 3), false, out));

    mechanics.emplace_back(new Tether(288, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_POS, { 200, 200 }), 100, 8, true, false));
    mechanics.emplace_back(new Tether(288, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_POS, { 200, 800 }), 100, 8, true, false));
    mechanics.emplace_back(new Tether(288, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_POS, { 800, 200 }), 100, 8, true, false));
    mechanics.emplace_back(new Tether(288, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_POS, { 800, 800 }), 100, 8, true, false));


    // Couplet 

    song.addCheckpoint(130, 288.1);

    mechanics.emplace_back(new MoveEntity(288.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_POS, { 200, 200 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(288.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_POS, { 200, 800 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(288.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_POS, { 800, 200 }), 1000, true));
    mechanics.emplace_back(new MoveEntity(288.2, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_POS, { 800, 800 }), 1000, true));

    mechanics.emplace_back(new Donut(296, 250, 707, 0, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(298, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(298, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(298, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(298, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(300, 250, 4, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(302, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(302, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(302, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(302, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_ONINIT)));

    mechanics.emplace_back(new Donut(304, 100, 500, 0, 4, Target(TARGET_POS, { 200, 500 })));
    mechanics.emplace_back(new Donut(304, 100, 500, 0, 4, Target(TARGET_POS, { 800, 500 })));
    mechanics.emplace_back(new Spread(306, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(306, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(306, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(306, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(308, 100, 2, 4, Target(TARGET_POS, { 200, 500 })));
    mechanics.emplace_back(new Spread(308, 100, 2, 4, Target(TARGET_POS, { 800, 500 })));
    mechanics.emplace_back(new Spread(310, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(310, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(310, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(310, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_ONINIT)));


    mechanics.emplace_back(new Donut(312, 100, 700, 0, 4, Target(TARGET_POS, { 200, 200 })));
    mechanics.emplace_back(new Donut(312, 100, 700, 0, 4, Target(TARGET_POS, { 800, 800 })));
    mechanics.emplace_back(new Spread(314, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(314, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(314, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(314, 250, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(316, 100, 2, 4, Target(TARGET_POS, { 200, 200 })));
    mechanics.emplace_back(new Spread(316, 100, 2, 4, Target(TARGET_POS, { 800, 800 })));
    mechanics.emplace_back(new Spread(318, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(318, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(318, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_ONINIT)));
    mechanics.emplace_back(new Spread(318, 250, 0, 2, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_ONINIT)));

    // FINALE 
    song.addCheckpoint(145, 323);



    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 4; j++) {
            mechanics.emplace_back(new Spread(324 + 4 * i, 150, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_FOLLOW)));
            if (i != 7)
                mechanics.emplace_back(new Spread(324 + 4 * (i + 1), 150, 0, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_ONINIT)));
        }
    }



    for (int i = 0; i < 8; i++) {

        float jj = static_cast<float>(i);
        float active = 1;
        if (i == 0)
            active = 4;
        mechanics.emplace_back(new Spread(324 + i, 200, 0, active, Target(TARGET_POS, { 0 + 125 * jj, 100 })));
        mechanics.emplace_back(new Spread(324 + i, 200, 0, active, Target(TARGET_POS, { 0 + 125 * jj, 200 })));
        mechanics.emplace_back(new Spread(324 + i, 200, 0, active, Target(TARGET_POS, { 0 + 125 * jj, 300 })));
        mechanics.emplace_back(new Spread(324 + i, 200, 0, active, Target(TARGET_POS, { 0 + 125 * jj, 400 })));

        mechanics.emplace_back(new Spread(324 + i, 200, 0, active, Target(TARGET_POS, { 1000 - 125 * jj, 600 })));
        mechanics.emplace_back(new Spread(324 + i, 200, 0, active, Target(TARGET_POS, { 1000 - 125 * jj, 700 })));
        mechanics.emplace_back(new Spread(324 + i, 200, 0, active, Target(TARGET_POS, { 1000 - 125 * jj, 800 })));
        mechanics.emplace_back(new Spread(324 + i, 200, 0, active, Target(TARGET_POS, { 1000 - 125 * jj, 900 })));

    }

    for (int i = 0; i < 8; i++) {

        float jj = static_cast<float>(i);
        mechanics.emplace_back(new Spread(332 + i, 200, 0, 0, Target(TARGET_POS, { 1000 - 125 * jj, 100 })));
        mechanics.emplace_back(new Spread(332 + i, 200, 0, 0, Target(TARGET_POS, { 1000 - 125 * jj, 200 })));
        mechanics.emplace_back(new Spread(332 + i, 200, 0, 0, Target(TARGET_POS, { 1000 - 125 * jj, 300 })));
        mechanics.emplace_back(new Spread(332 + i, 200, 0, 0, Target(TARGET_POS, { 1000 - 125 * jj, 400 })));

        mechanics.emplace_back(new Spread(332 + i, 200, 0, 0, Target(TARGET_POS, { 0 + 125 * jj, 600 })));
        mechanics.emplace_back(new Spread(332 + i, 200, 0, 0, Target(TARGET_POS, { 0 + 125 * jj, 700 })));
        mechanics.emplace_back(new Spread(332 + i, 200, 0, 0, Target(TARGET_POS, { 0 + 125 * jj, 800 })));
        mechanics.emplace_back(new Spread(332 + i, 200, 0, 0, Target(TARGET_POS, { 0 + 125 * jj, 900 })));

    }

    for (int i = 0; i < 8; i++) {

        float jj = static_cast<float>(i);
        mechanics.emplace_back(new Spread(340 + i, 200, 0, 0, Target(TARGET_POS, { 0 + 125 * jj, 100 })));
        mechanics.emplace_back(new Spread(340 + i, 200, 0, 0, Target(TARGET_POS, { 0 + 125 * jj, 200 })));
        mechanics.emplace_back(new Spread(340 + i, 200, 0, 0, Target(TARGET_POS, { 0 + 125 * jj, 300 })));
        mechanics.emplace_back(new Spread(340 + i, 200, 0, 0, Target(TARGET_POS, { 0 + 125 * jj, 400 })));

        mechanics.emplace_back(new Spread(340 + i, 200, 0, 0, Target(TARGET_POS, { 1000 - 125 * jj, 600 })));
        mechanics.emplace_back(new Spread(340 + i, 200, 0, 0, Target(TARGET_POS, { 1000 - 125 * jj, 700 })));
        mechanics.emplace_back(new Spread(340 + i, 200, 0, 0, Target(TARGET_POS, { 1000 - 125 * jj, 800 })));
        mechanics.emplace_back(new Spread(340 + i, 200, 0, 0, Target(TARGET_POS, { 1000 - 125 * jj, 900 })));

    }

    for (int i = 0; i < 4; i++) {

        float jj = static_cast<float>(i);
        mechanics.emplace_back(new Spread(348 + i, 200, 0, 0, Target(TARGET_POS, { 1000 - 125 * jj, 100 })));
        mechanics.emplace_back(new Spread(348 + i, 200, 0, 0, Target(TARGET_POS, { 1000 - 125 * jj, 200 })));
        mechanics.emplace_back(new Spread(348 + i, 200, 0, 0, Target(TARGET_POS, { 1000 - 125 * jj, 300 })));
        mechanics.emplace_back(new Spread(348 + i, 200, 0, 0, Target(TARGET_POS, { 1000 - 125 * jj, 400 })));

        mechanics.emplace_back(new Spread(348 + i, 200, 0, 0, Target(TARGET_POS, { 0 + 125 * jj, 600 })));
        mechanics.emplace_back(new Spread(348 + i, 200, 0, 0, Target(TARGET_POS, { 0 + 125 * jj, 700 })));
        mechanics.emplace_back(new Spread(348 + i, 200, 0, 0, Target(TARGET_POS, { 0 + 125 * jj, 800 })));
        mechanics.emplace_back(new Spread(348 + i, 200, 0, 0, Target(TARGET_POS, { 0 + 125 * jj, 900 })));

    }


    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new Tether(356 + 4 * i, Target(TARGET_ENTITY, TARGET_PLAYERS, (i + 1) % 2), Target(TARGET_POS, { 200, 800 }), 200, 4, true, false));
        mechanics.emplace_back(new Tether(356 + 4 * i, Target(TARGET_ENTITY, TARGET_PLAYERS, (i + 1) % 2 + 2), Target(TARGET_POS, { 800, 200 }), 200, 4, true, false));
        mechanics.emplace_back(new Cone(356 + 4 * i, 120, 2500, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, i % 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Cone(356 + 4 * i, 120, 2500, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, i % 2 + 2, TARGET_FOLLOW)));

        mechanics.emplace_back(new Spread(356 + 4 * i, 150, 0, 1, Target(TARGET_POS, { 100, 700 })));
        mechanics.emplace_back(new Spread(357 + 4 * i, 150, 0, 1, Target(TARGET_POS, { 300, 700 })));
        mechanics.emplace_back(new Spread(358 + 4 * i, 150, 0, 1, Target(TARGET_POS, { 300, 900 })));
        mechanics.emplace_back(new Spread(359 + 4 * i, 150, 0, 1, Target(TARGET_POS, { 100, 900 })));

        mechanics.emplace_back(new Spread(356 + 4 * i, 150, 0, 1, Target(TARGET_POS, { 900, 300 })));
        mechanics.emplace_back(new Spread(357 + 4 * i, 150, 0, 1, Target(TARGET_POS, { 900, 100 })));
        mechanics.emplace_back(new Spread(358 + 4 * i, 150, 0, 1, Target(TARGET_POS, { 700, 100 })));
        mechanics.emplace_back(new Spread(359 + 4 * i, 150, 0, 1, Target(TARGET_POS, { 700, 300 })));
    }

    mechanics.emplace_back(new Spread(388, 300, 4, 4, Target(TARGET_POS, { 500, 500 })));

    mechanics.emplace_back(new EndMap(390));
}

void intoYou(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em)
{
    song.addCheckpoint(0, 0);

    em.initRandomSequence(4);

    mechanics.emplace_back(new ApplyDebuff(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_ROOT, 8));
    mechanics.emplace_back(new ApplyDebuff(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_CRITICAL, 8));
    //mechanics.emplace_back(new ApplyDebuff(2, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_CRITICAL, 8));
    //mechanics.emplace_back(new ApplyDebuff(4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_CRITICAL, 8));
    mechanics.emplace_back(new ApplyDebuff(16, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_CRITICAL, 32));

    mechanics.emplace_back(new ApplyDebuff(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_ROOT, 8));
    mechanics.emplace_back(new ApplyDebuff(0, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_CRITICAL, 8));

    mechanics.emplace_back(new TetherIndicator(0, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 16));

    mechanics.emplace_back(new TextIndicator(16, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, {0, 0}), 4, "1"));
    mechanics.emplace_back(new TextIndicator(16, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, {0, 1}), 4, "2"));
    mechanics.emplace_back(new TextIndicator(16, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, {0, 2}), 4, "3"));
    mechanics.emplace_back(new TextIndicator(16, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, {0, 3}), 4, "4"));

    //mechanics.emplace_back(new Spread(24, 100, 1, 4, Target(TARGET_POS, { 500, 500 }), DEBUFF_CRITICAL, 4));
    //mechanics.emplace_back(new Cone(24, 30, 2000, 2, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW), DEBUFF_CRITICAL, 4));
    //mechanics.emplace_back(new Donut(24, 300, 500, 1, 4, Target(TARGET_POS, { 500, 500 }), DEBUFF_CRITICAL, 4));

    mechanics.emplace_back(new Cone(24, 30, 2000, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 0, 0 }, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(28, 30, 2000, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 0, 1 }, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(32, 30, 2000, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 0, 2 }, TARGET_FOLLOW)));
    mechanics.emplace_back(new Cone(36, 30, 2000, 1, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 0, 3 }, TARGET_FOLLOW)));
    
}

void itte(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em)
{
    // Intro

    song.addCheckpoint(0, 0);

    for (int n = 0; n < 4; n++) {
        for (int ii = 0; ii < 4; ii++) {
            float i = static_cast<float>(ii);
            mechanics.emplace_back(new Cone(8 + 16 * n, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * 2 * i), 500 + 300 * std::sin(PI / 4 * 2 * i) })));
            mechanics.emplace_back(new Cone(8 + 8 + 16 * n, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * (2 * i + 1)), 500 + 300 * std::sin(PI / 4 * (2 * i + 1)) })));

        }
    }

    // Couplet 1

    song.addCheckpoint(19, 71.9);


    for (int n = 0; n < 4; n++) {
        mechanics.emplace_back(new Tether(72 + 16 * n, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 100, 8, true, true));
        mechanics.emplace_back(new Tether(72 + 16 * n, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 100, 8, true, true));

        mechanics.emplace_back(new Tether(72 + 8 + 16 * n, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 400, 8, false, true));
        mechanics.emplace_back(new Tether(72 + 8 + 16 * n, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 400, 8, false, true));


        for (int ii = 0; ii < 4; ii++) {
            float i = static_cast<float>(ii);
            mechanics.emplace_back(new Cone(72 + 16 * n, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * 2 * i), 500 + 300 * std::sin(PI / 4 * 2 * i) })));
            mechanics.emplace_back(new Cone(72 + 8 + 16 * n, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * (2 * i + 1)), 500 + 300 * std::sin(PI / 4 * (2 * i + 1)) })));
        }
    }

    // Couplet 2

    song.addCheckpoint(40, 135.9);

    for (int n = 0; n < 6; n++) {
        mechanics.emplace_back(new Spread(136 + 8 * n, 200, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(136 + 8 * n, 200, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(136 + 8 * n, 200, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(136 + 8 * n, 200, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    }

    for (int n = 0; n < 3; n++) {
        mechanics.emplace_back(new Spread(136 + 4 + 16 * n, 200, 2, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(136 + 4 + 16 * n, 200, 2, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));

        mechanics.emplace_back(new Spread(136 + 12 + 16 * n, 200, 2, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(136 + 12 + 16 * n, 200, 2, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    }

    for (int n = 0; n < 3; n++) {
        for (int ii = 0; ii < 4; ii++) {
            float i = static_cast<float>(ii);
            mechanics.emplace_back(new Cone(136 + 16 * n, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * 2 * i), 500 + 300 * std::sin(PI / 4 * 2 * i) })));
            mechanics.emplace_back(new Cone(136 + 8 + 16 * n, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * (2 * i + 1)), 500 + 300 * std::sin(PI / 4 * (2 * i + 1)) })));
        }
    }


    // Refrain

    song.addCheckpoint(56, 183.9);

    for (int n = 0; n < 3; n++) {
        mechanics.emplace_back(new Spread(184 + 8 + 16 * n, 400, 0, 8, Target(TARGET_POS, { 500, 500 })));
        mechanics.emplace_back(new Donut(184 + 12 + 16 * n, 400, 1500, 0, 8, Target(TARGET_POS, { 500, 500 })));

        for (int ii = 0; ii < 4; ii++) {
            float i = static_cast<float>(ii);
            mechanics.emplace_back(new Cone(184 + 16 * n, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * 2 * i), 500 + 300 * std::sin(PI / 4 * 2 * i) })));
            mechanics.emplace_back(new Cone(184 + 4 + 16 * n, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * (2 * i + 1)), 500 + 300 * std::sin(PI / 4 * (2 * i + 1)) })));
        }
    }

    for (int n = 0; n < 2; n++) {
        for (int ii = 0; ii < 4; ii++) {
            float i = static_cast<float>(ii);
            mechanics.emplace_back(new Cone(248 + 8 * n, 45, 2000, 0, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * 2 * i), 500 + 300 * std::sin(PI / 4 * 2 * i) })));
            if (n == 0)
                mechanics.emplace_back(new Cone(248 + 4 + 8 * n, 45, 2000, 0, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * (2 * i + 1)), 500 + 300 * std::sin(PI / 4 * (2 * i + 1)) })));
        }
    }

    //mechanics.emplace_back(new Spread(224, 300, 4, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));


    mechanics.emplace_back(new Spread(230, 400, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(231, 400, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(234, 400, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(235, 400, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(238, 400, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(239, 400, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));


    mechanics.emplace_back(new Spread(246, 400, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(247, 400, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(250, 400, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(251, 400, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(254, 400, 2, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(255, 400, 2, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));



    //Intro
    song.addCheckpoint(81, 256);


    for (int n = 0; n < 6; n++) {
        mechanics.emplace_back(new Spread(272 + 8 * n, 200, 0, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_ONINIT)));
        mechanics.emplace_back(new Spread(272 + 8 * n, 200, 0, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_ONINIT)));
        mechanics.emplace_back(new Spread(272 + 8 * n, 200, 0, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_ONINIT)));
        mechanics.emplace_back(new Spread(272 + 8 * n, 200, 0, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_ONINIT)));
    }

    for (int n = 0; n < 3; n++) {
        for (int ii = 0; ii < 4; ii++) {
            float i = static_cast<float>(ii);
            mechanics.emplace_back(new Cone(272 + 16 * n, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * 2 * i), 500 + 300 * std::sin(PI / 4 * 2 * i) })));
            mechanics.emplace_back(new Cone(272 + 8 + 16 * n, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * (2 * i + 1)), 500 + 300 * std::sin(PI / 4 * (2 * i + 1)) })));

        }
    }

    //Couplet 1
    song.addCheckpoint(102, 319);


    mechanics.emplace_back(new Spread(320, 300, 4, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(320 + 16, 300, 4, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(320 + 16 * 2, 300, 4, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(320 + 16 * 3, 300, 4, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));


    mechanics.emplace_back(new Spread(320 + 8, 300, 2, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(320 + 8 + 16, 300, 2, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(320 + 8 + 16 * 2, 300, 2, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(320 + 8 + 16 * 3, 300, 2, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(320 + 8, 300, 2, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(320 + 8 + 16, 300, 2, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(320 + 8 + 16 * 2, 300, 2, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(320 + 8 + 16 * 3, 300, 2, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));


    for (int n = 0; n < 4; n++) {
        mechanics.emplace_back(new Tether(320 + 16 * n, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 100, 8, true, true));
        mechanics.emplace_back(new Tether(320 + 16 * n, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 100, 8, true, true));
        mechanics.emplace_back(new Spread(320 + 8 + 16 * n, 400, 0, 8, Target(TARGET_POS, { 500, 500 })));

        mechanics.emplace_back(new Tether(320 + 8 + 16 * n, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 400, 8, false, true));
        mechanics.emplace_back(new Tether(320 + 8 + 16 * n, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 400, 8, false, true));
        mechanics.emplace_back(new Donut(320 + 16 * n, 400, 1500, 0, 8, Target(TARGET_POS, { 500, 500 })));

        for (int ii = 0; ii < 4; ii++) {
            float i = static_cast<float>(ii);
            mechanics.emplace_back(new Cone(320 + 16 * n, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * 2 * i), 500 + 300 * std::sin(PI / 4 * 2 * i) })));
            mechanics.emplace_back(new Cone(320 + 8 + 16 * n, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * (2 * i + 1)), 500 + 300 * std::sin(PI / 4 * (2 * i + 1)) })));
        }
    }

    mechanics.emplace_back(new Spread(382, 400, 2, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(383, 400, 2, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));


    // Solo
    song.addCheckpoint(124, 384);


    mechanics.emplace_back(new MoveEntity(386, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500, 500 }), 1000, true));

    for (int ii = 0; ii < 8; ii++) {
        float i = static_cast<float>(ii);
        if (i == 7)
            mechanics.emplace_back(new Cone(392, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
        else
            mechanics.emplace_back(new Cone(400, 45, 2000, 0, 16, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
    }


    mechanics.emplace_back(new Spread(416, 300, 2, 8, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(416, 300, 2, 8, Target(TARGET_FURTHEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW)));

    for (int ii = 0; ii < 8; ii++) {
        float i = static_cast<float>(ii);
        if (i == 1)
            mechanics.emplace_back(new Cone(408, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
        else
            mechanics.emplace_back(new Cone(416, 45, 2000, 0, 16, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
    }

    mechanics.emplace_back(new Tether(432, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), Target(TARGET_FURTHEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), 400, 8, false, true));
    mechanics.emplace_back(new Spread(432, 300, 3, 8, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW)));


    for (int ii = 0; ii < 8; ii++) {
        float i = static_cast<float>(ii);
        if (i == 0 || i == 4)
            mechanics.emplace_back(new Cone(424, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
        else
            mechanics.emplace_back(new Cone(432, 45, 2000, 0, 16, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
    }

    mechanics.emplace_back(new Spread(448, 300, 2, 8, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(448, 500, 1, 8, Target(TARGET_FURTHEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(448, 500, 1, 8, Target(TARGET_FURTHEST, TARGET_PLAYERS, 1, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW)));


    for (int ii = 0; ii < 8; ii++) {
        float i = static_cast<float>(ii);
        if (i == 5 || i == 0 || i == 2)
            mechanics.emplace_back(new Cone(440, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
        else
            mechanics.emplace_back(new Cone(448, 45, 2000, 0, 16, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
    }

    // Couplet 1

    song.addCheckpoint(145, 480);

    int dodge[4] = { 6, 3, 2, 7 };

    for (int n = 0; n < 4; n++) {
        for (int ii = 0; ii < 8; ii++) {
            float i = static_cast<float>(ii);
            if (ii != dodge[n])
                mechanics.emplace_back(new Cone(480 + 8 * n, 45, 2000, 0, 0, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
            else {
                float d = dodge[n] % 2 == 0 ? 500 : 707.1048f;
                mechanics.emplace_back(new Cone(480 + 8 * n, 45, 2000, 0, 8, Target(TARGET_POS, { 500 + d * std::cos(PI / 4 * i), 500 + d * std::sin(PI / 4 * i) }), Target(TARGET_POS, { 500, 500 })));
            }
        }
    }


    // Couplet 2

    song.addCheckpoint(167, 512);

    //int player[4] = {6, 3, 2, 7};

    for (int n = 0; n < 4; n++) {
        mechanics.emplace_back(new Spread(512 + 16 * n, 300, 3, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, (n + 1) % 4, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(512 + 16 * n, 700, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, n, TARGET_FOLLOW)));

        mechanics.emplace_back(new Spread(512 + 4 + 16 * n, 200, 0, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, n, TARGET_ONINIT)));
        mechanics.emplace_back(new Spread(512 + 8 + 16 * n, 200, 0, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, n, TARGET_ONINIT)));

        mechanics.emplace_back(new MoveEntity(512 + 16 * n, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, n), 100, true));
        mechanics.emplace_back(new Spread(512 + 8 + 16 * n, 200, 0, 4, Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW)));

        for (int i = 0; i < 4; i++) {
            if (i != n)
                mechanics.emplace_back(new Spread(512 + 8 + 16 * n, 200, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, i, TARGET_FOLLOW)));
        }
    }

    for (int n = 0; n < 5; n++) {
        for (int ii = 0; ii < 4; ii++) {
            float i = static_cast<float>(ii);
            mechanics.emplace_back(new Cone(512 + 16 * n, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * 2 * i), 500 + 300 * std::sin(PI / 4 * 2 * i) })));
            if (n != 4)
                mechanics.emplace_back(new Cone(512 + 8 + 16 * n, 45, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * (2 * i + 1)), 500 + 300 * std::sin(PI / 4 * (2 * i + 1)) })));
        }
    }


    // Refrain

    song.addCheckpoint(190, 592);

    mechanics.emplace_back(new Tether(652, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), Target(TARGET_ENTITY, TARGET_PLAYERS, 1), 300, 64, false, true));
    mechanics.emplace_back(new Tether(652, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), Target(TARGET_ENTITY, TARGET_PLAYERS, 2), 300, 64, false, true));
    mechanics.emplace_back(new Tether(652, Target(TARGET_ENTITY, TARGET_PLAYERS, 2), Target(TARGET_ENTITY, TARGET_PLAYERS, 3), 300, 64, false, true));
    mechanics.emplace_back(new Tether(652, Target(TARGET_ENTITY, TARGET_PLAYERS, 3), Target(TARGET_ENTITY, TARGET_PLAYERS, 0), 300, 64, false, true));

    mechanics.emplace_back(new Spread(596, 150, 1, 8, Target(TARGET_POS, { 200,200 })));
    mechanics.emplace_back(new Spread(596, 150, 1, 8, Target(TARGET_POS, { 800,200 })));
    mechanics.emplace_back(new Spread(596, 150, 1, 8, Target(TARGET_POS, { 200,800 })));
    mechanics.emplace_back(new Spread(596, 150, 1, 8, Target(TARGET_POS, { 800,800 })));

    mechanics.emplace_back(new Spread(644, 400, 0, 8, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Donut(636, 400, 1500, 0, 8, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Donut(652, 400, 1500, 0, 8, Target(TARGET_POS, { 500, 500 })));


    for (int n = 0; n < 2; n++) {
        for (int ii = 0; ii < 24; ii++) {
            float i = static_cast<float>(ii);
            float active = n == 0 && i == 0 ? 8 : 4;
            mechanics.emplace_back(new Cone(604 + i + 24 * n, 15, 2000, 0, active, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 12 * i), 500 + 300 * std::sin(PI / 12 * i) })));
            mechanics.emplace_back(new Cone(604 + i + 24 * n, 15, 2000, 0, active, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 12 * (i + 6)), 500 + 300 * std::sin(PI / 12 * (i + 6)) })));
            mechanics.emplace_back(new Cone(604 + i + 24 * n, 15, 2000, 0, active, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 12 * (i + 12)), 500 + 300 * std::sin(PI / 12 * (i + 12)) })));
            mechanics.emplace_back(new Cone(604 + i + 24 * n, 15, 2000, 0, active, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 12 * (i + 18)), 500 + 300 * std::sin(PI / 12 * (i + 18)) })));
        }
    }

    // MOTTO SPAM

    for (int i = 0; i < 7; i++) {
        mechanics.emplace_back(new Spread(658 + 4 * i, 300, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2 * (i % 2) + 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(659 + 4 * i, 300, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2 * (i % 2) + 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(660 + 4 * i, 200, 2, 4, Target(TARGET_POS, { 500,500 })));
    }

    mechanics.emplace_back(new Spread(688, 300, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(688, 300, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(688, 300, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(688, 300, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));

    for (int i = 0; i < 4; i++) {
        mechanics.emplace_back(new Spread(692 + 4 * i, 300, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2 * (i % 2) + 0, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(693 + 4 * i, 300, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2 * (i % 2) + 1, TARGET_FOLLOW)));
        mechanics.emplace_back(new Spread(694 + 4 * i, 200, 2, 4, Target(TARGET_POS, { 500,500 })));
    }

    for (int n = 0; n < 5; n++) {
        for (int ii = 0; ii < 4; ii++) {
            float i = static_cast<float>(ii);
            mechanics.emplace_back(new Cone(692 + 4 * n, 45, 2000, 0, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * (2 * i + n % 2)), 500 + 300 * std::sin(PI / 4 * (2 * i + n % 2)) })));
        }
    }

    /*mechanics.emplace_back(new Spread(692 + 4*4, 300, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(692 + 4*4, 300, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 1, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(692 + 4*4, 300, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 2, TARGET_FOLLOW)));
    mechanics.emplace_back(new Spread(692 + 4*4, 300, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, 3, TARGET_FOLLOW)));

*/
    int dodge1[4] = { 1,3 };
    int bait[4] = { 3, 6 };

    for (int n = 0; n < 2; n++) {
        for (int ii = 0; ii < 8; ii++) {
            float i = static_cast<float>(ii);
            if (ii != dodge1[n])
                mechanics.emplace_back(new Cone(712 + 4 * n, 45, 2000, 0, 4, Target(TARGET_POS, { 500, 500 }), Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
        }
    }

    mechanics.emplace_back(new EndMap(718));

}

void furachi(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em)
{
    // COUPLET 1
    song.addCheckpoint(0, 0);

    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new Cone(12, 22.5, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }),
            Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
    }

    mechanics.emplace_back(new Spread(20, 225, 0, 8, Target(TARGET_POS, { 150, 150 })));
    mechanics.emplace_back(new Spread(20, 225, 0, 8, Target(TARGET_POS, { 500, 150 })));
    mechanics.emplace_back(new Spread(20, 225, 0, 8, Target(TARGET_POS, { 850, 150 })));
    mechanics.emplace_back(new Spread(20, 225, 0, 8, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(20, 225, 0, 8, Target(TARGET_POS, { 150, 850 })));
    mechanics.emplace_back(new Spread(20, 225, 0, 8, Target(TARGET_POS, { 500, 850 })));
    mechanics.emplace_back(new Spread(20, 225, 0, 8, Target(TARGET_POS, { 850, 850 })));

    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new Cone(28, 22.5, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }), 
            Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
    }

    mechanics.emplace_back(new Spread(36, 225, 0, 8, Target(TARGET_POS, { 150, 150 })));
    mechanics.emplace_back(new Spread(36, 225, 0, 8, Target(TARGET_POS, { 850, 150 })));
    mechanics.emplace_back(new Spread(36, 225, 0, 8, Target(TARGET_POS, { 150, 500 })));
    mechanics.emplace_back(new Spread(36, 225, 0, 8, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(36, 225, 0, 8, Target(TARGET_POS, { 850, 500 })));
    mechanics.emplace_back(new Spread(36, 225, 0, 8, Target(TARGET_POS, { 150, 850 })));
    mechanics.emplace_back(new Spread(36, 225, 0, 8, Target(TARGET_POS, { 850, 850 })));

    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new Cone(44, 22.5, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }),
            Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
    }


    mechanics.emplace_back(new Spread(52, 225, 0, 8, Target(TARGET_POS, { 150, 150 })));
    mechanics.emplace_back(new Spread(52, 225, 0, 8, Target(TARGET_POS, { 500, 150 })));
    mechanics.emplace_back(new Spread(52, 225, 0, 8, Target(TARGET_POS, { 850, 150 })));
    mechanics.emplace_back(new Spread(52, 225, 0, 8, Target(TARGET_POS, { 150, 500 })));
    mechanics.emplace_back(new Spread(52, 225, 0, 8, Target(TARGET_POS, { 850, 500 })));
    mechanics.emplace_back(new Spread(52, 225, 0, 8, Target(TARGET_POS, { 150, 850 })));
    mechanics.emplace_back(new Spread(52, 225, 0, 8, Target(TARGET_POS, { 500, 850 })));
    mechanics.emplace_back(new Spread(52, 225, 0, 8, Target(TARGET_POS, { 850, 850 })));

    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new Cone(60, 22.5, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }),
            Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
    }

    mechanics.emplace_back(new Spread(68, 225, 0, 8, Target(TARGET_POS, { 150, 150 })));
    mechanics.emplace_back(new Spread(68, 225, 0, 8, Target(TARGET_POS, { 500, 150 })));
    mechanics.emplace_back(new Spread(68, 225, 0, 8, Target(TARGET_POS, { 850, 150 })));
    mechanics.emplace_back(new Spread(68, 225, 0, 8, Target(TARGET_POS, { 150, 500 })));
    mechanics.emplace_back(new Spread(68, 225, 0, 8, Target(TARGET_POS, { 850, 500 })));
    mechanics.emplace_back(new Spread(68, 225, 0, 8, Target(TARGET_POS, { 150, 850 })));
    mechanics.emplace_back(new Spread(68, 225, 0, 8, Target(TARGET_POS, { 500, 850 })));
    mechanics.emplace_back(new Spread(68, 225, 0, 8, Target(TARGET_POS, { 850, 850 })));


    // REFRAIN
    em.initRandomSequence(8);

    song.addCheckpoint(23, 68.1);

    mechanics.emplace_back(new TextIndicator(70, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 0, 0 }), 8, "1"));
    mechanics.emplace_back(new TextIndicator(70, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 0, 1 }), 8, "2"));
    mechanics.emplace_back(new TextIndicator(70, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 0, 2 }), 8, "3"));
    mechanics.emplace_back(new TextIndicator(70, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 0, 3 }), 8, "4"));
    mechanics.emplace_back(new TextIndicator(70, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 0, 4 }), 8, "5"));
    mechanics.emplace_back(new TextIndicator(70, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 0, 5 }), 8, "6"));
    mechanics.emplace_back(new TextIndicator(70, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 0, 6 }), 8, "7"));
    mechanics.emplace_back(new TextIndicator(70, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 0, 7 }), 8, "8"));


    mechanics.emplace_back(new ActivateTotem(72, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xFFFFFFFF, 15));
    mechanics.emplace_back(new MoveEntity(72, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 850, 500 }), 100, true));


    for (int i = 0; i < 8; i++) {
        for(int j = 1; j < 8; j++)
            mechanics.emplace_back(new Spread(76 + 4*i, 100, 1, i == 0 ? 4 + (8-j)/2.f:4,
                Target(TARGET_POS, { 500 + 350 * std::cos(PI / 4 * j), 500 + 350 * std::sin(PI / 4 * j) })));

        mechanics.emplace_back(new Cone(76 + 4 * i, 90, 2500, 1, 0, Target(TARGET_POS, { 850, 500 }),
            Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 0, (float)i }, TARGET_FOLLOW)));

    }

    mechanics.emplace_back(new ActivateTotem(104, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));

    mechanics.emplace_back(new Spread(108, 225, 4, 4, Target(TARGET_POS, { 200, 500 })));
    mechanics.emplace_back(new Spread(108, 225, 4, 4, Target(TARGET_POS, { 800, 500 })));
    for (int j = 0; j < 8; j++)
        mechanics.emplace_back(new Spread(112, 125, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(116, 225, 4, 4, Target(TARGET_POS, { 500, 200 })));
    mechanics.emplace_back(new Spread(116, 225, 4, 4, Target(TARGET_POS, { 500, 800 })));
    for (int j = 0; j < 8; j++)
        mechanics.emplace_back(new Spread(120, 125, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(124, 225, 4, 4, Target(TARGET_POS, { 200, 500 })));
    mechanics.emplace_back(new Spread(124, 225, 4, 4, Target(TARGET_POS, { 800, 500 })));


    // COUPLET 2

    song.addCheckpoint(42, 124.1);

    for (int j = 0; j < 8; j++)
        mechanics.emplace_back(new Spread(132, 125, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_FOLLOW)));
    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new Cone(132, 22.5, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }),
            Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
    }

    mechanics.emplace_back(new Spread(140, 225, 4, 8, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 0, 500 }), TARGET_FOLLOW), DEBUFF_CRITICAL, 2));
    mechanics.emplace_back(new Spread(140, 225, 4, 8, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 1000, 500 }), TARGET_FOLLOW), DEBUFF_CRITICAL, 2));

    mechanics.emplace_back(new Spread(140, 225, 0, 8, Target(TARGET_POS, { 150, 150 })));
    mechanics.emplace_back(new Spread(140, 225, 0, 8, Target(TARGET_POS, { 500, 150 })));
    mechanics.emplace_back(new Spread(140, 225, 0, 8, Target(TARGET_POS, { 850, 150 })));
    mechanics.emplace_back(new Spread(140, 225, 0, 8, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(140, 225, 0, 8, Target(TARGET_POS, { 150, 850 })));
    mechanics.emplace_back(new Spread(140, 225, 0, 8, Target(TARGET_POS, { 500, 850 })));
    mechanics.emplace_back(new Spread(140, 225, 0, 8, Target(TARGET_POS, { 850, 850 })));

    for (int j = 0; j < 8; j++)
        mechanics.emplace_back(new Spread(148, 125, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_FOLLOW)));
    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new Cone(148, 22.5, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }),
            Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
    }

    mechanics.emplace_back(new Spread(156, 225, 4, 8, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 500, 1000 }), TARGET_FOLLOW), DEBUFF_CRITICAL, 2));
    mechanics.emplace_back(new Spread(156, 225, 4, 8, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 500, 0 }), TARGET_FOLLOW), DEBUFF_CRITICAL, 2));

    mechanics.emplace_back(new Spread(156, 225, 0, 8, Target(TARGET_POS, { 150, 150 })));
    mechanics.emplace_back(new Spread(156, 225, 0, 8, Target(TARGET_POS, { 850, 150 })));
    mechanics.emplace_back(new Spread(156, 225, 0, 8, Target(TARGET_POS, { 150, 500 })));
    mechanics.emplace_back(new Spread(156, 225, 0, 8, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(156, 225, 0, 8, Target(TARGET_POS, { 850, 500 })));
    mechanics.emplace_back(new Spread(156, 225, 0, 8, Target(TARGET_POS, { 150, 850 })));
    mechanics.emplace_back(new Spread(156, 225, 0, 8, Target(TARGET_POS, { 850, 850 })));

    for (int j = 0; j < 8; j++)
        mechanics.emplace_back(new Spread(164, 125, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_FOLLOW)));
    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new Cone(164, 22.5, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }),
            Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
    }

    mechanics.emplace_back(new Spread(172, 125, 2, 8, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 0, 0 }), TARGET_FOLLOW), DEBUFF_CRITICAL, 2));
    mechanics.emplace_back(new Spread(172, 125, 2, 8, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 1000, 0 }), TARGET_FOLLOW), DEBUFF_CRITICAL, 2));
    mechanics.emplace_back(new Spread(172, 125, 2, 8, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 0, 1000 }), TARGET_FOLLOW), DEBUFF_CRITICAL, 2));
    mechanics.emplace_back(new Spread(172, 125, 2, 8, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 1000, 1000 }), TARGET_FOLLOW), DEBUFF_CRITICAL, 2));


    mechanics.emplace_back(new Spread(172, 225, 0, 8, Target(TARGET_POS, { 150, 150 })));
    mechanics.emplace_back(new Spread(172, 225, 0, 8, Target(TARGET_POS, { 500, 150 })));
    mechanics.emplace_back(new Spread(172, 225, 0, 8, Target(TARGET_POS, { 850, 150 })));
    mechanics.emplace_back(new Spread(172, 225, 0, 8, Target(TARGET_POS, { 150, 500 })));
    mechanics.emplace_back(new Spread(172, 225, 0, 8, Target(TARGET_POS, { 850, 500 })));
    mechanics.emplace_back(new Spread(172, 225, 0, 8, Target(TARGET_POS, { 150, 850 })));
    mechanics.emplace_back(new Spread(172, 225, 0, 8, Target(TARGET_POS, { 500, 850 })));
    mechanics.emplace_back(new Spread(172, 225, 0, 8, Target(TARGET_POS, { 850, 850 })));

    for (int j = 0; j < 8; j++)
        mechanics.emplace_back(new Spread(180, 125, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_FOLLOW)));
    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new Cone(180, 22.5, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }),
            Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
    }

    // REFRAIN 2

    em.initRandomSequence(8);

    song.addCheckpoint(65, 180.1);

    mechanics.emplace_back(new TextIndicator(182, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 1, 0 }), 8, "1"));
    mechanics.emplace_back(new TextIndicator(182, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 1, 1 }), 8, "2"));
    mechanics.emplace_back(new TextIndicator(182, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 1, 2 }), 8, "3"));
    mechanics.emplace_back(new TextIndicator(182, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 1, 3 }), 8, "4"));
    mechanics.emplace_back(new TextIndicator(182, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 1, 4 }), 8, "5"));
    mechanics.emplace_back(new TextIndicator(182, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 1, 5 }), 8, "6"));
    mechanics.emplace_back(new TextIndicator(182, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 1, 6 }), 8, "7"));
    mechanics.emplace_back(new TextIndicator(182, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 1, 7 }), 8, "8"));

    mechanics.emplace_back(new ActivateTotem(184, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xFFFFFFFF, 15));
    mechanics.emplace_back(new MoveEntity(184, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 850, 850 }), 100, true));

    mechanics.emplace_back(new ActivateTotem(184, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, 0x4848f4ff, 15));
    mechanics.emplace_back(new MoveEntity(184, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 500, 500 }), 100, true));

    mechanics.emplace_back(new ActivateTotem(184, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), true, 0xda81feff, 15));
    mechanics.emplace_back(new MoveEntity(184, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), Target(TARGET_POS, { 150, 150 }), 100, true));

    mechanics.emplace_back(new TetherIndicator(184, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW), TARGET_FOLLOW), 32));

    mechanics.emplace_back(new TetherIndicator(184, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        Target(TARGET_CLOSEST, TARGET_PLAYERS, 1, new Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW), TARGET_FOLLOW), 32));

    mechanics.emplace_back(new TetherIndicator(184, Target(TARGET_ENTITY, TARGET_TOTEMS, 2),
        Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW), TARGET_FOLLOW), 32));

    for (int i = 0; i < 8; i++) {

        mechanics.emplace_back(new Cone(188 + 4 * i, 30, 2500, 1, 0, Target(TARGET_POS, { 500, 500 }),
            Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW), TARGET_FOLLOW), DEBUFF_MASK1, 3.5*4));
        mechanics.emplace_back(new Cone(188 + 4 * i, 30, 2500, 1, 0, Target(TARGET_POS, { 500, 500 }),
            Target(TARGET_CLOSEST, TARGET_PLAYERS, 1, new Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW), TARGET_FOLLOW), DEBUFF_MASK1, 3.5 * 4));

        mechanics.emplace_back(new Spread(188 + 4 * i, 350, 1, 0, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 2, TARGET_FOLLOW), TARGET_FOLLOW),
            DEBUFF_MASK2, 30));

        mechanics.emplace_back(new Spread(188 + 4 * i, 175, 2, 4, Target(TARGET_POS, { 700, 300 })));
        mechanics.emplace_back(new Spread(188 + 4 * i, 175, 2, 4, Target(TARGET_POS, { 300, 700 })));

        mechanics.emplace_back(new Cone(188 + 4 * i, 90, 2500, 1, 0, Target(TARGET_POS, { 850, 850 }),
            Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 1, (float)i }, TARGET_FOLLOW)));

    }

    mechanics.emplace_back(new ActivateTotem(216, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));
    mechanics.emplace_back(new ActivateTotem(216, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false));
    mechanics.emplace_back(new ActivateTotem(216, Target(TARGET_ENTITY, TARGET_TOTEMS, 2), false));

    mechanics.emplace_back(new Spread(220, 225, 4, 4, Target(TARGET_POS, { 200, 500 })));
    mechanics.emplace_back(new Spread(220, 225, 4, 4, Target(TARGET_POS, { 800, 500 })));
    for (int j = 0; j < 8; j++)
        mechanics.emplace_back(new Spread(224, 125, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(228, 225, 4, 4, Target(TARGET_POS, { 500, 200 })));
    mechanics.emplace_back(new Spread(228, 225, 4, 4, Target(TARGET_POS, { 500, 800 })));
    for (int j = 0; j < 8; j++)
        mechanics.emplace_back(new Spread(232, 125, 1, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_FOLLOW)));

    mechanics.emplace_back(new Spread(236, 225, 4, 4, Target(TARGET_POS, { 200, 500 })));
    mechanics.emplace_back(new Spread(236, 225, 4, 4, Target(TARGET_POS, { 800, 500 })));


    // COUPLET 3
     
    song.addCheckpoint(85, 236.1);

    for (int j = 0; j < 8; j++)
        mechanics.emplace_back(new Spread(244, 125, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_FOLLOW)));
    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new Cone(244, 22.5, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }),
            Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
    }

    mechanics.emplace_back(new Spread(252, 225, 4, 8, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 0, 0 }), TARGET_FOLLOW), DEBUFF_CRITICAL, 2));
    mechanics.emplace_back(new Spread(252, 225, 4, 8, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 1000, 1000 }), TARGET_FOLLOW), DEBUFF_CRITICAL, 2));

    mechanics.emplace_back(new Spread(252, 225, 0, 8, Target(TARGET_POS, { 500, 150 })));
    mechanics.emplace_back(new Spread(252, 225, 0, 8, Target(TARGET_POS, { 850, 150 })));
    mechanics.emplace_back(new Spread(252, 225, 0, 8, Target(TARGET_POS, { 150, 500 })));
    mechanics.emplace_back(new Spread(252, 225, 0, 8, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(252, 225, 0, 8, Target(TARGET_POS, { 850, 500 })));
    mechanics.emplace_back(new Spread(252, 225, 0, 8, Target(TARGET_POS, { 150, 850 })));
    mechanics.emplace_back(new Spread(252, 225, 0, 8, Target(TARGET_POS, { 500, 850 })));

    for (int j = 0; j < 8; j++)
        mechanics.emplace_back(new Spread(260, 125, 1, 8, Target(TARGET_ENTITY, TARGET_PLAYERS, j, TARGET_FOLLOW)));
    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new Cone(260, 22.5, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }),
            Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
    }

    mechanics.emplace_back(new Spread(268, 225, 4, 8, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 0, 1000 }), TARGET_FOLLOW), DEBUFF_CRITICAL, 2));
    mechanics.emplace_back(new Spread(268, 225, 4, 8, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_POS, { 1000, 0 }), TARGET_FOLLOW), DEBUFF_CRITICAL, 2));

    mechanics.emplace_back(new Spread(268, 225, 0, 8, Target(TARGET_POS, { 150, 150 })));
    mechanics.emplace_back(new Spread(268, 225, 0, 8, Target(TARGET_POS, { 500, 150 })));
    mechanics.emplace_back(new Spread(268, 225, 0, 8, Target(TARGET_POS, { 150, 500 })));
    mechanics.emplace_back(new Spread(268, 225, 0, 8, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(268, 225, 0, 8, Target(TARGET_POS, { 850, 500 })));
    mechanics.emplace_back(new Spread(268, 225, 0, 8, Target(TARGET_POS, { 500, 850 })));
    mechanics.emplace_back(new Spread(268, 225, 0, 8, Target(TARGET_POS, { 850, 850 })));

    // REFRAIN 3

    song.addCheckpoint(99, 268.1);

    em.initRandomSequence(8);
    em.initRandomSequence(8);

    mechanics.emplace_back(new TextIndicator(272, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 2, 0 }), 8, "1"));
    mechanics.emplace_back(new TextIndicator(272, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 2, 1 }), 8, "2"));
    mechanics.emplace_back(new TextIndicator(272, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 2, 2 }), 8, "3"));
    mechanics.emplace_back(new TextIndicator(272, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 2, 3 }), 8, "4"));
    mechanics.emplace_back(new TextIndicator(272, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 2, 4 }), 8, "1"));
    mechanics.emplace_back(new TextIndicator(272, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 2, 5 }), 8, "2"));
    mechanics.emplace_back(new TextIndicator(272, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 2, 6 }), 8, "3"));
    mechanics.emplace_back(new TextIndicator(272, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 2, 7 }), 8, "4"));

    for(int i = 0; i < 8; i++)
        mechanics.emplace_back(new Spread(286, 225, 0, 4, Target(TARGET_ENTITY, TARGET_PLAYERS, i, TARGET_ONINIT)));

    mechanics.emplace_back(new ActivateTotem(276, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xFFFFFFFF, 15));
    mechanics.emplace_back(new MoveEntity(276, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500, 150 }), 100, true));

    mechanics.emplace_back(new ActivateTotem(276, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), true, 0xda81feff, 15));
    mechanics.emplace_back(new MoveEntity(276, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), Target(TARGET_POS, { 500, 850 }), 100, true));

    mechanics.emplace_back(new TetherIndicator(276, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW), TARGET_FOLLOW), 26));
    mechanics.emplace_back(new TetherIndicator(276, Target(TARGET_ENTITY, TARGET_TOTEMS, 1),
        Target(TARGET_CLOSEST, TARGET_PLAYERS, 1, new Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW), TARGET_FOLLOW), 26));

    for (int i = 0; i < 4; i++) {
        mechanics.emplace_back(new Spread(290 + 4 * i, 250, 1, 0, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW), TARGET_FOLLOW),
            DEBUFF_MASK2, 20));
        mechanics.emplace_back(new Spread(290 + 4 * i, 250, 1, 0, Target(TARGET_CLOSEST, TARGET_PLAYERS, 1, new Target(TARGET_ENTITY, TARGET_TOTEMS, 1, TARGET_FOLLOW), TARGET_FOLLOW),
            DEBUFF_MASK2, 20));

        mechanics.emplace_back(new Spread(290 + 4 * i, 175, 4, 4, Target(TARGET_POS, { 500, 500 })));

        mechanics.emplace_back(new Cone(290 + 4 * i, 90, 2500, 1, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
            Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 2, (float)i }, TARGET_FOLLOW)));

        mechanics.emplace_back(new Cone(290 + 4 * i, 90, 2500, 1, 0, Target(TARGET_ENTITY, TARGET_TOTEMS, 0),
            Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 2, (float)(i + 4) }, TARGET_FOLLOW)));
    }

    mechanics.emplace_back(new TextIndicator(298, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 3, 0 }), 8, "1"));
    mechanics.emplace_back(new TextIndicator(298, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 3, 1 }), 8, "2"));
    mechanics.emplace_back(new TextIndicator(298, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 3, 2 }), 8, "3"));
    mechanics.emplace_back(new TextIndicator(298, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 3, 3 }), 8, "4"));
    mechanics.emplace_back(new TextIndicator(298, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 3, 4 }), 8, "5"));
    mechanics.emplace_back(new TextIndicator(298, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 3, 5 }), 8, "6"));
    mechanics.emplace_back(new TextIndicator(298, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 3, 6 }), 8, "7"));
    mechanics.emplace_back(new TextIndicator(298, Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 3, 7 }), 8, "8"));

    mechanics.emplace_back(new MoveEntity(302, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 850, 500 }), 100, true));
    mechanics.emplace_back(new ActivateTotem(302, Target(TARGET_ENTITY, TARGET_TOTEMS, 1), false));

    for (int i = 0; i < 8; i++) {
        for (int j = 1; j < 8; j++)
            mechanics.emplace_back(new Spread(306 + 4 * i, 100, 1, i == 0 ? 4 + (8 - j) / 2.f : 4,
                Target(TARGET_POS, { 500 + 350 * std::cos(PI / 4 * j), 500 + 350 * std::sin(PI / 4 * j) })));

        mechanics.emplace_back(new Cone(306 + 4 * i, 90, 2500, 1, 0, Target(TARGET_POS, { 850, 500 }),
            Target(TARGET_RANDOMSEQUENCE, TARGET_PLAYERS, { 3, (float)i }, TARGET_FOLLOW)));

    }

    mechanics.emplace_back(new ActivateTotem(334, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));
    

    mechanics.emplace_back(new Spread(346, 225, 0, 8, Target(TARGET_POS, { 150, 150 })));
    mechanics.emplace_back(new Spread(346, 225, 0, 8, Target(TARGET_POS, { 500, 150 })));
    mechanics.emplace_back(new Spread(346, 225, 0, 8, Target(TARGET_POS, { 850, 150 })));
    mechanics.emplace_back(new Spread(346, 225, 0, 8, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(346, 225, 0, 8, Target(TARGET_POS, { 150, 850 })));
    mechanics.emplace_back(new Spread(346, 225, 0, 8, Target(TARGET_POS, { 500, 850 })));
    mechanics.emplace_back(new Spread(346, 225, 0, 8, Target(TARGET_POS, { 850, 850 })));

    for (int i = 0; i < 8; i++) {
        mechanics.emplace_back(new Cone(354, 22.5, 2000, 0, 8, Target(TARGET_POS, { 500, 500 }),
            Target(TARGET_POS, { 500 + 300 * std::cos(PI / 4 * i), 500 + 300 * std::sin(PI / 4 * i) })));
    }

    mechanics.emplace_back(new Spread(362, 225, 0, 8, Target(TARGET_POS, { 150, 150 })));
    mechanics.emplace_back(new Spread(362, 225, 0, 8, Target(TARGET_POS, { 850, 150 })));
    mechanics.emplace_back(new Spread(362, 225, 0, 8, Target(TARGET_POS, { 150, 500 })));
    mechanics.emplace_back(new Spread(362, 225, 0, 8, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(362, 225, 0, 8, Target(TARGET_POS, { 850, 500 })));
    mechanics.emplace_back(new Spread(362, 225, 0, 8, Target(TARGET_POS, { 150, 850 })));
    mechanics.emplace_back(new Spread(362, 225, 0, 8, Target(TARGET_POS, { 850, 850 })));

    mechanics.emplace_back(new Spread(370, 225, 4, 8, Target(TARGET_POS, { 200, 500 })));
    mechanics.emplace_back(new Spread(370, 225, 4, 8, Target(TARGET_POS, { 800, 500 })));

    mechanics.emplace_back(new EndMap(372));
     
    //music.setPlayingOffset(sf::seconds(99));
}

/*void lazySong(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em)
{
    song.addCheckpoint(0, 0);

    mechanics.emplace_back(new Spread( 8, 150, 1, 8, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(16, 150, 1, 8, Target(TARGET_POS, { 200, 200 })));
    mechanics.emplace_back(new Spread(24, 150, 1, 8, Target(TARGET_POS, { 200, 800 })));
    mechanics.emplace_back(new Spread(32, 150, 1, 8, Target(TARGET_POS, { 800, 800 })));


    song.addCheckpoint(24, 33);

    mechanics.emplace_back(new Spread(40, 700, 0, 8, Target(TARGET_POS, { 900, 900 })));
    mechanics.emplace_back(new Spread(48, 700, 0, 8, Target(TARGET_POS, { 100, 100 })));
    mechanics.emplace_back(new Spread(56, 700, 0, 8, Target(TARGET_POS, { 900, 900 })));
    mechanics.emplace_back(new Spread(64, 700, 0, 8, Target(TARGET_POS, { 100, 100 })));

    song.addCheckpoint(46, 65);

    mechanics.emplace_back(new Tether(70, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW), Target(TARGET_POS, { 800, 800 }), 500, 6, false, false));

    song.addCheckpoint(52, 71);

    mechanics.emplace_back(new Spread(76, 150, 1, 8, Target(TARGET_POS, { 800, 800 })));
    mechanics.emplace_back(new Spread(80, 150, 1, 8, Target(TARGET_POS, { 600, 600 })));
    mechanics.emplace_back(new Spread(84, 150, 1, 8, Target(TARGET_POS, { 371, 598 })));
    mechanics.emplace_back(new Spread(88, 150, 1, 8, Target(TARGET_POS, { 187, 346 })));
    mechanics.emplace_back(new Spread(92, 150, 1, 8, Target(TARGET_POS, { 196, 63 })));
    mechanics.emplace_back(new Spread(96, 150, 1, 8, Target(TARGET_POS, { 477, 96 })));
    mechanics.emplace_back(new Spread(100, 150, 1, 8, Target(TARGET_POS, { 714, 250 })));
    mechanics.emplace_back(new Spread(104, 150, 1, 8, Target(TARGET_POS, { 799, 520 })));

    mechanics.emplace_back(new Donut(112, 200, 2000, 0, 8, Target(TARGET_POS, { 200, 800 })));
    mechanics.emplace_back(new Donut(120, 200, 2000, 0, 8, Target(TARGET_POS, { 800, 200 })));

    song.addCheckpoint(85, 124);

    mechanics.emplace_back(new Spread(128, 700, 0, 8, Target(TARGET_POS, { 900, 100 })));
    mechanics.emplace_back(new Spread(128, 700, 0, 8, Target(TARGET_POS, { 900, 900 })));
    mechanics.emplace_back(new Spread(128, 700, 0, 8, Target(TARGET_POS, { 100, 100 })));

    mechanics.emplace_back(new Spread(136, 700, 0, 8, Target(TARGET_POS, { 100, 900})));
    mechanics.emplace_back(new Spread(136, 700, 0, 8, Target(TARGET_POS, { 900, 900 })));
    mechanics.emplace_back(new Spread(136, 700, 0, 8, Target(TARGET_POS, { 100, 100 })));

    mechanics.emplace_back(new Spread(144, 700, 0, 8, Target(TARGET_POS, { 900, 100 })));
    mechanics.emplace_back(new Spread(144, 700, 0, 8, Target(TARGET_POS, { 900, 900 })));
    mechanics.emplace_back(new Spread(144, 700, 0, 8, Target(TARGET_POS, { 100, 100 })));

    mechanics.emplace_back(new Spread(152, 700, 0, 8, Target(TARGET_POS, { 100, 900 })));
    mechanics.emplace_back(new Spread(152, 700, 0, 8, Target(TARGET_POS, { 900, 900 })));
    mechanics.emplace_back(new Spread(152, 700, 0, 8, Target(TARGET_POS, { 100, 100 })));

    mechanics.emplace_back(new Tether(158, Target(TARGET_ENTITY, TARGET_PLAYERS, 0, TARGET_FOLLOW), Target(TARGET_POS, { 900, 100 }), 500, 6, false, false));

    song.addCheckpoint(112, 160);

    mechanics.emplace_back(new Spread(160, 150, 1, 8, Target(TARGET_POS, { 100, 900 })));
    mechanics.emplace_back(new Spread(162, 150, 1, 8, Target(TARGET_POS, { 200, 800 })));
    mechanics.emplace_back(new Spread(164, 150, 1, 8, Target(TARGET_POS, { 230, 661 })));
    mechanics.emplace_back(new Spread(166, 150, 1, 8, Target(TARGET_POS, { 275, 527 })));
    mechanics.emplace_back(new Spread(168, 150, 1, 8, Target(TARGET_POS, { 336, 400 })));
    mechanics.emplace_back(new Spread(170, 150, 1, 8, Target(TARGET_POS, { 293, 265 })));
    mechanics.emplace_back(new Spread(172, 150, 1, 8, Target(TARGET_POS, { 330, 128 })));
    mechanics.emplace_back(new Spread(174, 150, 1, 8, Target(TARGET_POS, { 469, 102 })));
    mechanics.emplace_back(new Spread(176, 150, 1, 8, Target(TARGET_POS, { 598, 161 })));
    mechanics.emplace_back(new Spread(178, 150, 1, 8, Target(TARGET_POS, { 654, 290 })));
    mechanics.emplace_back(new Spread(180, 150, 1, 8, Target(TARGET_POS, { 691, 427 })));
    mechanics.emplace_back(new Spread(182, 150, 1, 8, Target(TARGET_POS, { 670, 566 })));
    mechanics.emplace_back(new Spread(184, 150, 1, 8, Target(TARGET_POS, { 634, 703 })));
    mechanics.emplace_back(new Spread(186, 150, 1, 8, Target(TARGET_POS, { 660, 842 })));
    mechanics.emplace_back(new Spread(188, 150, 1, 8, Target(TARGET_POS, { 772, 930 })));
    mechanics.emplace_back(new Spread(190, 150, 1, 8, Target(TARGET_POS, { 919, 942 })));


    mechanics.emplace_back(new Donut(194, 200, 2000, 0, 4, Target(TARGET_POS, { 200, 800 })));
    mechanics.emplace_back(new Donut(198, 200, 2000, 0, 4, Target(TARGET_POS, { 200, 200 })));
    mechanics.emplace_back(new Donut(202, 200, 2000, 0, 4, Target(TARGET_POS, { 800, 200 })));
    mechanics.emplace_back(new Donut(206, 200, 2000, 0, 4, Target(TARGET_POS, { 800, 800 })));

    mechanics.emplace_back(new Donut(210, 200, 2000, 0, 4, Target(TARGET_POS, { 200, 800 })));
    mechanics.emplace_back(new Donut(214, 200, 2000, 0, 4, Target(TARGET_POS, { 200, 200 })));
    mechanics.emplace_back(new Donut(218, 200, 2000, 0, 4, Target(TARGET_POS, { 800, 200 })));
    mechanics.emplace_back(new Donut(222, 200, 2000, 0, 4, Target(TARGET_POS, { 800, 800 })));

    song.addCheckpoint(155, 224);

    mechanics.emplace_back(new Spread(224, 150, 1, 8, Target(TARGET_POS, { 800, 800 })));
    mechanics.emplace_back(new Spread(226, 150, 0, 8, Target(TARGET_POS, { 847, 612 })));
    mechanics.emplace_back(new Spread(228, 150, 1, 8, Target(TARGET_POS, { 889, 423 })));
    mechanics.emplace_back(new Spread(230, 150, 0, 8, Target(TARGET_POS, { 893, 230 })));
    mechanics.emplace_back(new Spread(232, 150, 1, 8, Target(TARGET_POS, { 715, 153 })));
    mechanics.emplace_back(new Spread(234, 150, 0, 8, Target(TARGET_POS, { 524, 122 })));
    mechanics.emplace_back(new Spread(236, 150, 1, 8, Target(TARGET_POS, { 361, 225 })));
    mechanics.emplace_back(new Spread(238, 150, 0, 8, Target(TARGET_POS, { 179, 293 })));
    mechanics.emplace_back(new Spread(240, 150, 1, 8, Target(TARGET_POS, { 120, 476 })));
    mechanics.emplace_back(new Spread(242, 150, 0, 8, Target(TARGET_POS, { 169, 664 })));
    mechanics.emplace_back(new Spread(244, 150, 1, 8, Target(TARGET_POS, { 281, 822 })));
    mechanics.emplace_back(new Spread(246, 150, 0, 8, Target(TARGET_POS, { 428, 695 })));
    mechanics.emplace_back(new Spread(248, 150, 1, 8, Target(TARGET_POS, { 572, 566 })));
    mechanics.emplace_back(new Spread(250, 150, 0, 8, Target(TARGET_POS, { 714, 435 })));
    mechanics.emplace_back(new Spread(252, 150, 1, 8, Target(TARGET_POS, { 854, 301 })));
    mechanics.emplace_back(new Spread(254, 150, 0, 8, Target(TARGET_POS, { 894, 112 })));

    mechanics.emplace_back(new Spread(258, 150, 1, 8, Target(TARGET_POS, { 800, 200 })));
    mechanics.emplace_back(new Spread(258, 424, 0, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(264, 150, 1, 8, Target(TARGET_POS, { 800, 800 })));
    mechanics.emplace_back(new Donut(264, 424, 2000, 0, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(268, 150, 1, 8, Target(TARGET_POS, { 200, 800 })));
    mechanics.emplace_back(new Spread(268, 424, 0, 4, Target(TARGET_POS, { 500, 500 })));
    mechanics.emplace_back(new Spread(272, 150, 1, 8, Target(TARGET_POS, { 200, 200 })));
    mechanics.emplace_back(new Donut(272, 424, 2000, 0, 4, Target(TARGET_POS, { 500, 500 })));

    
    mechanics.emplace_back(new EndMap(274));


    //music.setPlayingOffset(sf::seconds(52));
}
*/

void lazySong(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em)
{
    song.addCheckpoint(0, 0);

    mechanics.emplace_back(new EndMap(4));


    //music.setPlayingOffset(sf::seconds(52));
}

void thirdeye(std::vector<Mechanic*>& mechanics, Song& song, sf::Music& music, EntityManager& em)
{
    song.addCheckpoint(0, 0);

    mechanics.emplace_back(new Spread(4, 120, 1, 8, Target(TARGET_POS, { 300, 200 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(4, 120, 1, 8, Target(TARGET_POS, { 700, 200 }), DEBUFF_HAATO, 8, "purple"));

    mechanics.emplace_back(new Spread(8, 120, 1, 8, Target(TARGET_POS, { 700, 400 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(8, 120, 1, 8, Target(TARGET_POS, { 300, 400 }), DEBUFF_HAATO, 8, "purple"));

    mechanics.emplace_back(new Spread(12, 120, 1, 8, Target(TARGET_POS, { 300, 600 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(12, 120, 1, 8, Target(TARGET_POS, { 700, 600 }), DEBUFF_HAATO, 8, "purple"));

    mechanics.emplace_back(new Spread(16, 120, 1, 8, Target(TARGET_POS, { 300, 800 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(16, 120, 1, 8, Target(TARGET_POS, { 700, 800 }), DEBUFF_HAATO, 8, "purple"));


    song.addCheckpoint(17, 26);

    mechanics.emplace_back(new ActivateTotem(28, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xFFFFFFFF, 15));
    mechanics.emplace_back(new MoveEntity(28, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500, 500 }), 1000, true));
    mechanics.emplace_back(new TetherIndicator(28, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_FOLLOW), 30));


    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new ApplyDebuff(32 + 2 * i, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), DEBUFF_EYE1, 32));
    }

    mechanics.emplace_back(new ApplyDebuff(46.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_EYER, 2));
    mechanics.emplace_back(new ApplyDebuff(46.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_EYER, 2));

    mechanics.emplace_back(new DisplayImage(47.5, "Beatmaps/239584/sasasasasa.png", 2, Target(TARGET_POS, { 0, 270 })));
    mechanics.emplace_back(new DisplayImage(47.5, "Beatmaps/239584/saadaiya.png", 1, Target(TARGET_POS, { 0, 425 })));

    
    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new ApplyDebuff(48 + 2 * i, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), DEBUFF_EYE1, 32));
    }

    mechanics.emplace_back(new ApplyDebuff(62.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_EYER, 2));
    mechanics.emplace_back(new ApplyDebuff(62.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_EYER, 2));

    mechanics.emplace_back(new DisplayImage(63.5, "Beatmaps/239584/sasasasasa.png", 2, Target(TARGET_POS, { 0, 270 })));
    mechanics.emplace_back(new DisplayImage(63.5, "Beatmaps/239584/saadaiya.png", 1, Target(TARGET_POS, { 0, 425 })));
    
    mechanics.emplace_back(new ActivateTotem(60, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));
    


    song.addCheckpoint(40, 64);


    int arrayI[] = {1, 2, 1, 0, 1, 2, 1};
    int arrayJ[] = {1, 2, 3, 2, 1, 0, 1};

    for (int n = 0; n < 7; n++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == arrayI[n] && j == arrayJ[n]) continue;
                mechanics.emplace_back(new Spread(66 + 2*n, 180, 0, 2, Target(TARGET_POS, { 125 + 250.f * i, 125 + 250.f * j })));
            }
        }
    }

    mechanics.emplace_back(new ActivateTotem(78, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xFFFFFFFF, 15));
    mechanics.emplace_back(new MoveEntity(78, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500, 500 }), 1000, true));
    mechanics.emplace_back(new TetherIndicator(78, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_FOLLOW), 12));

    int arrayI2[] = { 1, 2, 3, 3, 3, 2};
    int arrayJ2[] = { 0, 0, 1, 2, 1, 3};

    int arrayI3[] = { 2, 1, 2, 2, 2, 1};
    int arrayJ3[] = { 1, 1, 2, 1, 2, 2};

    for (int n = 0; n < 6; n++) {
        mechanics.emplace_back(new ApplyDebuff(80 + 2 * n, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), DEBUFF_EYE1, 32));
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == arrayI2[n] && j == arrayJ2[n]) continue;
                if (i == arrayI3[n] && j == arrayJ3[n]) continue;
                mechanics.emplace_back(new Spread(80 + 2 * n, 180, 0, 2, Target(TARGET_POS, { 125 + 250.f * i, 125 + 250.f * j })));
            }
        }
    }


    mechanics.emplace_back(new ApplyDebuff(94.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_EYER, 2));
    mechanics.emplace_back(new ApplyDebuff(94.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_EYER, 2));

    mechanics.emplace_back(new DisplayImage(95.5, "Beatmaps/239584/sasasasasa.png", 3, Target(TARGET_POS, { 0, 270 })));
    mechanics.emplace_back(new DisplayImage(95.5, "Beatmaps/239584/saadaiya.png", 1, Target(TARGET_POS, { 0, 425 })));

    mechanics.emplace_back(new ActivateTotem(90, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));
                                            
    song.addCheckpoint(62, 95.7);

    mechanics.emplace_back(new ActivateTotem(96, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xFFFFFFFF, 15));
    mechanics.emplace_back(new MoveEntity(96, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500, 900 }), 1000, true));
    mechanics.emplace_back(new TetherIndicator(96, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_FOLLOW), 28));

    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new ApplyDebuff(98 + 2 * i, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), DEBUFF_EYE1, 32));
    }


    mechanics.emplace_back(new Spread(98, 120, 1, 2, Target(TARGET_POS, { 200, 200 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(100, 120, 1, 2, Target(TARGET_POS, { 300, 400 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(102, 120, 1, 2, Target(TARGET_POS, { 200, 600 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(104, 120, 1, 2, Target(TARGET_POS, { 300, 800 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(106, 120, 1, 2, Target(TARGET_POS, { 400, 600 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(108, 120, 1, 2, Target(TARGET_POS, { 300, 400 }), DEBUFF_GAADO, 8, "blue"));


    mechanics.emplace_back(new Spread(98, 120, 1, 2, Target(TARGET_POS, { 800, 200 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(100, 120, 1, 2, Target(TARGET_POS, { 700, 400 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(102, 120, 1, 2, Target(TARGET_POS, { 800, 600 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(104, 120, 1, 2, Target(TARGET_POS, { 700, 800 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(106, 120, 1, 2, Target(TARGET_POS, { 600, 600 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(108, 120, 1, 2, Target(TARGET_POS, { 700, 400 }), DEBUFF_HAATO, 8, "purple"));

    mechanics.emplace_back(new ApplyDebuff(110.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_EYER, 2));
    mechanics.emplace_back(new ApplyDebuff(110.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_EYER, 2));

    mechanics.emplace_back(new DisplayImage(111.5, "Beatmaps/239584/sasasasasa.png", 2, Target(TARGET_POS, { 0, 270 })));
    mechanics.emplace_back(new DisplayImage(111.5, "Beatmaps/239584/saadaiya.png", 1, Target(TARGET_POS, { 0, 425 })));


    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new ApplyDebuff(114 + 2 * i, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), DEBUFF_EYE1, 32));
    }


    mechanics.emplace_back(new Spread(114, 120, 1, 2, Target(TARGET_POS, { 200, 200 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(116, 120, 1, 2, Target(TARGET_POS, { 300, 400 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(118, 120, 1, 2, Target(TARGET_POS, { 200, 600 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(120, 120, 1, 2, Target(TARGET_POS, { 300, 800 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(122, 120, 1, 2, Target(TARGET_POS, { 400, 600 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(124, 120, 1, 2, Target(TARGET_POS, { 300, 400 }), DEBUFF_GAADO, 8, "blue"));


    mechanics.emplace_back(new Spread(114, 120, 1, 2, Target(TARGET_POS, { 800, 200 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(116, 120, 1, 2, Target(TARGET_POS, { 700, 400 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(118, 120, 1, 2, Target(TARGET_POS, { 800, 600 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(120, 120, 1, 2, Target(TARGET_POS, { 700, 800 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(122, 120, 1, 2, Target(TARGET_POS, { 600, 600 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(124, 120, 1, 2, Target(TARGET_POS, { 700, 400 }), DEBUFF_HAATO, 8, "purple"));

    mechanics.emplace_back(new ApplyDebuff(126.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_EYER, 2));
    mechanics.emplace_back(new ApplyDebuff(126.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_EYER, 2));

    mechanics.emplace_back(new DisplayImage(127.5, "Beatmaps/239584/sasasasasa.png", 2, Target(TARGET_POS, { 0, 270 })));
    mechanics.emplace_back(new DisplayImage(127.5, "Beatmaps/239584/saadaiya.png", 1, Target(TARGET_POS, { 0, 425 })));

    mechanics.emplace_back(new ActivateTotem(124, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));

    song.addCheckpoint(83, 128);

    mechanics.emplace_back(new Spread(130, 120, 1, 2, Target(TARGET_POS, { 300, 200 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(132, 120, 1, 2, Target(TARGET_POS, { 300, 300 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(134, 120, 1, 2, Target(TARGET_POS, { 300, 400 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(136, 120, 1, 2, Target(TARGET_POS, { 700, 500 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(138, 120, 1, 2, Target(TARGET_POS, { 700, 600 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(140, 120, 1, 2, Target(TARGET_POS, { 700, 700 }), DEBUFF_GAADO, 8, "blue"));

    mechanics.emplace_back(new Spread(130, 120, 1, 2, Target(TARGET_POS, { 700, 200 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(132, 120, 1, 2, Target(TARGET_POS, { 700, 300 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(134, 120, 1, 2, Target(TARGET_POS, { 700, 400 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(136, 120, 1, 2, Target(TARGET_POS, { 300, 500 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(138, 120, 1, 2, Target(TARGET_POS, { 300, 600 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(140, 120, 1, 2, Target(TARGET_POS, { 300, 700 }), DEBUFF_HAATO, 8, "purple"));


    mechanics.emplace_back(new ActivateTotem(142, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xFFFFFFFF, 15));
    mechanics.emplace_back(new MoveEntity(142, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500, 900 }), 1000, true));
    mechanics.emplace_back(new TetherIndicator(142, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_FOLLOW), 12));

    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new ApplyDebuff(144 + 2 * i, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), DEBUFF_EYE1, 32));
    }

    mechanics.emplace_back(new Spread(144, 120, 1, 2, Target(TARGET_POS, {300, 200}), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(146, 120, 1, 2, Target(TARGET_POS, { 300, 300 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(148, 120, 1, 2, Target(TARGET_POS, { 300, 400 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(150, 120, 1, 2, Target(TARGET_POS, { 700, 500 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(152, 120, 1, 2, Target(TARGET_POS, { 700, 600 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(154, 120, 1, 2, Target(TARGET_POS, { 700, 700 }), DEBUFF_GAADO, 8, "blue"));

    mechanics.emplace_back(new Spread(144, 120, 1, 2, Target(TARGET_POS, { 700, 200 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(146, 120, 1, 2, Target(TARGET_POS, { 700, 300 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(148, 120, 1, 2, Target(TARGET_POS, { 700, 400 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(150, 120, 1, 2, Target(TARGET_POS, { 300, 500 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(152, 120, 1, 2, Target(TARGET_POS, { 300, 600 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(154, 120, 1, 2, Target(TARGET_POS, { 300, 700 }), DEBUFF_HAATO, 8, "purple"));

    mechanics.emplace_back(new ApplyDebuff(158.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_EYER, 2));
    mechanics.emplace_back(new ApplyDebuff(158.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_EYER, 2));

    mechanics.emplace_back(new DisplayImage(159.5, "Beatmaps/239584/sasasasasa.png", 2, Target(TARGET_POS, { 0, 270 })));
    mechanics.emplace_back(new DisplayImage(159.5, "Beatmaps/239584/saadaiya.png", 1, Target(TARGET_POS, { 0, 425 })));

    mechanics.emplace_back(new ActivateTotem(156, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));


    song.addCheckpoint(105, 159.7);

    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new ApplyDebuff(162 + 2 * i, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), DEBUFF_EYE1, 32));
    }

    mechanics.emplace_back(new ActivateTotem(160, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xFFFFFFFF, 15));
    mechanics.emplace_back(new MoveEntity(160, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500, 500 }), 1000, true));
    mechanics.emplace_back(new TetherIndicator(160, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_FOLLOW), 28));


    mechanics.emplace_back(new Spread(162, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(0 * PI / 6), 500 + 250 * std::cos(0 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(166, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(2 * PI / 6), 500 + 250 * std::cos(2 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(170, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(4 * PI / 6), 500 + 250 * std::cos(4 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
                                                                                                                                           
    mechanics.emplace_back(new Spread(164, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(1 * PI / 6), 500 + 250 * std::cos(1 * PI / 6) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(168, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(3 * PI / 6), 500 + 250 * std::cos(3 * PI / 6) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(172, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(5 * PI / 6), 500 + 250 * std::cos(5 * PI / 6) }), DEBUFF_HAATO, 8, "purple"));
                                                                                                         
                                                                                                         
    mechanics.emplace_back(new Spread(162, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(0 * PI / 6 + PI), 500 + 250 * std::cos(0 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(166, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(2 * PI / 6 + PI), 500 + 250 * std::cos(2 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(170, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(4 * PI / 6 + PI), 500 + 250 * std::cos(4 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));

    mechanics.emplace_back(new Spread(164, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(1 * PI / 6 + PI), 500 + 250 * std::cos(1 * PI / 6 + PI) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(168, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(3 * PI / 6 + PI), 500 + 250 * std::cos(3 * PI / 6 + PI) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(172, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(5 * PI / 6 + PI), 500 + 250 * std::cos(5 * PI / 6 + PI) }), DEBUFF_GAADO, 8, "blue"));

    mechanics.emplace_back(new ApplyDebuff(174.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_EYER, 2));
    mechanics.emplace_back(new ApplyDebuff(174.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_EYER, 2));

    mechanics.emplace_back(new DisplayImage(175.5, "Beatmaps/239584/sasasasasa.png", 2, Target(TARGET_POS, { 0, 270 })));
    mechanics.emplace_back(new DisplayImage(175.5, "Beatmaps/239584/saadaiya.png", 1, Target(TARGET_POS, { 0, 425 })));




    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new ApplyDebuff(178 + 2 * i, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), DEBUFF_EYE1, 32));
    }

    mechanics.emplace_back(new Spread(178, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(0 * PI / 6), 500 + 250 * std::cos(0 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(182, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(2 * PI / 6), 500 + 250 * std::cos(2 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(186, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(4 * PI / 6), 500 + 250 * std::cos(4 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
                                                                                                                                           
    mechanics.emplace_back(new Spread(180, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(1 * PI / 6), 500 + 250 * std::cos(1 * PI / 6) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(184, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(3 * PI / 6), 500 + 250 * std::cos(3 * PI / 6) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(188, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(5 * PI / 6), 500 + 250 * std::cos(5 * PI / 6) }), DEBUFF_HAATO, 8, "purple"));
                                                                                                         
                                                                                                         
    mechanics.emplace_back(new Spread(178, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(0 * PI / 6 + PI), 500 + 250 * std::cos(0 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(182, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(2 * PI / 6 + PI), 500 + 250 * std::cos(2 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(186, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(4 * PI / 6 + PI), 500 + 250 * std::cos(4 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
                                                                                                                                                                          
    mechanics.emplace_back(new Spread(180, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(1 * PI / 6 + PI), 500 + 250 * std::cos(1 * PI / 6 + PI) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(184, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(3 * PI / 6 + PI), 500 + 250 * std::cos(3 * PI / 6 + PI) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(188, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(5 * PI / 6 + PI), 500 + 250 * std::cos(5 * PI / 6 + PI) }), DEBUFF_GAADO, 8, "blue"));

    mechanics.emplace_back(new ApplyDebuff(190.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_EYER, 2));
    mechanics.emplace_back(new ApplyDebuff(190.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_EYER, 2));

    mechanics.emplace_back(new DisplayImage(191.5, "Beatmaps/239584/sasasasasa.png", 2, Target(TARGET_POS, { 0, 270 })));
    mechanics.emplace_back(new DisplayImage(191.5, "Beatmaps/239584/saadaiya.png", 1, Target(TARGET_POS, { 0, 425 })));
    
    mechanics.emplace_back(new ActivateTotem(190, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));

    song.addCheckpoint(139, 207);

    mechanics.emplace_back(new Spread(210, 120, 1, 2, Target(TARGET_POS, { 300, 200 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(214, 120, 1, 2, Target(TARGET_POS, { 300, 400 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(218, 120, 1, 2, Target(TARGET_POS, { 300, 600 }), DEBUFF_GAADO, 8, "blue"));

    mechanics.emplace_back(new Spread(212, 120, 1, 2, Target(TARGET_POS, { 300, 300 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(216, 120, 1, 2, Target(TARGET_POS, { 300, 500 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(220, 120, 1, 2, Target(TARGET_POS, { 300, 700 }), DEBUFF_HAATO, 8, "purple"));

    mechanics.emplace_back(new Spread(212, 120, 1, 2, Target(TARGET_POS, { 700, 300 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(216, 120, 1, 2, Target(TARGET_POS, { 700, 500 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(220, 120, 1, 2, Target(TARGET_POS, { 700, 700 }), DEBUFF_GAADO, 8, "blue"));

    mechanics.emplace_back(new Spread(210, 120, 1, 2, Target(TARGET_POS, { 700, 200 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(214, 120, 1, 2, Target(TARGET_POS, { 700, 400 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(218, 120, 1, 2, Target(TARGET_POS, { 700, 600 }), DEBUFF_HAATO, 8, "purple"));


    int arrayI4[] = { 2, 1, 0, 1, 2, 3, 2 };
    int arrayJ4[] = { 2, 1, 2, 3, 2, 3, 2 };

    for (int n = 0; n < 7; n++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == arrayI4[n] && j == arrayJ4[n]) continue;
                mechanics.emplace_back(new Spread(234 + 2 * n, 180, 0, 2, Target(TARGET_POS, { 125 + 250.f * i, 125 + 250.f * j })));
            }
        }
    }

    mechanics.emplace_back(new ActivateTotem(246, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xFFFFFFFF, 15));
    mechanics.emplace_back(new MoveEntity(246, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500, 500 }), 1000, true));
    mechanics.emplace_back(new TetherIndicator(246, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_FOLLOW), 12));

    int arrayI5[] = { 1, 1, 2, 3, 2, 2 };
    int arrayJ5[] = { 3, 2, 2, 2, 2, 1 };

    int arrayI6[] = { 2, 2, 1, 1, 1, 1 };
    int arrayJ6[] = { 1, 0, 0, 1, 2, 1 };

    for (int n = 0; n < 6; n++) {
        mechanics.emplace_back(new ApplyDebuff(248 + 2 * n, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), DEBUFF_EYE1, 32));
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == arrayI5[n] && j == arrayJ5[n]) {
                    if(n%2 == 0)
                        mechanics.emplace_back(new Spread(248 + 2 * n, 120, 1, 2, Target(TARGET_POS, { 125 + 250.f * i, 125 + 250.f * j }), DEBUFF_GAADO, 8, "blue"));
                    else
                        mechanics.emplace_back(new Spread(248 + 2 * n, 120, 1, 2, Target(TARGET_POS, { 125 + 250.f * i, 125 + 250.f * j }), DEBUFF_HAATO, 8, "purple"));
                }
                else if (i == arrayI6[n] && j == arrayJ6[n]) {
                    if (n % 2 == 1)
                        mechanics.emplace_back(new Spread(248 + 2 * n, 120, 1, 2, Target(TARGET_POS, { 125 + 250.f * i, 125 + 250.f * j }), DEBUFF_GAADO, 8, "blue"));
                    else
                        mechanics.emplace_back(new Spread(248 + 2 * n, 120, 1, 2, Target(TARGET_POS, { 125 + 250.f * i, 125 + 250.f * j }), DEBUFF_HAATO, 8, "purple"));

                }

                else
                    mechanics.emplace_back(new Spread(248 + 2 * n, 180, 0, 2, Target(TARGET_POS, { 125 + 250.f * i, 125 + 250.f * j })));
            }
        }
    }

    mechanics.emplace_back(new ApplyDebuff(262.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_EYER, 2));
    mechanics.emplace_back(new ApplyDebuff(262.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_EYER, 2));

    mechanics.emplace_back(new DisplayImage(263.5, "Beatmaps/239584/sasasasasa.png", 3, Target(TARGET_POS, { 0, 270 })));
    mechanics.emplace_back(new DisplayImage(263.5, "Beatmaps/239584/saadaiya.png", 1, Target(TARGET_POS, { 0, 425 })));

    mechanics.emplace_back(new ActivateTotem(258, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));

    song.addCheckpoint(175, 264);

    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new ApplyDebuff(266 + 2 * i, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), DEBUFF_EYE1, 32));
    }

    mechanics.emplace_back(new ActivateTotem(264, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xFFFFFFFF, 15));
    mechanics.emplace_back(new MoveEntity(264, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500, 500 }), 1000, true));
    mechanics.emplace_back(new TetherIndicator(264, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_FOLLOW), 28));


    mechanics.emplace_back(new Spread(266, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(0 * PI / 6), 500 + 250 * std::cos(0 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(268, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(1 * PI / 6), 500 + 250 * std::cos(1 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(270, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(2 * PI / 6), 500 + 250 * std::cos(2 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(272, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(3 * PI / 6), 500 + 250 * std::cos(3 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(274, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(4 * PI / 6), 500 + 250 * std::cos(4 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(276, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(5 * PI / 6), 500 + 250 * std::cos(5 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));

    mechanics.emplace_back(new Spread(266, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(0 * PI / 6 + PI), 500 + 250 * std::cos(0 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(268, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(1 * PI / 6 + PI), 500 + 250 * std::cos(1 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(270, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(2 * PI / 6 + PI), 500 + 250 * std::cos(2 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(272, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(3 * PI / 6 + PI), 500 + 250 * std::cos(3 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(274, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(4 * PI / 6 + PI), 500 + 250 * std::cos(4 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(276, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(5 * PI / 6 + PI), 500 + 250 * std::cos(5 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));

    mechanics.emplace_back(new ApplyDebuff(278.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_EYER, 2));
    mechanics.emplace_back(new ApplyDebuff(278.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_EYER, 2));

    mechanics.emplace_back(new DisplayImage(279.5, "Beatmaps/239584/sasasasasa.png", 2, Target(TARGET_POS, { 0, 270 })));
    mechanics.emplace_back(new DisplayImage(279.5, "Beatmaps/239584/saadaiya.png", 1, Target(TARGET_POS, { 0, 425 })));


    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new ApplyDebuff(282 + 2 * i, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), DEBUFF_EYE1, 32));
    }

    mechanics.emplace_back(new Spread(282, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(0 * PI / 6), 500 + 250 * std::cos(0 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(284, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(1 * PI / 6), 500 + 250 * std::cos(1 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(286, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(2 * PI / 6), 500 + 250 * std::cos(2 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(288, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(3 * PI / 6), 500 + 250 * std::cos(3 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(290, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(4 * PI / 6), 500 + 250 * std::cos(4 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(292, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(5 * PI / 6), 500 + 250 * std::cos(5 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));

    mechanics.emplace_back(new Spread(282, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(0 * PI / 6 + PI), 500 + 250 * std::cos(0 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(284, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(1 * PI / 6 + PI), 500 + 250 * std::cos(1 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(286, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(2 * PI / 6 + PI), 500 + 250 * std::cos(2 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(288, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(3 * PI / 6 + PI), 500 + 250 * std::cos(3 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(290, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(4 * PI / 6 + PI), 500 + 250 * std::cos(4 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(292, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(5 * PI / 6 + PI), 500 + 250 * std::cos(5 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));

    mechanics.emplace_back(new ApplyDebuff(294.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_EYER, 2));
    mechanics.emplace_back(new ApplyDebuff(294.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_EYER, 2));

    mechanics.emplace_back(new DisplayImage(295.5, "Beatmaps/239584/sasasasasa.png", 2, Target(TARGET_POS, { 0, 270 })));
    mechanics.emplace_back(new DisplayImage(295.5, "Beatmaps/239584/saadaiya.png", 1, Target(TARGET_POS, { 0, 425 })));

    mechanics.emplace_back(new ActivateTotem(292, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));

    song.addCheckpoint(198, 296);

    mechanics.emplace_back(new Spread(298, 120, 1, 2, Target(TARGET_POS, { 100, 100 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(300, 120, 1, 2, Target(TARGET_POS, { 229, 212 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(302, 120, 1, 2, Target(TARGET_POS, { 219, 392 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(304, 120, 1, 2, Target(TARGET_POS, { 231, 553 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(306, 120, 1, 2, Target(TARGET_POS, { 330, 692 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(308, 120, 1, 2, Target(TARGET_POS, { 500, 686 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(310, 120, 1, 2, Target(TARGET_POS, { 584, 824 }), DEBUFF_GAADO, 8, "blue"));

    mechanics.emplace_back(new Spread(298, 120, 1, 2, Target(TARGET_POS, { 900, 900 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(300, 120, 1, 2, Target(TARGET_POS, { 771, 787 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(302, 120, 1, 2, Target(TARGET_POS, { 781, 617 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(304, 120, 1, 2, Target(TARGET_POS, { 769, 447 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(306, 120, 1, 2, Target(TARGET_POS, { 670, 308 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(308, 120, 1, 2, Target(TARGET_POS, { 500, 165 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(310, 120, 1, 2, Target(TARGET_POS, { 416, 165 }), DEBUFF_HAATO, 8, "purple"));


    mechanics.emplace_back(new ActivateTotem(310, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xFFFFFFFF, 15));
    mechanics.emplace_back(new MoveEntity(310, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500, 500 }), 1000, true));
    mechanics.emplace_back(new TetherIndicator(310, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_FOLLOW), 12));

    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new ApplyDebuff(312 + 2 * i, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), DEBUFF_EYE1, 32));
    }

    mechanics.emplace_back(new Spread(312, 120, 1, 2, Target(TARGET_POS, { 100, 100 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(314, 120, 1, 2, Target(TARGET_POS, { 260, 260 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(316, 120, 1, 2, Target(TARGET_POS, { 420, 420 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(318, 120, 1, 2, Target(TARGET_POS, { 420, 580 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(320, 120, 1, 2, Target(TARGET_POS, { 260, 740 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(322, 120, 1, 2, Target(TARGET_POS, { 100, 900 }), DEBUFF_GAADO, 8, "blue"));


    mechanics.emplace_back(new Spread(312, 120, 1, 2, Target(TARGET_POS, { 900, 900 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(314, 120, 1, 2, Target(TARGET_POS, { 740, 740 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(316, 120, 1, 2, Target(TARGET_POS, { 580, 580 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(318, 120, 1, 2, Target(TARGET_POS, { 580, 420 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(320, 120, 1, 2, Target(TARGET_POS, { 740, 260 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(322, 120, 1, 2, Target(TARGET_POS, { 900, 100 }), DEBUFF_HAATO, 8, "purple"));


    mechanics.emplace_back(new ApplyDebuff(326.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_EYER, 2));
    mechanics.emplace_back(new ApplyDebuff(326.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_EYER, 2));

    mechanics.emplace_back(new DisplayImage(327.5, "Beatmaps/239584/sasasasasa.png", 2, Target(TARGET_POS, { 0, 270 })));
    mechanics.emplace_back(new DisplayImage(327.5, "Beatmaps/239584/saadaiya.png", 1, Target(TARGET_POS, { 0, 425 })));

    mechanics.emplace_back(new ActivateTotem(322, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));

    song.addCheckpoint(221, 328);


    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new ApplyDebuff(330 + 2 * i, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), DEBUFF_EYE1, 32));
    }

    mechanics.emplace_back(new ActivateTotem(328, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xFFFFFFFF, 15));
    mechanics.emplace_back(new MoveEntity(328, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500, 500 }), 1000, true));
    mechanics.emplace_back(new TetherIndicator(328, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_FOLLOW), 28));


    mechanics.emplace_back(new Spread(330, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(0 * PI / 6), 500 + 250 * std::cos(0 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(332, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(1 * PI / 6), 500 + 250 * std::cos(1 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(334, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(2 * PI / 6), 500 + 250 * std::cos(2 * PI / 6) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(336, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(3 * PI / 6), 500 + 250 * std::cos(3 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(338, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(4 * PI / 6), 500 + 250 * std::cos(4 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(340, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(5 * PI / 6), 500 + 250 * std::cos(5 * PI / 6) }), DEBUFF_HAATO, 8, "purple"));

    mechanics.emplace_back(new Spread(330, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(0 * PI / 6 + PI), 500 + 250 * std::cos(0 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(332, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(1 * PI / 6 + PI), 500 + 250 * std::cos(1 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(334, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(2 * PI / 6 + PI), 500 + 250 * std::cos(2 * PI / 6 + PI) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(336, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(3 * PI / 6 + PI), 500 + 250 * std::cos(3 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(338, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(4 * PI / 6 + PI), 500 + 250 * std::cos(4 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(340, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(5 * PI / 6 + PI), 500 + 250 * std::cos(5 * PI / 6 + PI) }), DEBUFF_GAADO, 8, "blue"));

    mechanics.emplace_back(new ApplyDebuff(342.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_EYER, 2));
    mechanics.emplace_back(new ApplyDebuff(342.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_EYER, 2));

    mechanics.emplace_back(new DisplayImage(343.5, "Beatmaps/239584/sasasasasa.png", 2, Target(TARGET_POS, { 0, 270 })));
    mechanics.emplace_back(new DisplayImage(343.5, "Beatmaps/239584/saadaiya.png", 1, Target(TARGET_POS, { 0, 425 })));



    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new ApplyDebuff(346 + 2 * i, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), DEBUFF_EYE1, 32));
    }

    mechanics.emplace_back(new Spread(346, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(0 * PI / 6), 500 + 250 * std::cos(0 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(348, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(1 * PI / 6), 500 + 250 * std::cos(1 * PI / 6) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(350, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(2 * PI / 6), 500 + 250 * std::cos(2 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(352, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(3 * PI / 6), 500 + 250 * std::cos(3 * PI / 6) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(354, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(4 * PI / 6), 500 + 250 * std::cos(4 * PI / 6) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(356, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(5 * PI / 6), 500 + 250 * std::cos(5 * PI / 6) }), DEBUFF_HAATO, 8, "purple"));

    mechanics.emplace_back(new Spread(346, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(0 * PI / 6 + PI), 500 + 250 * std::cos(0 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(348, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(1 * PI / 6 + PI), 500 + 250 * std::cos(1 * PI / 6 + PI) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(350, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(2 * PI / 6 + PI), 500 + 250 * std::cos(2 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(352, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(3 * PI / 6 + PI), 500 + 250 * std::cos(3 * PI / 6 + PI) }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(354, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(4 * PI / 6 + PI), 500 + 250 * std::cos(4 * PI / 6 + PI) }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(356, 120, 1, 2, Target(TARGET_POS, { 500 + 250 * std::sin(5 * PI / 6 + PI), 500 + 250 * std::cos(5 * PI / 6 + PI) }), DEBUFF_GAADO, 8, "blue"));

    mechanics.emplace_back(new ApplyDebuff(358.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_EYER, 2));
    mechanics.emplace_back(new ApplyDebuff(358.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_EYER, 2));

    mechanics.emplace_back(new DisplayImage(359.5, "Beatmaps/239584/sasasasasa.png", 2, Target(TARGET_POS, { 0, 270 })));
    mechanics.emplace_back(new DisplayImage(359.5, "Beatmaps/239584/saadaiya.png", 1, Target(TARGET_POS, { 0, 425 })));

    mechanics.emplace_back(new ActivateTotem(356, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));


    mechanics.emplace_back(new Spread(362, 120, 1, 2, Target(TARGET_POS, { 300, 100 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(364, 120, 1, 2, Target(TARGET_POS, { 300, 260 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(366, 120, 1, 2, Target(TARGET_POS, { 300, 420 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(368, 120, 1, 2, Target(TARGET_POS, { 300, 580 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(370, 120, 1, 2, Target(TARGET_POS, { 300, 740 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(372, 120, 1, 2, Target(TARGET_POS, { 300, 900 }), DEBUFF_GAADO, 8, "blue"));


    mechanics.emplace_back(new Spread(362, 120, 1, 2, Target(TARGET_POS, { 700, 100 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(364, 120, 1, 2, Target(TARGET_POS, { 700, 260 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(366, 120, 1, 2, Target(TARGET_POS, { 700, 420 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(368, 120, 1, 2, Target(TARGET_POS, { 700, 580 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(370, 120, 1, 2, Target(TARGET_POS, { 700, 740 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(372, 120, 1, 2, Target(TARGET_POS, { 700, 900 }), DEBUFF_HAATO, 8, "purple"));


    for (int i = 0; i < 6; i++) {
        mechanics.emplace_back(new ApplyDebuff(376 + 2 * i, Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0), TARGET_FOLLOW), DEBUFF_EYE1, 32));
    }

    mechanics.emplace_back(new ActivateTotem(374, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), true, 0xFFFFFFFF, 15));
    mechanics.emplace_back(new MoveEntity(374, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), Target(TARGET_POS, { 500, 500 }), 1000, true));
    mechanics.emplace_back(new TetherIndicator(374, Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), Target(TARGET_CLOSEST, TARGET_PLAYERS, 0, new Target(TARGET_ENTITY, TARGET_TOTEMS, 0, TARGET_FOLLOW), TARGET_FOLLOW), 12));


    mechanics.emplace_back(new Spread(376, 120, 1, 2, Target(TARGET_POS, { 300, 100 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(378, 120, 1, 2, Target(TARGET_POS, { 300, 260 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(380, 120, 1, 2, Target(TARGET_POS, { 300, 420 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(382, 120, 1, 2, Target(TARGET_POS, { 300, 580 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(384, 120, 1, 2, Target(TARGET_POS, { 300, 740 }), DEBUFF_GAADO, 8, "blue"));
    mechanics.emplace_back(new Spread(386, 120, 1, 2, Target(TARGET_POS, { 300, 900 }), DEBUFF_GAADO, 8, "blue"));


    mechanics.emplace_back(new Spread(376, 120, 1, 2, Target(TARGET_POS, { 700, 100 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(378, 120, 1, 2, Target(TARGET_POS, { 700, 260 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(380, 120, 1, 2, Target(TARGET_POS, { 700, 420 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(382, 120, 1, 2, Target(TARGET_POS, { 700, 580 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(384, 120, 1, 2, Target(TARGET_POS, { 700, 740 }), DEBUFF_HAATO, 8, "purple"));
    mechanics.emplace_back(new Spread(386, 120, 1, 2, Target(TARGET_POS, { 700, 900 }), DEBUFF_HAATO, 8, "purple"));


    mechanics.emplace_back(new ApplyDebuff(390.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 0), DEBUFF_EYER, 2));
    mechanics.emplace_back(new ApplyDebuff(390.5, Target(TARGET_ENTITY, TARGET_PLAYERS, 1), DEBUFF_EYER, 2));

    mechanics.emplace_back(new DisplayImage(399.5, "Beatmaps/239584/sasasasasa.png", 10, Target(TARGET_POS, { 0, 270 })));
    mechanics.emplace_back(new DisplayImage(399.5, "Beatmaps/239584/saadaiya.png", 9, Target(TARGET_POS, { 0, 425 })));

    mechanics.emplace_back(new ActivateTotem(386, Target(TARGET_ENTITY, TARGET_TOTEMS, 0), false));



    mechanics.emplace_back(new EndMap(424));

}
