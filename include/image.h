#ifndef IMAGE_H
#define IMAGE_H

#include <string>


class t_image {
public:
    t_image(float *data, unsigned int width, unsigned int height, unsigned int channels);
    ~t_image();
    float get_pixel(unsigned int x, unsigned int y, unsigned int c);
    void set_pixel(float value, unsigned int x, unsigned int y, unsigned int c);
    unsigned int get_width();
    unsigned int get_height();
    unsigned int get_channels();
    float *get_data();
    static t_image *from_file(std::string path);

private:
    unsigned int width, height, channels;
    float *data;
};

#endif // IMAGE_H
