#include "bmp.hpp"

int main(){

    unsigned char data[12] = {
        0, 0, 255,
        0, 255, 0,
        255, 0, 0,
        255, 255, 255
    };
    writeBMP("image.bmp", 2, 2, (char*)data);

    return 0;
}
