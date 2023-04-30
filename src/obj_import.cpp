#include "../include/obj_import.h"
#include <iostream>
#include <glm/ext.hpp>
#include <glm/gtx/string_cast.hpp>
#include <fstream>
#include <iostream>
#include <sstream>


t_obj_import::t_obj_import(std::string path) {
    std::ifstream f(path); // TODO: add error handling.
    std::string line, word;

    while (std::getline(f, line)) {
        std::istringstream iss(line);
        while (iss >> word) {
            if (word.compare("o") == 0) {
                std::cout << "found an object" << std::endl;
            }
        }
    }
}

t_obj_import::~t_obj_import() {
    std::cout << "t_obj_import destructor" << std::endl;
}

void *t_obj_import::_parse_ints(char *str, size_t size) {
    int *buffer = (int *) calloc(size, sizeof(int));
    char *token;
    for (int i = 0; i < size; i++) {
        token = strsep(&str, " \n/");
        buffer[i] = atoi(token);
    }
    return (void *) buffer;
}

void *t_obj_import::_parse_floats(char *str, size_t size) {
    float *buffer = (float *) calloc(size, sizeof(float));
    char *token;
    for (int i = 0; i < size; i++) {
        token = strsep(&str, " \n/");
        buffer[i] = atof(token);
    }
    return (void *) buffer;
}

void *t_obj_import::_parse_line(char *line, enum obj_line_type *type) {
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

