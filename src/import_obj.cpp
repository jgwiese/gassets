#include "../include/import_obj.h"
#include <iostream>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iterator>
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

    std::vector<t_vertex> vertices;
    std::vector<t_face> faces;

    t_mesh *p_mesh = NULL;
    t_material *p_material = NULL;
    t_import_mtllib *p_import_mtllib = NULL;
    t_object *p_object = NULL;

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
                        p_mesh = new t_mesh(vertices, faces);
                        vertices.clear();
                        faces.clear();

                        // add tuple to object
                        p_object->add_mesh_material(std::make_tuple(p_mesh, p_material));
                    }
                    this->v_objects.push_back(p_object);
                    p_mesh = NULL;
                    p_material = NULL;
                }

                coordinates.clear();
                normals.clear();
                uvs.clear();

                vertices.clear();
                faces.clear();
                
                // create new object
                if (iss >> name) 
                    p_object = new t_object(name);
                else
                    p_object = new t_object("object_" + std::to_string(this->v_objects.size()));
                
                break;
            }
            if (word.compare("v") == 0) {
                iss >> x >> y >> z;
                coordinates.push_back(glm::vec3(x, y, z));
                break;
            }
            if (word.compare("vn") == 0) {
                iss >> x >> y >> z;
                normals.push_back(glm::vec3(x, y, z));
                break;
            }
            if (word.compare("vt") == 0) {
                iss >> x >> y;
                uvs.push_back(glm::vec2(x, y));
                break;
            }
            if (word.compare("usemtl") == 0) {
                if (faces.size() > 0) {
                    // create mesh
                    p_mesh = new t_mesh(vertices, faces);
                    vertices.clear();
                    faces.clear();

                    // add tuple to object
                    p_object->add_mesh_material(std::make_tuple(p_mesh, p_material));
                }

                // set current material
                iss >> name;
                p_material = p_import_mtllib->get_material(name);
                break;
            }
            if (word.compare("f") == 0) {
                while (iss >> word) {
                    int last_pos = 0;
                    int current_pos = 0;
                    std::vector<std::string> vertex_indices_string = split(word, '/');

                    t_vertex vertex(
                        coordinates[std::stoi(vertex_indices_string[0])],
                        normals[std::stoi(vertex_indices_string[1])],
                        uvs[std::stoi(vertex_indices_string[2])]
                    );
                    vertices.push_back(vertex);
                }
                // create face
                int size = vertices.size();
                t_vertex *v1, *v2, *v3;
                v1 = &vertices[size - 2];
                v2 = &vertices[size - 1];
                v3 = &vertices[size];

                // TODO: how to multiply/divide a glm vector simply?
                glm::vec3 face_normal(
                    (v1->normal.x + v2->normal.x + v3->normal.x) / 3.0,
                    (v1->normal.y + v2->normal.y + v3->normal.y) / 3.0,
                    (v1->normal.z + v2->normal.z + v3->normal.z) / 3.0
                );
                t_face face(glm::ivec3(size - 2, size - 1, size), face_normal);
                faces.push_back(face);
                break;
            }
        }
    }

    // add last object
    if (p_object != NULL) {
        if (faces.size() > 0) {
            // create mesh
            p_mesh = new t_mesh(vertices, faces);
            vertices.clear();
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

/*
void *t_import_obj::_parse_line(char *line, enum obj_line_type *type) {
    char *line_copy = line;
    char *token = NULL;
    void *buffer = NULL;
    if (line_copy != NULL) {
        token = strsep(&line_copy, " \n");
        if (strcmp(token, "o") == 0) {
            *type = NAME;
            token = strsep(&line_copy, " \n");
            buffer = calloc(strlen(token), sizeof(char));
            strcpy((char *) buffer, token);
        }
        else if (strcmp(token, "v") == 0) {
            *type = COORDINATES;
            buffer = _parse_floats(line_copy, 3);
        }
        else if (strcmp(token, "vn") == 0) {
            *type = NORMAL;
            buffer = _parse_floats(line_copy, 3);
        }
        else if (strcmp(token, "vt") == 0) {
            *type = UV;
            buffer = _parse_floats(line_copy, 2);
        }
        else if (strcmp(token, "mtllib") == 0) {
            *type = MATERIAL;
            token = strsep(&line_copy, " \n");
            buffer = calloc(strlen(token) + 1, sizeof(char));
            strcpy((char *) buffer, token);
        }
        else if (strcmp(token, "f") == 0) {
            *type = FACE;
            buffer = _parse_ints(line_copy, 9);
        }
    }
    return buffer;
}
*/

