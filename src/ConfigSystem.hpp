#ifndef CONFIG_SYSTEM_H
#define CONFIG_SYSTEM_H

#include <string>

class ConfigSystem {
public:
    int windowWidth;
    int windowHeight;

    std::string gameTitle;

    int updateDelay;
    int frameDelay;

    std::string assetFile;

    ConfigSystem()
        : windowWidth(800)
        , windowHeight(600)
        , gameTitle("Bombardier")
        , updateDelay(1)
        , frameDelay(1)
        , assetFile("assets.dat")
    {

    }
};

#endif // CONFIG_SYSTEM_H

