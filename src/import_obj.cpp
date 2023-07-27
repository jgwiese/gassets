#include "../include/import_obj.h"
#include <glm/common.hpp>
#include <iostream>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>
#include "../include/object.h"
#include "../include/import_mtllib.h"


template <typename Out>
void split(const std::string &s, char delim, Out result) {
    std::istringstream iss(s);
    std::string item;
    while (std::getline(iss, item, delim)) {
        *result++ = item;
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}


std::string join(std::vector<std::string> words, char delim) {
    std::string result = "";
    for (int i = 0; i < words.size() - 1; i++) {
        result += words[i] + delim;
    }
    return result + words.at(words.size() - 1);
}


t_import_obj::t_import_obj(std::string path) {
    std::ifstream f(path); // TODO: add error handling.
    std::string line, word, name;

    std::vector<glm::vec3> coordinates;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;
    float x, y, z;

    //std::vector<t_vertex> *vertices;
    std::vector<t_vertex> v_vertices;
    std::vector<glm::ivec3> v_vertex_indices; // coordinates_i, normal_i, uv_i
    std::vector<t_face> faces;

    t_mesh *p_mesh = NULL;
    assets::t_material *p_material = NULL;
    t_import_mtllib *p_import_mtllib = NULL;
    t_object *p_object = NULL;
    bool flat_shading = false;

    while (std::getline(f, line)) {
        std::istringstream iss(line);
        while (iss >> word) {
            if (word.compare("mtllib") == 0) {
                iss >> name;
                std::vector<std::string> tmp = split(path, '/');
                tmp.pop_back();
                tmp.push_back(name);
                std::string path_mtllib = join(tmp, '/');
                p_import_mtllib = new t_import_mtllib(path_mtllib);
                break;
            }
            if (word.compare("o") == 0) {
                if (p_object != NULL) {
                    if (faces.size() > 0) {
                        // create mesh
                        p_mesh = new t_mesh(v_vertices, faces, flat_shading);
                        faces.clear();

                        // add tuple to object
                        p_object->add_mesh_material(std::make_tuple(p_mesh, p_material));
                    }
                    this->v_objects.push_back(p_object);
                    p_mesh = NULL;
                    p_material = NULL;
                }

                v_vertices.clear();
                v_vertex_indices.clear();
                faces.clear();
                
                // create new object
                if (iss >> name) 
                    p_object = new t_object(name);
                else
                    p_object = new t_object("object_" + std::to_string(this->v_objects.size()));
                
                break;
            }
            if (word.compare("s") == 0) {
                iss >> name;
                if ((name == "off") || (std::stoi(name) == 0)) {
                    flat_shading = false;
                }
                else {
                    flat_shading = true;
                }
            }
            if (word.compare("v") == 0) {
                iss >> x >> y >> z;
                coordinates.push_back(glm::vec3(-x, y, -z));
                break;
            }
            if (word.compare("vn") == 0) {
                iss >> x >> y >> z;
                normals.push_back(glm::vec3(x, y, z));
                break;
            }
            if (word.compare("vt") == 0) {
                iss >> x >> y;
                glm::vec2 vt = glm::vec2(x, y);
                uvs.push_back(vt);
                break;
            }
            if (word.compare("usemtl") == 0) {
                if (faces.size() > 0) {
                    // create mesh
                    p_mesh = new t_mesh(v_vertices, faces, flat_shading);
                    faces.clear();

                    // add tuple to object
                    p_object->add_mesh_material(std::make_tuple(p_mesh, p_material));
                }

                v_vertices.clear();
                v_vertex_indices.clear();

                // set current material
                iss >> name;
                p_material = p_import_mtllib->get_material(name);
                break;
            }
            if (word.compare("f") == 0) {
                std::vector<unsigned int> indices_clean;
                while (iss >> word) {
                    int last_pos = 0;
                    int current_pos = 0;
                    std::vector<std::string> vertex_indices_string = split(word, '/');

                    unsigned int coordinates_i = std::stoi(vertex_indices_string[0]) - 1;
                    unsigned int normal_i = std::stoi(vertex_indices_string[2]) - 1;
                    unsigned int uv_i = std::stoi(vertex_indices_string[1]) - 1;
                    std::vector<glm::ivec3>::iterator it = std::find_if(v_vertex_indices.begin(), v_vertex_indices.end(), [&coordinates_i, &uv_i, &normal_i] (const glm::ivec3 &v) {return (coordinates_i == v.x) && (uv_i == v.z) && (normal_i == v.y);});
                    unsigned int index = std::distance(v_vertex_indices.begin(), it);
                    indices_clean.push_back(index);
                    if (it == v_vertex_indices.end()) {
                        v_vertex_indices.push_back(glm::ivec3(coordinates_i, normal_i, uv_i));
                        v_vertices.push_back(t_vertex(coordinates.at(coordinates_i),normals.at(normal_i), uvs.at(uv_i)));
                    }
                }
                // create face
                t_vertex *v1, *v2, *v3;
                v1 = &v_vertices[indices_clean[0]];
                v2 = &v_vertices[indices_clean[1]];
                v3 = &v_vertices[indices_clean[2]];

                // TODO: how to multiply/divide a glm vector simply?
                glm::vec3 face_normal(
                    (v1->normal.x + v2->normal.x + v3->normal.x) / 3.0,
                    (v1->normal.y + v2->normal.y + v3->normal.y) / 3.0,
                    (v1->normal.z + v2->normal.z + v3->normal.z) / 3.0
                );
                t_face face(glm::ivec3(indices_clean[0], indices_clean[1], indices_clean[2]), face_normal);
                faces.push_back(face);
                break;
            }
        }
    }

    // add last object
    if (p_object != NULL) {
        if (faces.size() > 0) {
            // create mesh

            p_mesh = new t_mesh(v_vertices, faces, flat_shading);
            v_vertices.clear();
            v_vertex_indices.clear();
            faces.clear();

            // add tuple to object
            p_object->add_mesh_material(std::make_tuple(p_mesh, p_material));
        }
        this->v_objects.push_back(p_object);
        p_mesh = NULL;
        p_material = NULL;
    }
}

t_import_obj::~t_import_obj() {
    std::cout << "t_import_obj destructor" << std::endl;
}

std::vector<t_object *> *t_import_obj::get_objects() {
    return &this->v_objects;
}
