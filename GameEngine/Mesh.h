#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm.hpp>
#include <GL/glew.h>

class Mesh {
public:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
    };

    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);

    const std::vector<Vertex>& getVertices() const;
    const std::vector<unsigned int>& getIndices() const;

    int getIndexCount() { return m_indices.size(); };
    GLuint getVAO() const { return m_VAO; };
    GLuint getVBO() const { return m_VBO; };
    GLuint getEBO() const { return m_EBO; };

    void bind();
    void unbind();

private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
};

#endif // !MESH_H

