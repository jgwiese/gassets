#include "../include/mesh.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>


t_mesh::t_mesh(std::vector<t_vertex> v_vertices, std::vector<t_face> v_faces) {
    this->v_vertices = v_vertices;
    this->v_faces = v_faces;

    for (unsigned int i = 0; i < v_faces.size(); i++) {
        this->v_indices.push_back(v_faces[i].vertex_indices.x);
        this->v_indices.push_back(v_faces[i].vertex_indices.y);
        this->v_indices.push_back(v_faces[i].vertex_indices.z);
    }

    /*
    this->p_obj = new t_obj(path);
    this->name = p_obj->name;
    this->material = p_obj->material;

    // TODO: add text in assertions
    for (unsigned int i = 0; i < p_obj->v_coordinates.size(); i++) {
        t_vertex vertex;
        this->v_vertices.push_back(vertex); // TODO: unsure whether this is actually vanishing data?

    }
    unsigned int coordinate_index, uv_index, normal_index;
    for (unsigned int i = 0; i < this->p_obj->v_face_indices.size(); i++) {
        t_face face;
        for (unsigned int j = 0; j < 3; j++) {
            coordinate_index = this->p_obj->v_face_indices[i].front[j].x - 1;
            uv_index = this->p_obj->v_face_indices[i].front[j].y - 1;
            normal_index = this->p_obj->v_face_indices[i].front[j].z - 1;
            this->v_indices.push_back(coordinate_index);
            
            this->v_vertices[coordinate_index].coordinates.x = p_obj->v_coordinates[coordinate_index].x;
            this->v_vertices[coordinate_index].coordinates.y = p_obj->v_coordinates[coordinate_index].y;
            this->v_vertices[coordinate_index].coordinates.z = p_obj->v_coordinates[coordinate_index].z;

            this->v_vertices[coordinate_index].normal.x = p_obj->v_normals[normal_index].x;
            this->v_vertices[coordinate_index].normal.y = p_obj->v_normals[normal_index].y;
            this->v_vertices[coordinate_index].normal.z = p_obj->v_normals[normal_index].z;

            this->v_vertices[coordinate_index].uv.x = p_obj->v_uvs[uv_index].x;
            this->v_vertices[coordinate_index].uv.y = 1.0 - p_obj->v_uvs[uv_index].y;
            
            face.vertex_indices[j] = coordinate_index;
            for (unsigned int k = 0; k < 3; k++) {
                face.normal[k] += 1.0 / 3.0 * this->v_vertices[coordinate_index].normal[k];
            }
        }
        this->v_faces.push_back(face);
    }
    */
}

t_mesh::~t_mesh() {

}

/*
void t_mesh::_copy_floats(float *arr1, float *arr2, size_t n) {
    for (int i = 0; i < n; i++) {
        arr1[i] = arr2[i];
    }
}
*/

std::vector<t_vertex> *t_mesh::get_vertices() {
    return &this->v_vertices;
}

std::vector<t_face> *t_mesh::get_faces() {
    return &this->v_faces;
}

std::vector<unsigned int> *t_mesh::get_indices() {
    return &this->v_indices;
}

