#include "parsing.h"

void ParseArguments (int argc, char** argv, Arguments &arguments) {
    for (int i = 0; i < 4; ++i) {
        arguments.information_ownership[i] = false;
    }

    for (int i = 1; i < argc; ++i) {

        if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "--input")) {
            arguments.input = argv[++i];
            arguments.information_ownership[0] = true;

        } else if (!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")) {
            arguments.output = argv[++i];
            arguments.information_ownership[1] = true;

        } else if (strcmp(argv[i], "-m") == 0 || strcmp(argv[i], "--max-iter") == 0) {
            arguments.max_iter = atoi(argv[++i]);
            arguments.information_ownership[2] = true;

        } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--freq") == 0) {
            arguments.freq = atoi(argv[++i]);
            arguments.information_ownership[3] = true;

        } else {
            std::cerr << "ERROR: Uncorrect arguments\n";
            exit(1);
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (!arguments.information_ownership[i]) {
            std::cerr << "ERROR: Not enough arguments" << std::endl;
            exit(1);
        }
    }
}
