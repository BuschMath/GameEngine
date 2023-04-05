#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture {
private:
    unsigned int m_id;
    int m_width;
    int m_height;
    int m_nrChannels;

public:
    Texture(const std::string& filename);
    ~Texture();

    void bind() const;
    void unbind() const;

    // Getters
    unsigned int getId() const { return m_id; }
    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    int getNumChannels() const { return m_nrChannels; }
};

#endif // !TEXTURE_H
