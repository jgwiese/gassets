#ifndef IMPORT_MTLLIB_H
#define IMPORT_MTLLIB_H

#include <vector>
#include <string>
#include <unordered_map>
#include "material.h"


class t_import_mtllib {
public:
    t_import_mtllib(std::string path);
    ~t_import_mtllib();
    void reset_values();
    assets::t_material *get_material(std::string name);

private:
    std::unordered_map<std::string, assets::t_material *> um_name_material;
    std::string name;
    glm::vec3 kd, ks, ke;
    t_image *map_kd;
    float ni, d, illum, pr, pm, ps, pc, pcr, aniso, anisor;
};

#endif // IMPORT_MTLLIB_H

