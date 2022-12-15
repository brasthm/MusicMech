//
// Created by cyril on 14/05/2022.
//

#ifndef MUSICMECH_SERVER_RANDOM_H
#define MUSICMECH_SERVER_RANDOM_H

#include <random>
#include <iostream>
#include <algorithm>

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
    inline sf::Uint32 genurand(int lower = 0, int upper = UINT32_MAX) {
        std::uniform_real_distribution<> dis(lower, upper);
        return dis(gen);
    }
    template<typename T>
    inline void shuffle_(std::vector<T> &v) {
        std::shuffle(v.begin(), v.end(), gen);
    }

    inline void setSeed_(std::seed_seq *seed) {
        gen.seed(*seed);
        std::cout << gen() << std::endl;
    }

    inline static Random &getInstance() {
        if(!random)
            random = new Random();
        return *random;
    };

    inline ~Random() {
        delete random;
    }
public:

    inline static int rand() {
        return getInstance().genrand();
    }

    inline static int randint(int lower, int upper) {
        return getInstance().genrand(lower, upper);
    }
    inline static sf::Uint32 randuint() {
        return getInstance().genrand();
    }


    template<typename T>
    inline static void shuffle(std::vector<T> &v) {
        getInstance().shuffle_(v);
    }

    inline static void setSeed(std::seed_seq *seed) {
        getInstance().setSeed_(seed);
    }


    Random(const Random&) = delete;
    Random& operator= (const Random) = delete;
};


#endif //MUSICMECH_SERVER_RANDOM_H
