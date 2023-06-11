#include "Profile.h"
#include "RessourceLoader.h"
#include "../main.h"

#include <fstream>
#include <iostream>

Profile::Profile()
{
	defined_ = false;
	title_id_ = 0;
	banner_id_ = 0;
	name_ = "";

	returnCard_.create(400, 200);
	card_.create(400, 200);
	textCard_.create(400, 200);

	bg_.setTexture(RessourceLoader::getTexture("Images/Banner/" + BANNERS[BANNER_EMPTY].path));
	bg_.setPosition(0, 0);

	nameText_.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	nameText_.setFillColor(sf::Color::Black);
	nameText_.setCharacterSize(70);

	titleText_.setFont(RessourceLoader::getFont("Font/Roboto-Bold.ttf"));
	titleText_.setFillColor(sf::Color::Black);
	titleText_.setCharacterSize(30);

	clock_.restart();

}

void Profile::load(int id)
{
	std::string path;
	path = "PROFILE" + std::to_string(id) + ".dat";

	id_ = id;

	std::ifstream file(path, std::ios::in | std::ios::binary);
	if (!file) {
		//std::cout << "Cannot open file " << path << std::endl;
		defined_ = false;
		return;
	}
	
	// NAME
	size_t size = 0;
	file.read(reinterpret_cast<char*>(&size), sizeof(size_t));
	name_ = "";
	for (size_t i = 0; i < size; ++i) {
		char c = 0;
		file.read(reinterpret_cast<char*>(&c), sizeof(char));
		name_ += c;
	}

	// ID_TITLE
	file.read(reinterpret_cast<char*>(&title_id_), sizeof title_id_);

	//ID_BANNER
	file.read(reinterpret_cast<char*>(&banner_id_), sizeof banner_id_);

	defined_ = true;

	if(BANNERS[banner_id_].shader != "") 
		shader_.loadFromFile(RessourceLoader::getPath(BANNERS[banner_id_].shader), sf::Shader::Fragment);
	if (BANNERS[banner_id_].textShader != "")
		textShader_.loadFromFile(RessourceLoader::getPath(BANNERS[banner_id_].textShader), sf::Shader::Fragment);

	if(BANNERS[banner_id_].path != "")
		bg_.setTexture(RessourceLoader::getTexture("Images/Banner/" + BANNERS[banner_id_].path));

}

void Profile::save()
{
	std::string path;
	path = "PROFILE" + std::to_string(id_) + ".dat";


	std::ofstream file(path, std::ios::out | std::ios::binary);
	if (!file) {
		std::cout << "Cannot open file " << path << std::endl;
	}

	// NAME
	size_t size = name_.size();
	file.write(reinterpret_cast<char*>(&size), sizeof(size_t));

	for (size_t i = 0; i < size; ++i) {
		file.write(reinterpret_cast<char*>(&name_[i]), sizeof(char));
	}

	// ID_TITLE
	file.write(reinterpret_cast<char*>(&title_id_), sizeof title_id_);

	//ID_BANNER
	file.write(reinterpret_cast<char*>(&banner_id_), sizeof banner_id_);
}

void Profile::create(int id, std::string name)
{
	id_ = id;
	name_ = name;
	defined_ = true;
	title_id_ = TITLE_EMPTY;
	banner_id_ = BANNER_NOVICE;

	if (BANNERS[banner_id_].shader != "")
		shader_.loadFromFile(RessourceLoader::getPath(BANNERS[banner_id_].shader), sf::Shader::Fragment);
	if (BANNERS[banner_id_].textShader != "")
		textShader_.loadFromFile(RessourceLoader::getPath(BANNERS[banner_id_].textShader), sf::Shader::Fragment);

	if (BANNERS[banner_id_].path != "")
		bg_.setTexture(RessourceLoader::getTexture("Images/Banner/" + BANNERS[banner_id_].path));
}

bool Profile::isDefined()
{
	return defined_;
}


std::string Profile::getName() const
{
	return name_;
}

int Profile::getBannerId() const
{
	return banner_id_;
}

int Profile::getTitleId() const
{
	return title_id_;
}

void Profile::setProfile(std::string const& name, int banner, int title)
{
	defined_ = true;
	name_ = name;
	banner_id_ = banner;
	title_id_ = title;

	if (BANNERS[banner_id_].shader != "")
		shader_.loadFromFile(RessourceLoader::getPath(BANNERS[banner_id_].shader), sf::Shader::Fragment);
	if (BANNERS[banner_id_].textShader != "")
		textShader_.loadFromFile(RessourceLoader::getPath(BANNERS[banner_id_].textShader), sf::Shader::Fragment);

	if (BANNERS[banner_id_].path != "")
		bg_.setTexture(RessourceLoader::getTexture("Images/Banner/" + BANNERS[banner_id_].path));
}

const sf::RenderTexture& Profile::getProfileCard()
{
	nameText_.setString(name_);
	nameText_.setPosition(400 / 2 - nameText_.getGlobalBounds().width / 2, 55);

	titleText_.setString(TITLES[title_id_]);
	titleText_.setPosition(400 / 2 - titleText_.getGlobalBounds().width / 2, 140);

	textCard_.clear(sf::Color::Transparent);

	if (defined_) {
		textCard_.draw(nameText_);
	}
	textCard_.display();

	card_.clear();
	card_.draw(bg_);
	card_.draw(titleText_);
	sf::Sprite spr(textCard_.getTexture());
	spr.setPosition(0, 0);

	if (BANNERS[banner_id_].textShader != "") {
		textShader_.setUniform("time", clock_.getElapsedTime().asSeconds());
		card_.draw(spr, &textShader_);
	}
	else {
		card_.draw(spr);
	}

	card_.display();

	if (BANNERS[banner_id_].shader == "")
		return card_;

	
	returnCard_.clear();

	sf::Sprite sp(card_.getTexture());
	sp.setPosition(0, 0);
	shader_.setUniform("time", clock_.getElapsedTime().asSeconds());
	returnCard_.draw(sp, &shader_);
	returnCard_.display();

	return returnCard_;
}
