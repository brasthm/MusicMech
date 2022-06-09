//
// Created by cyril on 14/05/2022.
//

#ifndef MUSICMECH_SERVER_RANDOM_H
#define MUSICMECH_SERVER_RANDOM_H

#include <random>

class Random {
private:
    inline static Random *random;
    std::random_device r;
    std::mt19937 gen;

    inline Random() : gen(r()) {};
    inline int genrand(int lower = INT32_MIN, int upper = INT32_MAX) {
        std::uniform_real_distribution<> dis(lower, upper);
        return dis(gen);
    }

    inline static Random &getInstance() {
        if(!random)
            random = new Random();
        return *random;
    };
public:

    inline static int rand() {
        return getInstance().genrand();
    }

    inline static int randint(int lower, int upper) {
        return getInstance().genrand(lower, upper);
    }


    Random(const Random&) = delete;
    Random& operator= (const Random) = delete;
};


#endif //MUSICMECH_SERVER_RANDOM_H
