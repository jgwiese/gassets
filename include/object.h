#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include "mesh.h"
#include "material.h"


class t_object {
public:
    t_object(std::string name);
    void add_mesh_material(std::tuple<t_mesh *, assets::t_material *> mesh_material);
    std::vector<std::tuple<t_mesh *, assets::t_material *>> *get_mesh_material();
    std::string get_name();
    glm::vec3 get_center();
    void translate(glm::vec3);

private:
    std::string name;
    std::vector<std::tuple<t_mesh *, assets::t_material *>> v_mesh_material;
};

#endif // OBJECT_H

