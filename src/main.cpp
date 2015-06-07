#include "ErrorCode.hpp"
#include "ConfigSystem.hpp"
#include "Game.hpp"

int main()
{
    int returnCode = 0;

    try {
        ConfigSystem config;
        Game game(config);

        game.run();
    }
    catch (ErrorCode e) {
        e.informUser();
        std::cin >> returnCode;
        returnCode = 1;
    }

    return returnCode;
}

