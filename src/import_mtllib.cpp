#include "../include/import_mtllib.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


t_import_mtllib::t_import_mtllib(std::string path) {
    std::cout << "import mtllib" << std::endl;
    std::ifstream f(path); // TODO: add error handling.
    std::string line, word;
    float x, y, z;
    reset_values();

    while (std::getline(f, line)) {
        std::istringstream iss(line);
        while (iss >> word) {
            if (word.compare("newmtl") == 0) {
                if (name != "") {
                    t_material *p_material = new t_material(name, kd, ks, ke, ni, d, illum, pr, pm, ps, pc, pcr, aniso, anisor);
                    this->um_name_material.insert(std::make_pair(name, p_material));
                    std::cout << "new material added" << std::endl;
                    p_material->print();
                    std::cout << std::endl;
                    reset_values();
                }
                iss >> name;
            }
            if (word.compare("Kd") == 0) {
                iss >> x >> y >> z;
                this->kd = {x, y, z};
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
    if (name != "") {
        t_material *p_material = new t_material(name, kd, ks, ke, ni, d, illum, pr, pm, ps, pc, pcr, aniso, anisor);
        this->um_name_material.insert(std::make_pair(name, p_material));
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

t_material *t_import_mtllib::get_material(std::string name) {
    return this->um_name_material.at(name);
}

