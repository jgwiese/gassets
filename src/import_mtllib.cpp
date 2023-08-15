#include "../include/import_mtllib.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "../include/image.h"


t_import_mtllib::t_import_mtllib(std::string path) {
    std::cout << "import mtllib" << std::endl;
    std::string base_path;
    size_t last = 0;
    size_t next = 0;
    while ((next = path.find('/', last)) != std::string::npos) {
        base_path = path.substr(0, next);
        last = next + 1;
    }

    std::ifstream f(path); // TODO: add error handling.
    std::string line, word, fname;
    float x, y, z;
    reset_values();

    while (std::getline(f, line)) {
        std::istringstream iss(line);
        while (iss >> word) {
            if (word.compare("newmtl") == 0) {
                if (this->name != "") {
                    assets::t_material *p_material = new assets::t_material(this->name, kd, ks, ke, ni, d, illum, pr, pm, ps, pc, pcr, aniso, anisor, map_kd, map_ks);
                    this->um_name_material.insert(std::make_pair(this->name, p_material));
                    std::cout << "new material added" << std::endl;
                    p_material->print();
                    std::cout << std::endl;
                    reset_values();
                }
                iss >> this->name;
            }
            if (word.compare("Kd") == 0) {
                iss >> x >> y >> z;
                this->kd = {x, y, z};
                break;
            }
            if (word.compare("map_Kd") == 0) {
                iss >> fname;
                std::string fpath = base_path + '/' + fname;
                this->map_kd = t_image::from_file(fpath);
                break;
            }
            if (word.compare("map_Ks") == 0) {
                iss >> fname;
                std::string fpath = base_path + '/' + fname;
                this->map_ks = t_image::from_file(fpath);
                break;
            }
            if (word.compare("Ks") == 0) {
                iss >> x >> y >> z;
                this->ks = {x, y, z};
                break;
            }
            if (word.compare("Ke") == 0) {
                iss >> x >> y >> z;
                this->ke = {x, y, z};
                break;
            }
            if (word.compare("Ni") == 0) {
                iss >> x;
                this->ni = x;
                break;
            }
            if (word.compare("d") == 0) {
                iss >> x;
                this->d = x;
                break;
            }
            if (word.compare("illum") == 0) {
                iss >> x;
                this->illum = x;
                break;
            }
            if (word.compare("Pr") == 0) {
                iss >> x;
                this->pr = x;
                break;
            }
            if (word.compare("Pm") == 0) {
                iss >> x;
                this->pm = x;
                break;
            }
            if (word.compare("Ps") == 0) {
                iss >> x;
                this->ps = x;
                break;
            }
            if (word.compare("Pc") == 0) {
                iss >> x;
                this->pc = x;
                break;
            }
            if (word.compare("Pcr") == 0) {
                iss >> x;
                this->pcr = x;
                break;
            }
            if (word.compare("aniso") == 0) {
                iss >> x;
                this->aniso = x;
                break;
            }
            if (word.compare("anisor") == 0) {
                iss >> x;
                this->anisor = x;
                break;
            }
        }
    }
    //if (this->name != "") {
    if (true) {
        if (this->name == "") {
            this->name = "default";
        }
        assets::t_material *p_material = new assets::t_material(this->name, kd, ks, ke, ni, d, illum, pr, pm, ps, pc, pcr, aniso, anisor, map_kd, map_ks);
        this->um_name_material.insert(std::make_pair(this->name, p_material));
        std::cout << "new material added" << std::endl;
        p_material->print();
        std::cout << std::endl;
        reset_values();
    }
}

t_import_mtllib::~t_import_mtllib() {

}

void t_import_mtllib::reset_values() {
    this->name = "";
    this->kd = {0.0, 0.0, 0.0};
    this->map_kd = NULL;
    this->map_ks = NULL;
    this->ks = {0.0, 0.0, 0.0};
    this->ke = {0.0, 0.0, 0.0};
    this->d = 0.0;
    this->illum = 0.0;
    this->pr = 0.0;
    this->pm = 0.0;
    this->ps = 0.0;
    this->pc = 0.0;
    this->pcr = 0.0;
    this->aniso = 0.0;
    this->anisor = 0.0;
}

assets::t_material *t_import_mtllib::get_material(std::string name) {
    return this->um_name_material.at(name);
}

