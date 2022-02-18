#include "turing.h"

int main(int argc, char** argv) {
    // first arg is operation limit.
    // second arg is length of initial tape
    // 3rd-n args are the initial tape setup

    int maxOps = 10;
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
    TM cursor = {tape, 0};
    int numStates = 1;

    //Setting up the program instructions in a statetable
    instruction** stateTable;

    //Uncomment one of the lines below to decide which program to run, then compile with 'make'
    //stateTable = bitFlipInstructions(&numStates);
    //stateTable = incrementInstructions(&numStates);
    stateTable = busyBeaverInstructions(&numStates);


    
    

    //To run in verbose mode (print the state of the tape after every step)
    //Change the final argument of simulate from 0 to 1
    simulate(cursor, stateTable, maxOps, 0);
    freeTape(tape);
    freeStateTable(stateTable, 2);


}


void simulate(TM cursor, instruction** stateTable, int opLimit, int verbose) {
    int stepNum = 0;
    printf("Original Tape: ");
    showTape(cursor.current);
    while(stepNum < opLimit) {
        instruction operation = stateTable[cursor.state][cursor.current->value];
        cursor.current->value = operation.write;
        cursor.state = operation.nextState;

        switch(operation.d) {
            case (LEFT):
                cursor.current = moveLeft(cursor.current);
                break;
            case (RIGHT):
                cursor.current = moveRight(cursor.current);
                break;
            case (HALT):
                stepNum = opLimit + 1; //HALTs execution by increasing the counter to a value past the maximum
                break;
            default: //equivalent to: case (STAY)
                break;
        }
        if (verbose) {
            printf("               ");
            showTape(cursor.current);
        }
        
        
        stepNum++;
    }

    printf("Final Tape:    ");
    showTape(cursor.current);
    if(stepNum == opLimit) {
        printf("The program did not halt before reaching the input operation limit.\n");
    }

}


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
    while(start->prev != NULL) {
        start = start->prev;
    }
    printf("...");

    while (start->next != NULL) {
        printf("%u ", start->value);
        start = start->next;
    }
    printf("%u...\n", start->value);
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

void setInstruction(instruction* row, uint8_t write, direction d, int next) {
    // codes the write data
    row->nextState = next;
    row->write = write;
    row->d = d;

}


// Programs
/* NOTES:
    - Implemented as a 2-dimensional array holding instruction structors.
    - The instructions are set using a reference to the current instruction, what symbol to 
    write, which direction to move before the next instruction, and what state to change to.
    - I only use two symbols in the programs below but the possible symbols are stored
    as 8 bit, unsigned integers so feel free to write programs with more symbols. The only
    caveat is every symbol needs an instruction line in every possible state because instructions
    are found by using the value encountered. If a particular symbol is impossible in a given state
    feel free to leave that entry blank, but space must be allocated for it. Example: In a 4 symbol tape
    every state must have space for 4 instructions.



*/


instruction** busyBeaverInstructions(int* numStates) {
    // Three state busy beaver
    // symbols 0, 1
    // input tape should be an empty and should produce a tape of 1 1 1 1 1 1

    instruction** stateTable = newStateTable(3);
    *numStates = 3;

    stateTable[0] = newInstructionTable(2);
    setInstruction(&(stateTable[0][0]), 1, RIGHT, 1);
    setInstruction(&(stateTable[0][1]), 1, LEFT, 2);

    stateTable[1] = newInstructionTable(2);
    setInstruction(&(stateTable[1][0]), 1, LEFT, 0);
    setInstruction(&(stateTable[1][1]), 1, RIGHT, 1);

    stateTable[2] = newInstructionTable(2);
    setInstruction(&(stateTable[2][0]), 1, LEFT, 1);
    setInstruction(&(stateTable[2][1]), 1, HALT, 1);

    return stateTable;

}

instruction** bitFlipInstructions(int* numStates) {
    // Flips the value of all cells encountered
    // symbols 0,1
    // input any tape
    // Never terminates
    *numStates = 1;

    instruction** stateTable = newStateTable(1);

    stateTable[0] = newInstructionTable(2);
    setInstruction(&(stateTable[0][0]), 1, RIGHT, 0);
    setInstruction(&(stateTable[0][1]), 0, RIGHT, 0);

    return stateTable;

}


instruction** incrementInstructions(int* numStates) {
    // changes the first encountered 0 to 1 then halts
    // symbols 0,1
    // input any tape
    *numStates = 1;


    instruction** stateTable = newStateTable(1);

    stateTable[0] = newInstructionTable(2);
    setInstruction(&(stateTable[0][0]), 1, HALT, 0);
    setInstruction(&(stateTable[0][1]), 1, RIGHT, 0);

    return stateTable;

}

