#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include "vertex.h"
#include "face.h"


class t_mesh {
public:
    t_mesh(std::string path);
    ~t_mesh();
    void _copy_floats(float *arr1, float *arr2, size_t n);
    void print();

    std::vector<t_vertex> *get_vertices();
    std::vector<t_face> *get_faces();
    std::vector<unsigned int> *get_indices();

private:
    std::vector<t_vertex> v_vertices;
    std::vector<t_face> v_faces;
    std::vector<unsigned int> v_indices;
};

#endif // MESH_H

