#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "ConfigSystem.hpp"
#include "ResourceManager.hpp"
#include "ErrorCode.hpp"

class Screen;

class Game {
    ConfigSystem& mConfig;
    ResourceManager* mResourceManager;

    sf::Clock mClock;
    sf::RenderWindow* mWindow;
    sf::Texture* mSpritesheet;
    sf::SoundBuffer* mLaserSFX;

    sf::Sound mBgMusic;
    sf::Sound mDeathMusic;

    Screen* mCurrentScreen;

    bool mGameOver;

public:
    Game(ConfigSystem& config);
    ~Game();

    sf::Texture& getSpritesheet() const { return *mSpritesheet; };
    sf::SoundBuffer& getSoundBuffer() const { return *mLaserSFX; };
    sf::RenderWindow& getWindow() { return *mWindow; };
    ConfigSystem& getConfig() { return mConfig; };
    ResourceManager& getResourceManager() { return *mResourceManager; };

    bool isGameOver() { return mGameOver; };

    void gameOver();
    void restartGame();

    void run();
};

#endif // GAME_H


