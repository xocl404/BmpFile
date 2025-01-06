#ifndef LABWORK3_XOCL404_BMP_H
#define LABWORK3_XOCL404_BMP_H

#include "parsing.h"
#include "sandpile.h"
#include <fstream>
#include <string>
#include <cstring>
#include <cstdint>

struct Bmp {
    char signature[2]{'B', 'M'};
    uint32_t size_of_header = 14;
    uint32_t size_of_file;
    uint32_t location_of_raster_data;
    uint16_t length_x;
    uint16_t length_y;
    uint32_t size_of_table_of_colors = 20;
    uint8_t reserved[4]{0, 0, 0, 0};
    uint32_t size_of_information_header = 40;
    uint8_t planes[2]{1, 0};
    uint8_t bits_per_pixel[2]{4, 0};
    uint8_t compression[4]{0, 0, 0, 0};
    uint8_t raster_data_size[4]{0, 0, 0, 0};
    int8_t horizontal_resolution[4]{0, 0, 0, 0};
    int8_t vertical_resolution[4]{0, 0, 0, 0};
    uint8_t colors[4]{5, 0, 0, 0};
    uint8_t important_colors[4]{5, 0, 0, 0};
};

struct Color {
    uint8_t white[4]{255, 255, 255, 255};
    uint8_t green[4]{0, 255, 0, 255};
    uint8_t yellow[4]{0, 255, 255, 255};
    uint8_t purple[4]{255, 13, 171, 255};
    uint8_t black[4]{0, 0, 0, 255};
};

void CreatingBmpFile (char* bmppath, uint64_t** &matrix, Size &size, uint64_t number_of_picture, Bmp &bmp, Color &color);

#endif //LABWORK3_XOCL404_BMP_H
