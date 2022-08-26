#include "SongData.h"

#include "RessourceLoader.h"
#include "Utils.h"
#include "Random.h"

SongDatabase::SongDatabase()
{
	file_.open(RessourceLoader::getPath("Beatmaps/beatmap_list.txt"));

	std::string line;
	while (std::getline(file_, line))
	{
		auto infos = Utils::split(line, '|');
		songs_.emplace_back();
		songs_.back().id = infos[0];
		songs_.back().mmpath = infos[1];

		std::ifstream mmfile(RessourceLoader::getPath("Beatmaps/" + songs_.back().id + "/[4P] " + songs_.back().mmpath));
		while (std::getline(mmfile, line))
		{
			auto words = Utils::split(line, ':');

			if (words[0] == "AudioFilename") 
				songs_.back().songpath = "Beatmaps/" + songs_.back().id + "/" + words[1];
			if (words[0] == "BackgroundImage")
				songs_.back().image = "Beatmaps/" + songs_.back().id + "/" + words[1];
			if (words[0] == "VignetteImage")
				songs_.back().vignette = "Beatmaps/" + songs_.back().id + "/" + words[1];
			if (words[0] == "Title")
				songs_.back().name = words[1];
			if (words[0] == "Artist")
				songs_.back().artist = words[1];
			if (words[0] == "PreviewTime")
				songs_.back().preview = std::stoi(words[1]);
			if (words[0] == "Difficulty")
				songs_.back().difficulty = words[1];

			if (words[0] == "[TimingPoints]")
				break;
		}
		mmfile.close();
	}
	file_.close();

	mode_ = "4P";

	selected_ = Random::randint(0, songs_.size());

	music_.openFromFile(RessourceLoader::getPath(songs_[selected_].songpath));

}

SongData SongDatabase::getSelectedSong()
{
	return songs_[selected_];
}

void SongDatabase::play()
{
	music_.stop();
	music_.openFromFile(RessourceLoader::getPath(songs_[selected_].songpath));
	music_.setVolume(10);
	music_.setPlayingOffset(sf::milliseconds(songs_[selected_].preview));
	music_.setLoop(true);
	music_.play();
}

void SongDatabase::stop()
{
	music_.stop();
}

int SongDatabase::size()
{
	return songs_.size();
}

int SongDatabase::getSelected()
{
	return selected_;
}

void SongDatabase::setSelected(int selected)
{
	selected_ = selected;
}

void SongDatabase::setSelectedById(const std::string& id)
{
	for (int i = 0; i < songs_.size(); i++) {
		if (songs_[i].id == id) {
			selected_ = i;
			break;
		}
	}
}

SongData SongDatabase::getSong(int i)
{
	return songs_[i];
}

void SongDatabase::setSong(int i)
{
	music_.stop();
	music_.openFromFile(RessourceLoader::getPath(songs_[i].songpath));
	music_.setVolume(10);
	music_.setPlayingOffset(sf::milliseconds(songs_[i].preview));
	music_.setLoop(true);
	music_.play();
}

bool SongDatabase::isPlaying()
{
	return music_.getStatus() == sf::SoundSource::Status::Playing;
}

std::string SongDatabase::getMode()
{
	return mode_;
}

std::string SongDatabase::getSelectedPath()
{
	return "Beatmaps/" + songs_[selected_].id + "/[" + mode_ + "] " + songs_[selected_].mmpath;
}

void SongDatabase::setMode(const std::string& mode)
{
	mode_ = mode;
}
