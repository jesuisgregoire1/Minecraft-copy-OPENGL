#ifndef __TEXTURE_H__
#define __TEXTURE_H__
#include "glad/glad.h"
#include "stb_lib/stb_image.h"
#include <iostream>
namespace Texture{
    class TextureGeneration{
        private:
            int _width;
            int _height;
            int _nrOfChannels;
            unsigned int texture;
        public:
            void GenerateTexture(const char* path);
            void BindTexture();
    };
}
#endif