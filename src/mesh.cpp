#include "../include/mesh.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>


t_mesh::t_mesh(std::vector<t_vertex> v_vertices, std::vector<t_face> v_faces, bool flat_shading) {
    this->flat_shading = flat_shading;
    this->v_vertices = v_vertices;
    this->v_faces = v_faces;

    for (unsigned int i = 0; i < v_faces.size(); i++) {
        this->v_indices.push_back(v_faces[i].vertex_indices.x);
        this->v_indices.push_back(v_faces[i].vertex_indices.y);
        this->v_indices.push_back(v_faces[i].vertex_indices.z);
    }
    this->calculate_center();
}

t_mesh::~t_mesh() {

}

bool t_mesh::get_flat_shading() {
    return this->flat_shading;
}

std::vector<t_vertex> *t_mesh::get_vertices() {
    return &this->v_vertices;
}

std::vector<t_face> *t_mesh::get_faces() {
    return &this->v_faces;
}

std::vector<unsigned int> *t_mesh::get_indices() {
    return &this->v_indices;
}

void t_mesh::translate(glm::vec3 v) {
    std::vector<t_vertex> *v_vertices = this->get_vertices();
    for (unsigned int j = 0; j < v_vertices->size(); j++) {
        v_vertices->at(j).coordinates += v;
    }
}

glm::vec3 *t_mesh::get_center() {
    return &this->center;
}

void t_mesh::calculate_center() {
    for (unsigned int i = 0; i < this->get_vertices()->size(); i++) {
        this->center += this->get_vertices()->at(i).coordinates;
    }
    this->center /= this->get_vertices()->size();
}
