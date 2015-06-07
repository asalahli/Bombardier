#include "ResourceManager.hpp"
#include "GameObject.hpp"
#include "ErrorCode.hpp"
#include "sqlite3.h"
#include <cstring>

ResourceManager::ResourceManager(std::string assetsFile) {
    int rc;

    rc = sqlite3_open(assetsFile.c_str(), &mDB);
    if(rc != SQLITE_OK){
        std::cerr << "Could not open database: " << sqlite3_errmsg(mDB) << std::endl;
        throw ErrorCode(EC_DB_FAILURE);
    }
}

ResourceManager::~ResourceManager() {
    sqlite3_close(mDB);

    for (std::pair<std::string, sf::Texture*> item : mTextures) {
        delete item.second;
    }

    for (std::pair<std::string, sf::SoundBuffer*> item : mSoundBuffers) {
        delete item.second;
    }

    for (std::pair<std::string, sf::Image*> item : mImages) {
        delete item.second;
    }

    for (std::pair<std::string, sf::Font*> item : mFonts) {
        delete item.second;
    }
}

sf::Texture* ResourceManager::getTexture(std::string filename) {
    if (mTextures.count(filename) > 0) {
        return mTextures.at(filename);
    }

    int rc;
    std::string query = "SELECT bytes FROM files "
                        "WHERE  name='" + filename + "';";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(mDB, query.c_str(), -1, &stmt, NULL);
    if(rc != SQLITE_OK){
        std::cerr << "Could not prepare query: " << sqlite3_errmsg(mDB) << std::endl;
        sqlite3_finalize(stmt);
        throw ErrorCode(EC_DB_FAILURE);
    }

    rc = sqlite3_step(stmt);
    if(rc != SQLITE_ROW){
        std::cerr << "Could not execute query: " << sqlite3_errmsg(mDB) << std::endl;
        sqlite3_finalize(stmt);
        throw ErrorCode(EC_DB_FAILURE);
    }

    const void* data = sqlite3_column_blob(stmt, 0);
    size_t data_size = sqlite3_column_bytes(stmt, 0);

    sf::Texture* texture = new sf::Texture();

    if (!texture->loadFromMemory(data, data_size)) {
        throw ErrorCode(EC_TEXTURE_FAILURE);
    }

    mTextures[filename] = texture;

    sqlite3_finalize(stmt);

    return texture;
}

sf::SoundBuffer* ResourceManager::getSoundBuffer(std::string filename) {
    if (mSoundBuffers.count(filename) > 0) {
        return mSoundBuffers.at(filename);
    }

    int rc;
    std::string query = "SELECT bytes FROM files "
                        "WHERE  name='" + filename + "';";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(mDB, query.c_str(), -1, &stmt, NULL);
    if(rc != SQLITE_OK){
        std::cerr << "Could not prepare query: " << sqlite3_errmsg(mDB) << std::endl;
        sqlite3_finalize(stmt);
        throw ErrorCode(EC_DB_FAILURE);
    }

    rc = sqlite3_step(stmt);
    if(rc != SQLITE_ROW){
        std::cerr << "Could not execute query: " << sqlite3_errmsg(mDB) << std::endl;
        sqlite3_finalize(stmt);
        throw ErrorCode(EC_DB_FAILURE);
    }

    const void* data = sqlite3_column_blob(stmt, 0);
    size_t data_size = sqlite3_column_bytes(stmt, 0);

    sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();

    if (!soundBuffer->loadFromMemory(data, data_size)) {
        throw ErrorCode(EC_AUDIO_FAILURE);
    }

    mSoundBuffers[filename] = soundBuffer;

    sqlite3_finalize(stmt);

    return soundBuffer;
}

