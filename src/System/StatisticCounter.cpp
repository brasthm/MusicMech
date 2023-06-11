#include "StatisticCounter.h"
#include "../main.h"

StatisticCounter::StatisticCounter()
{
	
}

StatisticCounter& StatisticCounter::getInstance()
{
	if (!statisticsInstance) {
		statisticsInstance = std::unique_ptr<StatisticCounter>(new StatisticCounter());
	}

	return *statisticsInstance;
}

void StatisticCounter::_reset(int nbPlayers)
{
	players_ = nbPlayers;
	stats_[STATISTIC_DISTANCE] = std::make_unique<std::vector<float>>(players_);
	stats_[STATISTIC_STILL] = std::make_unique<std::vector<float>>(players_);
	stats_[STATISTIC_TARGET] = std::make_unique<std::vector<float>>(players_);
	stats_[STATISTIC_FAILED] = std::make_unique<std::vector<float>>(players_);
	stats_[STATISTIC_GREED] = std::make_unique<std::vector<float>>(players_);
	stats_[STATISTIC_INSHARE] = std::make_unique<std::vector<float>>(players_);

	active_ = std::make_unique<std::vector<bool>>(players_);

	timestamps_[TIMESTAMPS_FAILED].clear();
}

void StatisticCounter::_add(int key, int ind, float val)
{
	stats_[key]->at(ind) += val;
}

void StatisticCounter::_addTimestamp(int key, float val)
{
	timestamps_[key].push_back(val);
}

void StatisticCounter::_setActive(int ind, bool val)
{
	active_->at(ind) = val;
}

std::pair<int, float> StatisticCounter::_getOutlier(int key, bool first)
{
	std::vector<std::pair<int, float>> distances;

	std::vector<float> values;
	for (int i = 0; i < players_; i++) {
		if(active_->at(i))
			values.push_back(stats_[key]->at(i));
	}

	std::sort(values.begin(), values.end());

	float median = 0;
	median = stats_[key]->at(values.size() / 2);

	for (int i = 0; i < values.size(); i++) {
		if(median == 0)
			distances.emplace_back(i, stats_[key]->at(i));
		else
			distances.emplace_back(i, (stats_[key]->at(i) - median) / median);
	}

	std::sort(distances.begin(), distances.end(), 
		[](std::pair<int, float> a, std::pair<int, float> b) {
			return a.second < b.second;
		});

	if (first)
		return distances.front();
	else
		return distances.back();
}

float StatisticCounter::_get(int key, int ind)
{
	return stats_[key]->at(ind);
}

int StatisticCounter::_getTimestampSize(int key)
{
	return timestamps_[key].size();
}

float StatisticCounter::_getTimestamp(int key, float val)
{
	return timestamps_[key][val];
}

void StatisticCounter::reset(int nbPlayers)
{
	getInstance()._reset(nbPlayers);
}

void StatisticCounter::add(int key, int index, float val)
{
	getInstance()._add(key, index, val);
}

float StatisticCounter::get(int val, int index)
{
	return getInstance()._get(val, index);
}

float StatisticCounter::getTimestamp(int key, float val)
{
	return getInstance()._getTimestamp(key, val);
}

float StatisticCounter::getTimestampSize(int key)
{
	return getInstance()._getTimestampSize(key);
}

void StatisticCounter::addTimestamp(int key, float val)
{
	getInstance()._addTimestamp(key, val);
}

void StatisticCounter::setActive(int ind, bool val)
{
	getInstance()._setActive(ind, val);
}

std::pair<int, float> StatisticCounter::getOutlier(int key, bool first)
{
	return getInstance()._getOutlier(key, first);
}
