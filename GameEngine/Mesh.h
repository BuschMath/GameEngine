#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm.hpp>

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

private:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned int> m_indices;
};

#endif // !MESH_H

