#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>


class t_vertex {
public:
    glm::vec3 coordinates;
    glm::vec3 normal;
    glm::vec2 uv;
    t_vertex();
    t_vertex(glm::vec3 coordinates, glm::vec3 normal, glm::vec2 uv);
    ~t_vertex();
};

#endif // VERTEX_H

