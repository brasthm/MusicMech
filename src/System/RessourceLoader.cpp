//
// Created by cyril on 21/05/2022.
//

#include "RessourceLoader.h"
#include <filesystem>
#include <iostream>


RessourceReference<sf::Font> RessourceLoader::getFont(std::string const& name)
{
    if(ressourceLoaderInstance.loadedFonts.find(name) != ressourceLoaderInstance.loadedFonts.end())
        return ressourceLoaderInstance.loadedFonts[name].get();
    else
        return ressourceLoaderInstance.loadFont(name);
}

RessourceReference<sf::Texture> RessourceLoader::getTexture(std::string const& name)
{
    if(ressourceLoaderInstance.loadedTextures.find(name) != ressourceLoaderInstance.loadedTextures.end())
        return ressourceLoaderInstance.loadedTextures[name].get();
    else
        return ressourceLoaderInstance.loadTexture(name);
}

RessourceReference<sf::SoundBuffer> RessourceLoader::getSoundBuffer(std::string const& name)
{
    if(ressourceLoaderInstance.loadedSoundBuffers.find(name) != ressourceLoaderInstance.loadedSoundBuffers.end())
        return ressourceLoaderInstance.loadedSoundBuffers[name].get();
    else
        return ressourceLoaderInstance.loadSoundBuffer(name);
}

RessourceReference<sf::Texture> RessourceLoader::loadTexture(std::string const& name)
{
    const std::string path = getPath(name);
    auto        tex  = std::make_unique<sf::Texture>();
    tex->loadFromFile(path);
    return loadedTextures.insert({name, std::move(tex)}).first->second.get();
}

RessourceReference<sf::Font> RessourceLoader::loadFont(std::string const& name)
{
    const std::string path = getPath(name);
    auto        font = std::make_unique<sf::Font>();
    font->loadFromFile(path);
    return loadedFonts.insert({name, std::move(font)}).first->second.get();
}

std::string RessourceLoader::getPath(std::string const& name)
{
    if(!ressourceLoaderInstance.wdSet)
    {
        using namespace std::filesystem;
        path p = current_path();
        while(!exists(p / "rc") && p.has_parent_path())
            p = p.parent_path();
        if(exists(p / "rc"))
            current_path(p);
        else
            throw std::runtime_error("Can't find resources directory");
        ressourceLoaderInstance.wdSet = true;
    }
    return "rc/" + name;
}

RessourceReference<sf::SoundBuffer> RessourceLoader::loadSoundBuffer(std::string const& name)
{
    std::string path = getPath(name);
    auto snd = std::make_unique<sf::SoundBuffer>();
    snd->loadFromFile(path);
    return loadedSoundBuffers.insert({name, std::move(snd)}).first->second.get();
}

