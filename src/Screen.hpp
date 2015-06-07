#ifndef SCREEN_H
#define SCREEN_H

#include "Game.hpp"

class Screen {
    Game& mGame;

protected:
    bool mPaused;
public:
    Screen(Game& game) : mGame(game) { onCreate(); mPaused = false; };
    virtual ~Screen() {};

    Game& getGame() const { return mGame; };
    void pause() { mPaused = true; };
    void resume() { mPaused = false; };

    virtual void onCreate() {};
    virtual void onActivate() {};
    virtual void onDeactivate() {};

    virtual void onMouseDown(sf::Vector2f& pos, sf::Mouse::Button button) {};
    virtual void onMouseMove(sf::Vector2f& pos) {};
    virtual void onMouseWheel(sf::Event::MouseWheelEvent& event) {};
    virtual void onMouseWheelScroll(sf::Event::MouseWheelScrollEvent& event) {};

    virtual void onKeyDown(sf::Keyboard::Key key) {};

    virtual void update(float dt) {};
    virtual void draw() {};
};

#endif // SCREEN_H

