#include "InfoBox.hpp"

#define CORNER 20

InfoBox::InfoBox(Screen& screen)
    : GameObject(screen)
{
    sf::Font* font = getScreen().getGame().getResourceManager().getFont("kenvector_future.ttf");

    bg.setFillColor(sf::Color::Black);
    bg.setPosition(0, 100);
    bg.setSize(sf::Vector2f(800, 400));

    lmb.setTexture(*getScreen().getGame().getResourceManager().getTexture("mouseLeftWhite.png"));
    rmb.setTexture(*getScreen().getGame().getResourceManager().getTexture("mouseRightWhite.png"));

    lmb.setPosition(80, 150);
    rmb.setPosition(420, 150);

    help1.setFont(*font);
    help1.setString("Fire");
    help1.setCharacterSize(48);
    help1.setColor(sf::Color::White);
    help1.setPosition(180, 165);
    help1.setStyle(sf::Text::Bold);

    help2.setFont(*font);
    help2.setString("Move");
    help2.setCharacterSize(48);
    help2.setColor(sf::Color::White);
    help2.setPosition(520, 165);
    help2.setStyle(sf::Text::Bold);

    help3.setFont(*font);
    help3.setString("Press SPACE to play");
    help3.setCharacterSize(48);
    help3.setColor(sf::Color::White);
    help3.setPosition(55, 350);
    help3.setStyle(sf::Text::Bold);

    mVertices.resize(4);
    getScreen().getGame().getResourceManager().loadSprite(this, 0, "glassPanel.png", 0, 0);

    sf::Vector2f a = mVertices[0].texCoords;
    sf::Vector2f b = mVertices[2].texCoords;

    mVertices.resize(36);

    // 1
    mVertices[0].texCoords = sf::Vector2f(a.x, a.y);
    mVertices[1].texCoords = sf::Vector2f(a.x+CORNER, a.y);
    mVertices[2].texCoords = sf::Vector2f(a.x+CORNER, a.y+CORNER);
    mVertices[3].texCoords = sf::Vector2f(a.x, a.y+CORNER);

    // 2
    mVertices[4].texCoords = sf::Vector2f(b.x-CORNER, a.y);
    mVertices[5].texCoords = sf::Vector2f(b.x, a.y);
    mVertices[6].texCoords = sf::Vector2f(b.x, a.y+CORNER);
    mVertices[7].texCoords = sf::Vector2f(b.x-CORNER, a.y+CORNER);

    // 3
    mVertices[8].texCoords = sf::Vector2f(b.x-CORNER, b.y-CORNER);
    mVertices[9].texCoords = sf::Vector2f(b.x, b.y-CORNER);
    mVertices[10].texCoords = sf::Vector2f(b.x, b.y);
    mVertices[11].texCoords = sf::Vector2f(b.x-CORNER, b.y);

    // 4
    mVertices[12].texCoords = sf::Vector2f(a.x, b.y-CORNER);
    mVertices[13].texCoords = sf::Vector2f(a.x+CORNER, b.y-CORNER);
    mVertices[14].texCoords = sf::Vector2f(a.x+CORNER, b.y);
    mVertices[15].texCoords = sf::Vector2f(a.x, b.y);

    // top
    mVertices[16].texCoords = sf::Vector2f(a.x+CORNER, a.y);
    mVertices[17].texCoords = sf::Vector2f(b.x-CORNER, a.y);
    mVertices[18].texCoords = sf::Vector2f(b.x-CORNER, a.y+CORNER);
    mVertices[19].texCoords = sf::Vector2f(a.x+CORNER, a.y+CORNER);

    // left
    mVertices[20].texCoords = sf::Vector2f(a.x, a.y+CORNER);
    mVertices[21].texCoords = sf::Vector2f(a.x+CORNER, a.y+CORNER);
    mVertices[22].texCoords = sf::Vector2f(a.x+CORNER, b.y-CORNER);
    mVertices[23].texCoords = sf::Vector2f(a.x, b.y-CORNER);

    // center
    mVertices[24].texCoords = sf::Vector2f(a.x+CORNER, a.y+CORNER);
    mVertices[25].texCoords = sf::Vector2f(b.x-CORNER, a.y+CORNER);
    mVertices[26].texCoords = sf::Vector2f(b.x-CORNER, b.y-CORNER);
    mVertices[27].texCoords = sf::Vector2f(a.x+CORNER, b.y-CORNER);

    // right
    mVertices[28].texCoords = sf::Vector2f(b.x-CORNER, a.y+CORNER);
    mVertices[29].texCoords = sf::Vector2f(b.x, a.y+CORNER);
    mVertices[30].texCoords = sf::Vector2f(b.x, b.y-CORNER);
    mVertices[31].texCoords = sf::Vector2f(b.x-CORNER, b.y-CORNER);

    // bottom
    mVertices[32].texCoords = sf::Vector2f(a.x+CORNER, b.y-CORNER);
    mVertices[33].texCoords = sf::Vector2f(b.x-CORNER, b.y-CORNER);
    mVertices[34].texCoords = sf::Vector2f(b.x-CORNER, b.y);
    mVertices[35].texCoords = sf::Vector2f(a.x+CORNER, b.y);

    setBoxCoords(sf::FloatRect(0, 100, 800, 400));
}

