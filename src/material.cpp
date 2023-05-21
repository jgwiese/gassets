#include "../include/material.h"


t_material::t_material(std::string name) {
    this->name = name;
}

t_material::~t_material() {

}

std::string t_material::get_name() {
    return this->name;
}

