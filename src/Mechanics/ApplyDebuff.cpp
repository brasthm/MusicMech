//
// Created by cyril on 03/07/2022.
//

#include "ApplyDebuff.h"
#include "../System/StatisticCounter.h"
#include "../main.h"

ApplyDebuff::ApplyDebuff(float beat, const Target& target, DebuffType type, float duration) : target_(target) {
    beat_ = beat;
    type_ = type;
    end_ = beat + duration;
    passed_ = true;
}

void ApplyDebuff::onPassed(const sf::Time &elapsed, float currentBeat, float currentPart, EntityManager &entities) {
    entities.applyDebuff(currentBeat, target_, type_, end_);
    if (target_.team == TARGET_PLAYERS) {
        StatisticCounter::add(STATISTIC_TARGET, entities.getIndex(target_), 1);
    }
}

void ApplyDebuff::onFailed(const sf::Time& elapsed, float currentBeat, float currentPart, EntityManager& entities)
{
    if (target_.team == TARGET_PLAYERS) {
        StatisticCounter::add(STATISTIC_TARGET, entities.getIndex(target_), 1);
    }
}

Mechanic* ApplyDebuff::clone()
{
    return new ApplyDebuff(*this);
}

std::string ApplyDebuff::toString() {
    std::string res =  "DEBUFF," + std::to_string(beat_) + "," + std::to_string(type_) + ","
    + std::to_string(end_-beat_) + ",";

    res += target_.to_string();

    return res;
}

void ApplyDebuff::reset(float beat)
{
    target_.reset();
    Mechanic::reset(beat);
}
