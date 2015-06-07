#ifndef ERROR_CODE_H

#define ERROR_CODE_H
#include <iostream>

#define EC_TEXTURE_FAILURE          1
#define EC_COULD_NOT_LOAD_IMAGE     2
#define EC_DB_FAILURE               3
#define EC_AUDIO_FAILURE            4
#define EC_IMAGE_FAILURE            5
#define EC_FONT_FAILURE             6

class ErrorCode {
    int mCode;
public:
    ErrorCode(int code) { mCode = code; };
    void informUser() { std::cerr << "Error #" << mCode << std::endl; };
};

#endif // ERROR_CODE_H

