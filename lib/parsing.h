#ifndef LABWORK3_XOCL404_PARSING_H
#define LABWORK3_XOCL404_PARSING_H

#include <iostream>
#include <cstring>
#include <cstdint>

struct Arguments {
    char* input;
    char* output;
    uint64_t max_iter;
    uint64_t freq;
    bool information_ownership [4];
};
void ParseArguments (int argc, char** argv, Arguments &arguments);

#endif //LABWORK3_XOCL404_PARSING_H
