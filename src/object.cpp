#include "../include/object.h"


t_face_indices::t_face_indices(glm::ivec3 front[3]) {
    for (unsigned int i = 0; i < 3; i++) {
        this->front[i].x = front[i].x;
        this->front[i].y = front[i].y;
        this->front[i].z = front[i].z;
    }
}

t_face_indices::t_face_indices() {
    
}

t_face_indices::~t_face_indices() {
    
}

