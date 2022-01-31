#include "turing.h"

int main(int argc, char** argv) {
    // first arg is operation limit.
    // second arg is length of initial tape
    // 3rd-n arrgs are the initial tape setup
    // if there is only one arg, or the second arg is 0, the tape is setup to have 3 allocated cells containing 0;
    int maxOps = 100;
    uint8_t* setup;
    int length = 3;
    if (argc == 1) {
        setup = calloc(3,sizeof(uint8_t));
        setup[0] = 0;
        setup[1] = 0;
        setup[2] = 0;
    }

    if (argc > 1) {
        maxOps = atoi(argv[1]);
        if (argv[2][0] == '0') {
            setup = calloc(3,sizeof(uint8_t));
            setup[0] = 0;
            setup[1] = 0;
            setup[2] = 0;
        } else {
            setup = calloc(atoi(argv[2]), sizeof(uint8_t));
            for(int i = 0; i < atoi(argv[2]); i++) {
                setup[i] = atoi(argv[3+i]);
            }
            length = atoi(argv[2]);
        }

    }

    cell* tape = setupTape(length, setup);
    free(setup);
    showTape(tape);
    TM cursor = {tape, 0};


    free(tape);


}
// TODO:
void simulate(TM cursor, instruction** stateTable, int opLimit);


cell* setupTape(int length, uint8_t* setup) {
    cell* first = malloc(sizeof(cell));
    first->value = setup[0];
    first->prev = NULL;
    cell* current = first;

    for(int i = 1; i < length; i++) {
        current->next = malloc(sizeof(cell));
        current->next->prev = current;
        current = current->next;
        current->value = setup[i];
    }

    current->next = NULL;
    

    return first;
}


void showTape(cell* start) {
    if (start->next == NULL) {
        printf("%u\n", start->value);
    } else {
        printf("%u ", start->value);
        showTape(start->next);
    }
}


void freeTape(cell* start) {
    while(start->prev != NULL) {
        start = start->prev;
    }

    while(start->next != NULL) {
        start = start->next;
        free(start->prev);
    }

    free(start);


}


void addPrevious(cell* successor) {
    successor->prev = malloc(sizeof(cell));
    successor->prev->next = successor;
    successor->prev->prev = NULL;
    successor->prev->value = 0;
}


void addNext(cell* previous) {
    previous->next = malloc(sizeof(cell));
    previous->next->prev = previous;
    previous->next->next = NULL;
    previous->next->value = 0;
}

cell* moveRight(cell* current) {
    if (current->next == NULL) {
        addNext(current);
    }
    return current->next;
}

cell* moveLeft(cell* current) {
    if (current->prev == NULL) {
        addPrevious(current);
    }
    return current->prev;
}


instruction** newStateTable(int numStates) {
    // numStates should not include the halting state
    return calloc(numStates, sizeof(instruction*));
}

instruction* newInstructionTable(int numSymbols) {
    return calloc(numSymbols, sizeof(instruction));
}

void freeStateTable(instruction** stateTable, int numStates) {
    for(int i = 0; i < numStates; i++) {
        // this may be wrong
        free((stateTable[i]));
    }
    free(stateTable);
}




