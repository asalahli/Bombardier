#include "Cursor.hpp"

Cursor::Cursor(Screen& screen)
    : GameObject(screen)
{
    mVertices.resize(4);
    getScreen().getGame().getResourceManager().loadSprite(this, 0, "cursor_pointer3D.png", 0, 0);
}
