#include "../include/import_mtllib.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>


t_import_mtllib::t_import_mtllib(std::string path) {
    std::ifstream f(path); // TODO: add error handling.
    std::string line, word, name;

    while (std::getline(f, line)) {
        std::istringstream iss(line);
        while (iss >> word) {
            if (word.compare("newmtl") == 0) {
                iss >> name;
                t_material *p_material = new t_material(name);
                this->um_name_material.insert(std::make_pair(name, p_material));
            }
        }
    }
}

t_import_mtllib::~t_import_mtllib() {

}

t_material *t_import_mtllib::get_material(std::string name) {
    return this->um_name_material.at(name);
}

