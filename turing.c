#include "turing.h"

int main(int argc, char** argv) {
    int maxOps = 100;
    if (argc > 1) {
        maxOps = atoi(argv[1]);
    } 

    
    printf("Compilation successful %d\n", maxOps);
}

