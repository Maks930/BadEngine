#include <GL/glew.h>

#include <Mesh/mesh.h>

#include <iostream>

Vertex::Vertex(glm::vec3 pos, glm::vec3 normal, glm::vec2 uv) : 
    position(pos), normal(normal), texCoord(uv)
{}

Vertex::Vertex(glm::vec3 pos) :
    position(pos), normal(0), texCoord(0)
{}

Mesh::Mesh(std::vector<float> vertices, size_t vertCount, std::vector<uint32_t> elements, std::vector<int32_t> attr) :
    m_vertices(vertCount), m_indices(elements.size())
{

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices*sizeof(uint32_t), elements.data(), GL_STATIC_DRAW); //NOTE: maybe this bug


    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW); //NOTE: maybe this bug

    int offset = 0;
    for (int i = 0; i < attr.size(); ++i) {

        //TODO: delete me or replace logger

        // std::cout << "glVertexAttribPointer(" << (int)i << ", "
        //           << (int)attr.at(i) << ", GL_FLOAT, GL_FALSE, "
        //           << (int)vertices.size()/sizeof(float)
        //           << " * sizeof(GLfloat), (GLvoid*)("
        //           << (int)offset << " * sizeof(GLfloat))\n";


        // WARNING: ONLY 3 vertices, remplace me on dynamic, add to construct
        glVertexAttribPointer(
            i,
            attr.at(i),
            GL_FLOAT,
            GL_FALSE,
            m_vertices * sizeof(GLfloat),
            (GLvoid*)(offset * sizeof(GLfloat))
            );
        glEnableVertexAttribArray(i);
        offset += attr[i];
    }
    glBindVertexArray(0);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> elements, std::vector<int32_t> attr) :
    m_indices(elements.size())
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices*sizeof(uint32_t), elements.data(), GL_STATIC_DRAW); //NOTE: maybe this bug


    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    //TODO: rewrite to new format
    // glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(float), vertices.data(), GL_STATIC_DRAW); //NOTE: maybe this bug


    int offset = 0;
    for (int i = 0; i < attr.size(); ++i) {
        glVertexAttribPointer(
            i,
            attr.at(i),
            GL_FLOAT,
            GL_FALSE,
            m_vertices * sizeof(GLfloat),
            (GLvoid*)(offset * sizeof(GLfloat))
            );
        glEnableVertexAttribArray(i);
        offset += attr[i];
    }
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

void Mesh::draw(uint32_t primitive)
{

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glDrawElements(primitive, m_indices, GL_UNSIGNED_INT, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

}
