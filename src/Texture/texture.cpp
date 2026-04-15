#include "texture.hpp"

void Texture::TextureGeneration::GenerateTexture(const char* path){
    unsigned char* data;
    data = stbi_load(path, &_width, &_height, &_nrOfChannels, 0);
    // std::cout << "Loaded texture: " << path 
    //       << " " << _width << "x" << _height 
    //       << " channels: " << _nrOfChannels << std::endl;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // if(data){
    //     std :: cout << "We have data";
    // }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

void Texture::TextureGeneration::BindTexture(){
    glBindTexture(GL_TEXTURE_2D, texture);
}

int Texture::TextureGeneration::GetTextureWidth(){
    return _width;
}

int Texture::TextureGeneration::GetTextureHeigth(){
    return _height;
}