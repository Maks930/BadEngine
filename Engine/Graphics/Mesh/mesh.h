#ifndef MESH_H
#define MESH_H

#include <vector>

#include <Types/Types.h>
#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;

    Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 uv);
    Vertex(glm::vec3 pos);
};


class Mesh
{
private:
    uint32_t m_vao;
    uint32_t m_vbo;
    uint32_t m_ebo;

    size_t m_vertices;
    size_t m_indices;

public:
    Mesh(std::vector<float> vertices, size_t vertCount, std::vector<uint32_t> elements, std::vector<int32_t> attr);
    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> elements, std::vector<int32_t> attr = {0});
    ~Mesh();

    void draw(uint32_t primitive);
};

#endif // MESH_H
