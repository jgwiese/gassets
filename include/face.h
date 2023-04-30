#ifndef FACE_H
#define FACE_H

#include <glm/glm.hpp>

class t_face {
public:
    glm::ivec3 vertex_indices; // TODO: actually this is a bit strange, because it should have vertex positions for reusability.
    glm::vec3 normal;
    t_face();
    t_face(glm::ivec3 *vertex_indices, glm::vec3 *normal);
    ~t_face();
};

#endif // FACE_H

