#ifndef OBJ_IMPORT_H
#define OBJ_IMPORT_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "vertex.h"
#include "face.h"
#include "object.h"


enum obj_line_type {
    NONE,
    NAME,
    COORDINATES,
    NORMAL,
    UV,
    MATERIAL,
    FACE
};

class t_obj_import {
public:
    t_obj_import(std::string path);
    ~t_obj_import();

private:
    std::vector<t_object *> v_objects;
    std::vector<t_material *> v_materials;

    void *_parse_ints(char *str, size_t size);
    void *_parse_floats(char *str, size_t size);
    void *_parse_line(char *line, enum obj_line_type *type);
};

#endif // OBJ_IMPORT_H

