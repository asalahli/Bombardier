#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include <map>
#include <string>

struct sqlite3;
class GameObject;

class ResourceManager {
    sqlite3 *mDB;

    char fontBuffer[40000];

    std::map<std::string, sf::Texture*> mTextures;
    std::map<std::string, sf::SoundBuffer*> mSoundBuffers;
    std::map<std::string, sf::Image*> mImages;
    std::map<std::string, sf::Font*> mFonts;
public:
    ResourceManager(std::string assetsFile);
    ~ResourceManager();

    sf::Texture* getTexture(std::string filename);
    sf::SoundBuffer* getSoundBuffer(std::string filename);
    sf::Image* getImage(std::string filename);
    sf::Font* getFont(std::string filename);

    void loadSprite(GameObject* go, int index, std::string name, int x, int y);
};

#endif // RESOURCE_MANAGER_H
