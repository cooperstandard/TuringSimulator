#include <stdlib.h>
#include <stdio.h>


/* NOTES:
    - Store the cells as a doubly linked list on the heap.
    - state mutations are stored as function pointers.
    - Can't find a way to make anonymous functions in c so programming the machine will be a little tedious
    - Turing machine will preform operations until it completes the number specified at invocation
    - The instruction table will be stored in a continous block of memory



*/

/** Structures **/

// The 'tape' is a doubly linked list of cell structures.
typedef struct _cell {
    u_int8_t value;
    struct _cell* next;
    struct _cell* prev;
} cell;


// TODO: figure out how to represent an instruction properly
typedef struct _instruction {
    uint8_t (*operation) (uint8_t);
    struct _instruction* next0;
    struct _instruction* next1;
    int direction;
    /*
      0 move left,
      1 dont move, 
      2 move right, 
      3 move left if 0 else dont move, 
      4 move left if 0 else move right, 
      5 dont move if 0 else left, 
      6 dont move if 0 else right, 
      7 move right if 0 else dont move, 
      8 move right if 0 else left
    */


} instruction;

typedef struct {
    cell* cursor;
    instruction* currentInstruction;

} TM;




/** Globals **/



/** Prototypes **/

// allowing to fill the tape with data before running because any finite start state could be setup by a sequence of chaining rules that terminate at the initial position
cell* setupTape(int length, uint8_t* setup);

// allocates memory and sets value to 0 and appropiate relationship to parameter cell.
cell* addPrevious(cell* successor);

cell* addNext(cell* previous);

// Deallocates the memory used to store the tape
void freeTape(cell* start);

// displays the tape. starts at given cell and runs until reaches end of tape.
void showTape(cell* start);

