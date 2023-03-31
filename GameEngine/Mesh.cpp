#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
    : m_vertices(vertices), m_indices(indices)
{
}

const std::vector<Mesh::Vertex>& Mesh::getVertices() const
{
    return m_vertices;
}

const std::vector<unsigned int>& Mesh::getIndices() const
{
    return m_indices;
}
