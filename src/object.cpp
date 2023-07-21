#include "../include/object.h"
#include <iostream>

/*
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
*/


t_object::t_object(std::string name) {
    this->name = name;
}

void t_object::add_mesh_material(std::tuple<t_mesh *, assets::t_material *> mesh_material) {
    this->v_mesh_material.push_back(mesh_material);
}

std::vector<std::tuple<t_mesh *, assets::t_material *>> *t_object::get_mesh_material() {
    return &this->v_mesh_material;
}

std::string t_object::get_name() {
    return this->name;
}

