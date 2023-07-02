#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "vertex.h"
#include "face.h"


class t_mesh {
public:
    t_mesh(std::vector<t_vertex> v_vertices, std::vector<t_face> v_faces, bool flat_shading);
    ~t_mesh();
    //void _copy_floats(float *arr1, float *arr2, size_t n);
    void print();

    bool get_flat_shading();
    std::vector<t_vertex> *get_vertices();
    std::vector<t_face> *get_faces();
    std::vector<unsigned int> *get_indices();

private:
    bool flat_shading;
    std::vector<t_vertex> v_vertices;
    std::vector<t_face> v_faces; // TODO: currently not in use
    std::vector<unsigned int> v_indices;
};

#endif // MESH_H

