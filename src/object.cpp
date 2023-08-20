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
glm::vec3 t_object::center() {
    glm::vec3 center(0.0);
    unsigned int counter = 0;
    t_mesh *p_mesh;
    assets::t_material *p_material;
    for (unsigned int i = 0; i < this->v_mesh_material.size(); i++) {
        std::tie(p_mesh, p_material) = this->v_mesh_material.at(i);
        center += (*p_mesh->get_center()) * (p_mesh->get_vertices()->size() * float(1.0));
        counter += p_mesh->get_vertices()->size();
        /*
        std::vector<t_vertex> *v_vertices = p_mesh->get_vertices();
        for (unsigned int j = 0; j < v_vertices->size(); j++) {
            center += v_vertices->at(j).coordinates;
            counter++;
        }
        */
    }
    center /= counter;
    translate(-center);
    return center;
}

void t_object::translate(glm::vec3 v) {
    t_mesh *p_mesh;
    assets::t_material *p_material;
    for (unsigned int i = 0; i < this->v_mesh_material.size(); i++) {
        std::tie(p_mesh, p_material) = this->v_mesh_material.at(i);
        p_mesh->translate(v);
    }
}
