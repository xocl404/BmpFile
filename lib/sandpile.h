#ifndef LABWORK3_XOCL404_SANDPILE_H
#define LABWORK3_XOCL404_SANDPILE_H

#include <iostream>
#include <fstream>
#include <cstdint>

struct Direction {
    bool is_left = false;
    bool is_down = false;
    bool is_right = false;
    bool is_up = false;
};

struct Size {
    uint16_t length_x;
    uint16_t length_y;
};

struct Max {
    int16_t x;
    int16_t y;
};
struct Min {
    int16_t x;
    int16_t y;
};

void GetSize (const char* kTsvFilename, Size &size, Min &min, Max &max);
void ReadingTsvFile (const char* kTsvFilename, uint64_t** &matrix, Min &min);
bool IsExisted4AndMore (uint64_t** &matrix, Size &size);
void Scattering (uint64_t** &matrix, Size &size, Direction &direction);

#endif //LABWORK3_XOCL404_SANDPILE_H
