#include "Game.hpp"
#include "GameplayScreen.hpp"

Game::Game(ConfigSystem& config)
    : mConfig(config)
    , mGameOver(false)
{
    mResourceManager = new ResourceManager(config.assetFile);

    sf::VideoMode videoMode(config.windowWidth, config.windowHeight, 32);
    mWindow = new sf::RenderWindow(videoMode, config.gameTitle, sf::Style::Close | sf::Style::Titlebar);

    sf::View view = sf::View(sf::FloatRect(0, 0, config.windowWidth, config.windowHeight));
    view.zoom(2);
    mWindow->setView(view);

    mLaserSFX = mResourceManager->getSoundBuffer("sfx_laser2.ogg");
    mSpritesheet = mResourceManager->getTexture("space.png");
    mSpritesheet->setSmooth(true);

    sf::Image* icon = mResourceManager->getImage("icon.png");
    mWindow->setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());

    mBgMusic.setBuffer(*mResourceManager->getSoundBuffer("bg.ogg"));
    mDeathMusic.setBuffer(*mResourceManager->getSoundBuffer("death.ogg"));

    mBgMusic.setLoop(true);
    mBgMusic.play();

    /*
        Temporary!
        Update: Not really :D
    */
    mCurrentScreen = new GameplayScreen(*this);
}

Game::~Game() {
    delete mWindow;
    delete mCurrentScreen;
}

void Game::run() {
    mClock.restart();
//    getWindow().setMouseCursorVisible(false);
    while (getWindow().isOpen())
    {
        sf::Event event;
        while (getWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                getWindow().close();
            else if (!mGameOver && event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i pos(event.mouseButton.x, event.mouseButton.y);
                sf::Vector2f coords = getWindow().mapPixelToCoords(pos);
                mCurrentScreen->onMouseDown(coords, event.mouseButton.button);
            }
            else if (mGameOver && event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    restartGame();
                }
            }
            else if (!mGameOver && event.type == sf::Event::MouseMoved) {
                sf::Vector2i pos(event.mouseMove.x, event.mouseMove.y);
                sf::Vector2f coords = getWindow().mapPixelToCoords(pos);
                mCurrentScreen->onMouseMove(coords);
            }
            else if (!mGameOver && event.type == sf::Event::KeyPressed) {
                mCurrentScreen->onKeyDown(event.key.code);
            }
            else if (event.type == sf::Event::LostFocus) {
                mCurrentScreen->pause();
            }
            else if (event.type == sf::Event::GainedFocus) {
                mCurrentScreen->resume();
            }
        }

        int ms;
        for ( ;; ) {
            ms = mClock.getElapsedTime().asMilliseconds();
            if (ms >= getConfig().updateDelay) break;
            sf::sleep(sf::milliseconds(5));
        }
        mClock.restart();

        if (!mGameOver)
            mCurrentScreen->update(ms/1000.0);

        getWindow().clear();
        mCurrentScreen->draw();
        getWindow().display();
    }
}

void Game::gameOver() {
    mGameOver = true;
    mBgMusic.stop();
    mDeathMusic.play();
};

void Game::restartGame() {
    delete mCurrentScreen;
    mCurrentScreen = new GameplayScreen(*this);

    mGameOver = false;
    mDeathMusic.stop();
    mBgMusic.play();
}
