#include "../include/object.h"
#include <iostream>


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

