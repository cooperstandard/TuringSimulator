# TuringSimulator
### Cooper Standard, 2022


This project is a Turing Machine emulator. My goals for this project are to gain a better understanding of theoretical computing and refresh myself on c programming. There are three example programs, an inverter, an incrementer, and a three state implementation of busy beaver. Feel free to try some of your own. I have included descriptions of the program format in the header and c files.

Compile using the command `make` from the root of project folder.

To change which program is being executed uncomment one of the options below the comment on line 43.

Execute turingSimulator with this command:
`./turing.o <Instruction Limit> <Length of Initial Tape> <Space Seperated Values>`

For Example:
- To run with a limit of 40 steps and a starting tape of "0":
`./turing.o 40 1 0`
- To run with a limit of 5 steps and a starting tape of "1 1 1":
`./turing.o 5 3 1 1 1`

To display the tape after each step change the last arguement of call to `simulate`, on line 54, to 1
