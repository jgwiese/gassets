#include "../include/vertex.h"

t_vertex::t_vertex() {

}

t_vertex::t_vertex(glm::vec3 coordinates, glm::vec3 normal, glm::vec2 uv) {
    this->coordinates.x = coordinates.x;
    this->coordinates.y = coordinates.y;
    this->coordinates.z = coordinates.z;

    this->normal.x = normal.x;
    this->normal.y = normal.y;
    this->normal.z = normal.z;

    this->uv.x = uv.x;
    this->uv.y = uv.y;
}

t_vertex::~t_vertex() {
    
}

