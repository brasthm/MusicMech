#ifndef MUSICMECH_CLIENT_IFLOAT_H
#define MUSICMECH_CLIENT_IFLOAT_H

#include <SFML/System.hpp>

class IFloat {
	float prev_, current_, target_;
	float duration_;
	bool moving_;
	sf::Time t_;

public:
	IFloat(float val);
	void init(float val);
	void set(float val, float sec);
	void update(sf::Time elapsed);
	float get();
	bool isMoving();

};


#endif