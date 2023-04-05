#include "Texture.h"
#include "stb_image.h"
#include <GL/glew.h>
#include <iostream>

Texture::Texture(const std::string& filename) :
    m_id(0),
    m_width(0),
    m_height(0),
    m_nrChannels(0)
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename.c_str(), &m_width, &m_height, &m_nrChannels, 0);

    if (data) {
        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
        if (m_nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if (m_nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else {
            std::cout << "Failed to load texture: " << filename << std::endl;
        }
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    }
    else {
        std::cout << "Failed to load texture: " << filename << std::endl;
    }
}

Texture::~Texture() {
    glDeleteTextures(1, &m_id);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}
