#include "sandpile.h"

void GetSize (const char* kTsvFilename, Size &size, Min &min, Max &max) {
    std::ifstream file(kTsvFilename);
    if (!file.is_open()) {
        std::cerr << "ERROR: tsv-file opening error" << std::endl;

        exit(1);
    }

    int16_t x;
    int16_t y;
    uint64_t pixel;

    file >> x;
    file >> y;
    file >> pixel;
    max.x = x;
    max.y = y;
    min.x = x;
    min.y = y;

    while (file >> x >> y >> pixel) {
        max.x = std::max(x, max.x);
        min.x = std::min(x, min.x);
        max.y = std::max(y, max.y);
        min.y = std::min(y, min.y);
    }

    size.length_x = max.x - min.x + 1;
    size.length_y = max.y - min.y + 1;
}

void ReadingTsvFile (const char* kTsvFilename, uint64_t** &matrix, Min &min) {
    std::ifstream file(kTsvFilename);
    int16_t x;
    int16_t y;
    uint64_t pixel;
    while (file >> x >> y >> pixel) {
        matrix[x - min.x][y - min.y] = pixel;
    }
}

bool IsExisted4AndMore (uint64_t** &matrix, Size &size) {
    for (uint16_t x = 0; x < size.length_x; ++x) {
        for (uint16_t y = 0; y < size.length_y; ++y) {
            if (matrix[x][y] >= 4) {
                return true;
            }
        }
    }
    return false;
}

void Scattering (uint64_t** &matrix, Size &size, Direction &direction) {
    for (uint16_t y = 0; y < size.length_y; ++y) {
        if (matrix[0][y] >= 4) {
            direction.is_left = true;
            break;
        }
    }
    for (uint16_t x = 0; x < size.length_x; ++x) {
        if (matrix[x][0] >= 4) {
            direction.is_down = true;
            break;
        }
    }
    for (uint16_t y = 0; y < size.length_y; ++y) {
        if (matrix[size.length_x - 1][y] >= 4) {
            direction.is_right = true;
            break;
        }
    }
    for (uint16_t x = 0; x < size.length_x; ++x) {
        if (matrix[x][size.length_y - 1] >= 4) {
            direction.is_up = true;
            break;
        }
    }

    if (direction.is_left) {
        ++size.length_x;
        uint64_t** new_matrix = new uint64_t*[size.length_x];
        for (uint16_t i = 0; i < size.length_x; ++i) {
            new_matrix[i] = new uint64_t[size.length_y];
            for (uint16_t j = 0; j < size.length_y; ++j) {
              new_matrix[i][j] = 0;
            }
        }
        for (uint16_t x = 1; x < size.length_x; ++x) {
            for (uint16_t y = 0; y < size.length_y; ++y) {
                new_matrix[x][y] = matrix[x-1][y];
            }
        }
        for (uint16_t i = 0; i < size.length_x - 1; ++i) {
            delete [] matrix[i];
        }
        delete [] matrix;
        matrix = new_matrix;
    }
    if (direction.is_down) {
        ++size.length_y;
        uint64_t** new_matrix = new uint64_t*[size.length_x];
        for (uint16_t i = 0; i < size.length_x; ++i) {
            new_matrix[i] = new uint64_t[size.length_y];
            for (uint16_t j = 0; j < size.length_y; ++j) {
                new_matrix[i][j] = 0;
            }
        }
        for (uint16_t x = 0; x < size.length_x; ++x) {
            for (uint16_t y = 1; y < size.length_y; ++y) {
                new_matrix[x][y] = matrix[x][y-1];
            }
        }
        for (uint16_t i = 0; i < size.length_x; ++i) {
            delete [] matrix[i];
        }
        delete [] matrix;
        matrix = new_matrix;
    }
    if (direction.is_right) {
        ++size.length_x;
        uint64_t** new_matrix = new uint64_t*[size.length_x];
        for (uint16_t i = 0; i < size.length_x; ++i) {
            new_matrix[i] = new uint64_t[size.length_y];
            for (uint16_t j = 0; j < size.length_y; ++j) {
                new_matrix[i][j] = 0;
            }
        }
        for (uint16_t x = 0; x < size.length_x - 1; ++x) {
            for (uint16_t y = 0; y < size.length_y; ++y) {
                new_matrix[x][y] = matrix[x][y];
            }
        }
        for (uint16_t i = 0; i < size.length_x - 1; ++i) {
            delete [] matrix[i];
        }
        delete [] matrix;
        matrix = new_matrix;
    }
    if (direction.is_up) {
        ++size.length_y;
        uint64_t** new_matrix = new uint64_t*[size.length_x];
        for (uint16_t i = 0; i < size.length_x; ++i) {
            new_matrix[i] = new uint64_t[size.length_y];
            for (uint16_t j = 0; j < size.length_y; ++j) {
                new_matrix[i][j] = 0;
            }
        }
        for (uint16_t x = 0; x < size.length_x; ++x) {
            for (uint16_t y = 0; y < size.length_y-1; ++y) {
                new_matrix[x][y] = matrix[x][y];
            }
        }
        for (uint16_t i = 0; i < size.length_x; ++i) {
            delete [] matrix[i];
        }
        delete [] matrix;
        matrix = new_matrix;
    }
    for (uint16_t x = 1; x < size.length_x - 1; ++x) {
        for (uint16_t y = 1; y < size.length_y - 1; ++y) {
            if (matrix[x][y] >= 4) {
                matrix[x][y] -= 4;
                ++matrix[x - 1][y];
                ++matrix[x + 1][y];
                ++matrix[x][y - 1];
                ++matrix[x][y + 1];
            }
        }
    }
}
