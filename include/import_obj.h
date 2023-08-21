#ifndef IMPORT_OBJ_H
#define IMPORT_OBJ_H

#include <string>
#include <vector>
#include <glm/glm.hpp>
#include "vertex.h"
#include "face.h"
#include "object.h"


class t_import_obj {
public:
    t_import_obj(std::string path);
    ~t_import_obj();
    std::vector<t_object *> *get_objects();

private:
    std::vector<t_object *> v_objects;
};

#endif // IMPORT_OBJ_H
