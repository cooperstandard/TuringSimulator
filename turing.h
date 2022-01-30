#include <stdlib.h>
#include <stdio.h>


/* NOTES:
    - Store the cells as a doubly linked list on the heap.
    - state mutations are stored as function pointers.
    - Can't find a way to make anonymous functions in c so programming the machine will be a little tedious
    



*/

/** Structures **/

// The 'tape' is a doubly linked list of cell structures.
typedef struct _cell {
    u_int8_t value;
    struct _cell* next;
    struct _cell* prev;
} cell;

typedef struct _instruction {
    int* (*operation) (uint8_t);
    struct _instruction* next0;
    struct _instruction* next1;

} instruction;




/** Globals **/

cell* cursor;



/** Prototypes **/

// allowing to fill the tape with data before running because any finite start state could be setup by a sequence of chaining rules that terminate at the initial position
cell* setupTape(uint8_t* start);