void ResourceManager::loadSprite(GameObject* go, int index, std::string name, int x, int y) {
    int rc;

    std::string query = "SELECT left, top, width, height "
                        "FROM   sprites "
                        "WHERE  name='" + name + "';";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(mDB, query.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "Could not prepare query: " << sqlite3_errmsg(mDB) << std::endl;
        sqlite3_finalize(stmt);
        throw ErrorCode(EC_DB_FAILURE);
    }

    rc = sqlite3_step(stmt);
    if(rc != SQLITE_ROW){
        std::cerr << "Could not execute query: " << sqlite3_errmsg(mDB) << std::endl;
        sqlite3_finalize(stmt);
        throw ErrorCode(EC_DB_FAILURE);
    }

    int l = sqlite3_column_int(stmt, 0);
    int t = sqlite3_column_int(stmt, 1);
    int w = sqlite3_column_int(stmt, 2);
    int h = sqlite3_column_int(stmt, 3);

    sqlite3_finalize(stmt);

    go->mVertices[index*4+0].position = sf::Vector2f(x, y);
    go->mVertices[index*4+1].position = sf::Vector2f(x+w, y);
    go->mVertices[index*4+2].position = sf::Vector2f(x+w, y+h);
    go->mVertices[index*4+3].position = sf::Vector2f(x, y+h);

    go->mVertices[index*4+0].texCoords = sf::Vector2f(l, t);
    go->mVertices[index*4+1].texCoords = sf::Vector2f(l+w, t);
    go->mVertices[index*4+2].texCoords = sf::Vector2f(l+w, t+h);
    go->mVertices[index*4+3].texCoords = sf::Vector2f(l, t+h);
}


sf::Image* ResourceManager::getImage(std::string filename) {
    if (mImages.count(filename) > 0) {
        return mImages.at(filename);
    }

    int rc;
    std::string query = "SELECT bytes FROM files "
                        "WHERE  name='" + filename + "';";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(mDB, query.c_str(), -1, &stmt, NULL);
    if(rc != SQLITE_OK){
        std::cerr << "Could not prepare query: " << sqlite3_errmsg(mDB) << std::endl;
        sqlite3_finalize(stmt);
        throw ErrorCode(EC_DB_FAILURE);
    }

    rc = sqlite3_step(stmt);
    if(rc != SQLITE_ROW){
        std::cerr << "Could not execute query: " << sqlite3_errmsg(mDB) << std::endl;
        sqlite3_finalize(stmt);
        throw ErrorCode(EC_DB_FAILURE);
    }

    const void* data = sqlite3_column_blob(stmt, 0);
    size_t data_size = sqlite3_column_bytes(stmt, 0);

    sf::Image* image = new sf::Image();

    if (!image->loadFromMemory(data, data_size)) {
        throw ErrorCode(EC_IMAGE_FAILURE);
    }

    mImages[filename] = image;

    sqlite3_finalize(stmt);

    return image;
}

sf::Font* ResourceManager::getFont(std::string filename) {
    if (mFonts.count(filename) > 0) {
        return mFonts.at(filename);
    }

    int rc;
    std::string query = "SELECT bytes FROM files "
                        "WHERE  name='" + filename + "';";

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(mDB, query.c_str(), -1, &stmt, NULL);
    if(rc != SQLITE_OK){
        std::cerr << "Could not prepare query: " << sqlite3_errmsg(mDB) << std::endl;
        sqlite3_finalize(stmt);
        throw ErrorCode(EC_DB_FAILURE);
    }

    rc = sqlite3_step(stmt);
    if(rc != SQLITE_ROW){
        std::cerr << "Could not execute query: " << sqlite3_errmsg(mDB) << std::endl;
        sqlite3_finalize(stmt);
        throw ErrorCode(EC_DB_FAILURE);
    }

    const void* data = sqlite3_column_blob(stmt, 0);
    size_t data_size = sqlite3_column_bytes(stmt, 0);

    //
    // Apparently, sf::Font::loadFromFile() doesn't copy the data
    //
    memcpy(fontBuffer, data, data_size);

    sf::Font* font = new sf::Font();

    if (!font->loadFromMemory(fontBuffer, data_size)) {
        throw ErrorCode(EC_FONT_FAILURE);
    }

    mFonts[filename] = font;

    sqlite3_finalize(stmt);

    return font;
}
