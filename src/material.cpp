#include "../include/material.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>


t_material::t_material(std::string name, glm::vec3 kd, glm::vec3 ks, glm::vec3 ke, float ni, float d, float illum, float pr, float pm, float ps, float pc, float pcr, float aniso, float anisor) {
    this->name = name;
    this->kd = kd;
    this->ks = ks;
    this->ke = ke;
    this->ni = ni;
    this->d = d;
    this->illum = illum;
    this->pr = pr;
    this->pm = pm;
    this->ps = ps;
    this->pc = pc;
    this->pcr = pcr;
    this->aniso = aniso;
    this->anisor = anisor;
}

t_material::~t_material() {

}

void t_material::print() {
    std::cout << name << std::endl;
    std::cout << "kd " << glm::to_string(this->kd) << std::endl;
    std::cout << "ks " << glm::to_string(this->ks) << std::endl;
    std::cout << "ke " << glm::to_string(this->ke) << std::endl;
    std::cout << "ni " << this->ni << std::endl;
    std::cout << "d " << this->d << std::endl;
    std::cout << "illum " << this->illum << std::endl;
    std::cout << "pr " << this->pr << std::endl;
    std::cout << "pm " << this->pm << std::endl;
    std::cout << "ps " << this->ps << std::endl;
    std::cout << "pc " << this->pc << std::endl;
    std::cout << "pcr " << this->pcr << std::endl;
    std::cout << "aniso " << this->aniso << std::endl;
    std::cout << "anisor " << this->anisor << std::endl;
}
