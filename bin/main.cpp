#include "parsing.h"
#include "sandpile.h"
#include "bmp.h"

int main (int argc, char** argv) {
    Arguments arguments {};
    ParseArguments (argc, argv, arguments);

    const char* kTsvFilename = arguments.input;
    Size size;
    Min min;
    Max max;
    GetSize (kTsvFilename, size, min, max);

    uint64_t** matrix = new uint64_t*[size.length_x];
    for (uint16_t i = 0; i < size.length_x; ++i) {
        matrix[i] = new uint64_t[size.length_y];
        for (uint16_t j = 0; j < size.length_y; ++j) {
            matrix[i][j] = 0;
        }
    }

    ReadingTsvFile (kTsvFilename, matrix, min);

    uint64_t number_of_iteration = 0;
    uint64_t number_of_picture = 0;
    while (IsExisted4AndMore (matrix, size)) {
        Direction direction;
        Scattering (matrix, size, direction);
        ++number_of_iteration;
        if (arguments.freq) {
            if (!(number_of_iteration % arguments.freq)) {
                Bmp bmp;
                Color color;
                ++number_of_picture;
                CreatingBmpFile(arguments.output, matrix, size, number_of_picture, bmp, color);
            }
        }
        if (number_of_iteration == arguments.max_iter) {
            break;
        }
    }
    Bmp bmp;
    Color color;
    ++number_of_picture;
    CreatingBmpFile (arguments.output, matrix, size, number_of_picture, bmp, color);

    return EXIT_SUCCESS;
}
