#include "../include/image.h"
#include <iostream>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#endif // STB_IMAGE_IMPLEMENTATION


t_image::t_image(float *data, unsigned int width, unsigned int height, unsigned int channels) {
    this->width = width;
    this->height = height;
    this->channels = channels;
    this->transparency = false;

    if (data == NULL) {
        this->data = new float[width * height * channels]();
    }
    else {
        this->data = data;
        if (channels == 4) {
            std::cout << "4 channels" << std::endl;
            for (unsigned int i = channels - 1; i < (width * height * channels); i+=channels) {
                std::cout << "testing element " << i << std::endl;
                if (this->data[i] < 1.0) {
                    std::cout << "image has transparency" << std::endl;
                    this->transparency = true;
                }
            }
        }
    }
}

t_image::~t_image() {

}

float t_image::get_pixel(unsigned int x, unsigned int y, unsigned int c) {
    unsigned int i = c * this->channels + y * this->height + x * this->width;
    return this->data[i];
}

void t_image::set_pixel(float value, unsigned int x, unsigned int y, unsigned int c) {
    unsigned int i = c * this->channels + y * this->height + x * this->width;
    this->data[i] = value;
}

unsigned int t_image::get_width() {
    return this->width;
}

unsigned int t_image::get_height() {
    return this->height;
}

unsigned int t_image::get_channels() {
    return this->channels;
}

float *t_image::get_data() {
    return this->data;
}

bool t_image::has_transparency() {
    return this->transparency;
}

t_image *t_image::from_file(std::string path) {
    //stbi_set_flip_vertically_on_load(true);
    int width, height, channels;
    float *data = stbi_loadf(path.c_str(), &width, &height, &channels, 0);
    if (data == NULL) {
        std::cout << "error loading the image" << std::endl;
    }
    std::cout << path << ": width, height, channels: " << width << ", " << height << ", " << channels << std::endl;
    return new t_image(data, width, height, channels);
}
