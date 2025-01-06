#include "bmp.h"

void CreatingBmpFile (char* bmppath, uint64_t** &matrix, Size &size, uint64_t number_of_picture, Bmp &bmp, Color &color) {

    std::string bmpfilename = static_cast<std::string>(bmppath) + "/BmpPicture_" + std::to_string(number_of_picture) + ".bmp";
    std::ofstream file(bmpfilename, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "ERROR: file not created: " << bmpfilename << std::endl;

        exit(1);
    }

    uint8_t writing_mas[4];
    bmp.length_x = size.length_x;
    bmp.length_y = size.length_y;

    file << bmp.signature[0] << bmp.signature[1];

    bmp.size_of_file = bmp.size_of_header + bmp.size_of_information_header + bmp.size_of_table_of_colors + (bmp.length_x * bmp.length_y) / 2;
    writing_mas[0] = bmp.size_of_file;
    writing_mas[1] = bmp.size_of_file >> 8;
    writing_mas[2] = bmp.size_of_file >> 16;
    writing_mas[3] = bmp.size_of_file >> 24;
    file << writing_mas[0] << writing_mas[1] << writing_mas[2] << writing_mas[3];

    file << bmp.reserved[0] << bmp.reserved[1] << bmp.reserved[2] << bmp.reserved[3];

    bmp.location_of_raster_data = bmp.size_of_header + bmp.size_of_information_header + bmp.size_of_table_of_colors;
    writing_mas[0] = bmp.location_of_raster_data;
    writing_mas[1] = bmp.location_of_raster_data >> 8;
    writing_mas[2] = bmp.location_of_raster_data >> 16;
    writing_mas[3] = bmp.location_of_raster_data >> 24;
    file << writing_mas[0] << writing_mas[1] << writing_mas[2] << writing_mas[3];

    writing_mas[0] = bmp.size_of_information_header;
    writing_mas[1] = bmp.size_of_information_header >> 8;
    writing_mas[2] = bmp.size_of_information_header >> 16;
    writing_mas[3] = bmp.size_of_information_header >> 24;
    file << writing_mas[0] << writing_mas[1] << writing_mas[2] << writing_mas[3];

    writing_mas[0] = bmp.length_x;
    writing_mas[1] = bmp.length_x >> 8;
    writing_mas[2] = 0;
    writing_mas[3] = 0;
    file << writing_mas[0] << writing_mas[1] << writing_mas[2] << writing_mas[3];

    writing_mas[0] = bmp.length_y;
    writing_mas[1] = bmp.length_y >> 8;
    writing_mas[2] = 0;
    writing_mas[3] = 0;
    file << writing_mas[0] << writing_mas[1] << writing_mas[2] << writing_mas[3];

    file << bmp.planes[0] << bmp.planes[1];

    file << bmp.bits_per_pixel[0] << bmp.bits_per_pixel[1];

    file << bmp.compression[0] << bmp.compression[1] << bmp.compression[2] << bmp.compression[3];

    file << bmp.raster_data_size[0] << bmp.raster_data_size[1] << bmp.raster_data_size[2] << bmp.raster_data_size[3];

    file << bmp.horizontal_resolution[0] << bmp.horizontal_resolution[1] << bmp.horizontal_resolution[2] << bmp.horizontal_resolution[3];

    file << bmp.vertical_resolution[0] << bmp.vertical_resolution[1] << bmp.vertical_resolution[2] << bmp.vertical_resolution[3];

    file << bmp.colors[0] << bmp.colors[1] << bmp.colors[2] << bmp.colors[3];

    file << bmp.important_colors[0] << bmp.important_colors[1] << bmp.important_colors[2] << bmp.important_colors[3];

    file << color.white[0] << color.white[1] << color.white[2] << color.white[3];

    file << color.green[0] << color.green[1] << color.green[2] << color.green[3];

    file << color.yellow[0] << color.yellow[1] << color.yellow[2] << color.yellow[3];

    file << color.purple[0] << color.purple[1] << color.purple[2] << color.purple[3];

    file << color.black[0] << color.black[1] << color.black[2] << color.black[3];

    uint8_t first_pixel;
    uint8_t second_pixel;
    uint8_t writing_pixel;

    if (bmp.length_x % 8 != 0) {
        bmp.length_x = bmp.length_x + 8 - bmp.length_x % 8;
    }
    for (int y = 0; y < bmp.length_y; ++y) {
        for (uint16_t x = 0; x < bmp.length_x; x += 2) {
            if (x >= size.length_x) {
                first_pixel = 0;
                second_pixel = 0;
            } else if (x + 1 >= size.length_x) {
                if (matrix[x][y] > 4) {
                    first_pixel = 4;
                } else {
                    first_pixel = matrix[x][y];
                }
                second_pixel = 0;
            } else {
                if (matrix[x][y] > 4) {
                    first_pixel = 4;
                } else {
                    first_pixel = matrix[x][y];
                }
                if (matrix[x + 1][y] > 4) {
                    second_pixel = 4;
                } else {
                    second_pixel = matrix[x + 1][y];
                }
            }
            writing_pixel = (first_pixel << 4) + second_pixel;
            file << writing_pixel;
        }
    }

}