void InfoBox::update(float dt) {
    GameObject::update(dt);
}

void InfoBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(bg);

    GameObject::draw(target, states);

    target.draw(help1);
    target.draw(help2);
    target.draw(help3);
    target.draw(lmb);
    target.draw(rmb);
}

void InfoBox::setBoxCoords(sf::FloatRect box) {
    sf::Vector2f a(box.left, box.top);
    sf::Vector2f b(box.left+box.width, box.top+box.height);

    mVertices[0].position = sf::Vector2f(a.x, a.y);
    mVertices[1].position = sf::Vector2f(a.x+CORNER, a.y);
    mVertices[2].position = sf::Vector2f(a.x+CORNER, a.y+CORNER);
    mVertices[3].position = sf::Vector2f(a.x, a.y+CORNER);

    mVertices[4].position = sf::Vector2f(b.x-CORNER, a.y);
    mVertices[5].position = sf::Vector2f(b.x, a.y);
    mVertices[6].position = sf::Vector2f(b.x, a.y+CORNER);
    mVertices[7].position = sf::Vector2f(b.x-CORNER, a.y+CORNER);

    mVertices[8].position = sf::Vector2f(b.x-CORNER, b.y-CORNER);
    mVertices[9].position = sf::Vector2f(b.x, b.y-CORNER);
    mVertices[10].position = sf::Vector2f(b.x, b.y);
    mVertices[11].position = sf::Vector2f(b.x-CORNER, b.y);

    mVertices[12].position = sf::Vector2f(a.x, b.y-CORNER);
    mVertices[13].position = sf::Vector2f(a.x+CORNER, b.y-CORNER);
    mVertices[14].position = sf::Vector2f(a.x+CORNER, b.y);
    mVertices[15].position = sf::Vector2f(a.x, b.y);

    mVertices[16].position = sf::Vector2f(a.x+CORNER, a.y);
    mVertices[17].position = sf::Vector2f(b.x-CORNER, a.y);
    mVertices[18].position = sf::Vector2f(b.x-CORNER, a.y+CORNER);
    mVertices[19].position = sf::Vector2f(a.x+CORNER, a.y+CORNER);

    mVertices[20].position = sf::Vector2f(a.x, a.y+CORNER);
    mVertices[21].position = sf::Vector2f(a.x+CORNER, a.y+CORNER);
    mVertices[22].position = sf::Vector2f(a.x+CORNER, b.y-CORNER);
    mVertices[23].position = sf::Vector2f(a.x, b.y-CORNER);

    mVertices[24].position = sf::Vector2f(a.x+CORNER, a.y+CORNER);
    mVertices[25].position = sf::Vector2f(b.x-CORNER, a.y+CORNER);
    mVertices[26].position = sf::Vector2f(b.x-CORNER, b.y-CORNER);
    mVertices[27].position = sf::Vector2f(a.x+CORNER, b.y-CORNER);

    mVertices[28].position = sf::Vector2f(b.x-CORNER, a.y+CORNER);
    mVertices[29].position = sf::Vector2f(b.x, a.y+CORNER);
    mVertices[30].position = sf::Vector2f(b.x, b.y-CORNER);
    mVertices[31].position = sf::Vector2f(b.x-CORNER, b.y-CORNER);

    mVertices[32].position = sf::Vector2f(a.x+CORNER, b.y-CORNER);
    mVertices[33].position = sf::Vector2f(b.x-CORNER, b.y-CORNER);
    mVertices[34].position = sf::Vector2f(b.x-CORNER, b.y);
    mVertices[35].position = sf::Vector2f(a.x+CORNER, b.y);
}
