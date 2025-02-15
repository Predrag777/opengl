#include "texture.h"
#include "std_image.h"

Texture::Texture(const std::string& filename){
    unsigned int width, height, numComponents;
    unsigned char* imageData=stbi_load(filename.c_str(), &width, &height, &numComponents, 4);

    if(imageData==NULL)
        std::cerr << "Texture loading failed"<<std::endl;

    glGlenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

    stbi_image_free(imageData);
}

Texture::~Texture{
    glDeleteTextures(1, &m_texture);;
}

void Texture::Bind(unsigned int unit){
    assert(unit>=0 && unit<=31);
    glActivateTexture(GL_TEXTURE0+unit);
    glBindTexture(GL_TEXTURE_2D, m_texture);
}