#include "../include/face.h"


t_face::t_face() {

}

t_face::t_face(glm::ivec3 vertex_indices, glm::vec3 normal) {
    this->vertex_indices.x = vertex_indices.x;
    this->vertex_indices.y = vertex_indices.y;
    this->vertex_indices.z = vertex_indices.z;
    this->normal.x = normal.x;
    this->normal.y = normal.y;
    this->normal.z = normal.z;
}

t_face::~t_face() {
    
}

