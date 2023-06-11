//
// Created by cyril on 14/05/2022.
//

#ifndef MUSICMECH_CLIENT_STATISTICCOUNTER_H
#define MUSICMECH_CLIENT_STATISTICCOUNTER_H

#include <iostream>
#include <map>
#include <vector>
#include <memory>

class StatisticCounter {
private:
    inline static std::unique_ptr<StatisticCounter> statisticsInstance;

    StatisticCounter();
    static StatisticCounter& getInstance();

    int players_;
    std::map<int, std::unique_ptr<std::vector<float>>> stats_;
    std::map<int, std::vector<float>> timestamps_;
    std::unique_ptr <std::vector<bool>> active_;

    void _reset(int nbPlayers);
    void _add(int key, int ind, float val);
    float _get(int key, int ind);
    int _getTimestampSize(int key);
    float _getTimestamp(int key, float val);
    void _addTimestamp(int key, float val);
    void _setActive(int ind, bool val);

    std::pair<int, float> _getOutlier(int key, bool first = true);

public:
    static void reset(int nbPlayers);
    static void add(int key, int index, float val);
    static float get(int val, int index);
    static float getTimestamp(int key, float val);
    static float getTimestampSize(int key);
    static void addTimestamp(int key, float val);
    static void setActive(int ind, bool val);
    static std::pair<int, float> getOutlier(int key, bool first = true);

    StatisticCounter(const StatisticCounter&) = delete;
    StatisticCounter& operator= (const StatisticCounter) = delete;
    
};


#endif //MUSICMECH_SERVER_RANDOM_H
