#include <stdlib.h>
#include <stdio.h>


/** Structures **/

typedef enum {LEFT, STAY, RIGHT} direction;

// The 'tape' is a doubly linked list of cell structures.
typedef struct _cell {
    u_int8_t value;
    struct _cell* next;
    struct _cell* prev;
} cell;



// TODO: figure out how to represent an instruction properly
typedef struct _instruction {
    int state;
    uint8_t read;
    uint8_t write;
    direction d;
    int nextState;
    /* NOTES:
      - state does not need to be unique but for within a group of instructions of the same state the value in read needs to be unique
      - stored and searched like so:
            - There is an instruction table array which holds pointers to arrays for instructions of common state
            - The turing machine is given an initial state number and looks up the specific instruction using the value it reads
            - The state and instruction tables are in order so that the possible instructions for state 12 are stored at stateTable[12]
                and the instructions for value 0 are at instructionTable[0]
            - The final state in the state table points to an instruction table with instructions to write what is read, stay, and not 
                change state
            - The operation counter will be incremented so that it reaches the maximum value given at runtime
      -  
    */


} instruction;



typedef struct _TM{
    cell* current;
    int state;

} TM;



/** Prototypes **/

// allowing to fill the tape with data before running because any finite start state could be setup by a sequence of chaining rules that terminate at the initial position
cell* setupTape(int length, uint8_t* setup);

void simulate(TM cursor, instruction** stateTable, int opLimit);

// allocates memory and sets value to 0 and appropiate relationship to parameter cell.
void addPrevious(cell* successor);

void addNext(cell* previous);

// Deallocates the memory used to store the tape
void freeTape(cell* start);

// displays the tape. starts at given cell and runs until reaches end of tape.
void showTape(cell* start);

cell* moveRight(cell* current);

cell* moveLeft(cell* current);

instruction** newStateTable(int numStates);

instruction* newInstructionTable(int numSymbols);

void freeStateTable(instruction** stateTable, int numStates);

void setInstruction(instruction* row, int state, uint8_t read, uint8_t write, direction d, int next);

instruction** bitFlipTable();



