#include "../include/image.h"
#include <iostream>


t_image::t_image(float *data, unsigned int width, unsigned int height, unsigned int channels) {
    if (data == NULL) 
        this->data = new float[width * height * channels]();
    else
        this->data = data;

    this->width = width;
    this->height = height;
    this->channels = channels;
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
