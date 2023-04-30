#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <glm/glm.hpp>
#include "mesh.h"
#include "material.h"


class t_face_indices {
public:
    glm::ivec3 front[3];

    t_face_indices();
    t_face_indices(glm::ivec3 front[3]);
    ~t_face_indices();
};


class t_object {
public:
    t_object();

private:
    std::string name;
    std::vector<glm::vec3> v_coordinates;
    std::vector<glm::vec3> v_normals;
    std::vector<glm::vec2> v_uvs;
    std::vector<t_face_indices> v_face_indices;

    std::vector<t_mesh *> v_meshes;
    std::vector<t_material *> v_materials;
};

#endif // OBJECT_H

