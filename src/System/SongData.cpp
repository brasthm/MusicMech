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

		for (size_t i = 1; i < infos.size(); i++)
		{
			songs_.back().variants.emplace_back();
			songs_.back().variants.back().mmpath = infos[i];

			std::ifstream mmfile(RessourceLoader::getPath("Beatmaps/" + songs_.back().id + "/" + infos[i]));

			while (std::getline(mmfile, line))
			{
				auto words = Utils::split(line, ':');

				if (words.empty())
					continue;

				if (i == 1)
				{
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
				}
				
				if (words[0] == "Difficulty")
					songs_.back().variants.back().difficulty = words[1];
				if (words[0] == "Players")
					songs_.back().variants.back().nbPlayers = words[1];
				if (words[0] == "Variant")
					songs_.back().variants.back().label = words[1];

				if (words[0] == "[TimingPoints]")
					break;
			}

			mmfile.close();
		}
	}
	file_.close();

	selected_ = Random::randint(0, songs_.size());
	selectedVariant_ = 0;

	music_.openFromFile(RessourceLoader::getPath(songs_[selected_].songpath));

}

SongData SongDatabase::getSelectedSong()
{
	return songs_[selected_];
}

SongVariant SongDatabase::getSelectedVariant()
{
	return songs_[selected_].variants[selectedVariant_];
}

void SongDatabase::play()
{
	music_.stop();
	music_.openFromFile(RessourceLoader::getPath(songs_[selected_].songpath));
	music_.setVolume(50);
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

int SongDatabase::getIndexVariant()
{
	return selectedVariant_;
}

int SongDatabase::sizeVariant(int song)
{
	return songs_[song].variants.size();
}

void SongDatabase::setSelected(int selected, int variant)
{
	selected_ = selected;
	selectedVariant_ = variant;
}

void SongDatabase::setSelectedById(const std::string& id, int variant)
{
	for (int i = 0; i < songs_.size(); i++) {
		if (songs_[i].id == id) {
			selected_ = i;
			break;
		}
	}

	selectedVariant_ = variant;
}

SongData SongDatabase::getSong(int i)
{
	return songs_[i];
}

SongVariant SongDatabase::getVariant(int song, int var)
{
	return songs_[song].variants[var];
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

std::string SongDatabase::getCurentNbPlayers()
{
	return songs_[selected_].variants[selectedVariant_].nbPlayers;
}

std::string SongDatabase::getSelectedPath()
{
	return "Beatmaps/" + songs_[selected_].id + "/" + songs_[selected_].variants[selectedVariant_].mmpath;
}

std::string SongDatabase::getCurrentId()
{
	return songs_[selected_].id;
}

void SongDatabase::setVariant(std::string name)
{
	for (int i = 0; i < songs_[selected_].variants.size(); i++)
	{
		if (songs_[selected_].variants[i].label == name)
		{
			selectedVariant_ = i;
		}
	}
}
