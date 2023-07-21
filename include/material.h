#ifndef ASSETS_MATERIAl_H
#define ASSETS_MATERIAl_H

#include <string>
#include <glm/glm.hpp>
#include "image.h"

namespace assets {
    class t_material {
    public:
        t_material(std::string name, glm::vec3 kd, glm::vec3 ks, glm::vec3 ke, float ni, float d, float illum, float pr, float pm, float ps, float pc, float pcr, float aniso, float anisor, t_image *map_kd);
        ~t_material();
        std::string name;
        glm::vec3 kd, ks, ke;
        t_image *map_kd;
        float ni, d, illum, pr, pm, ps, pc, pcr, aniso, anisor;
        void print();

    private:

    };
}

#endif // ASSETS_MATERIAl_H
