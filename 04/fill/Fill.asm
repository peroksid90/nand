// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

// Put your code here.


//16384 24576      8192

(MAIN_LOOP)

@8192
D=A

@count
M=D

@KBD
D=M

@LOOP_WHITE
D;JEQ

(LOOP_BLACK)

@count
D=M

@END_BLACK
D;JEQ

@count
M=D-1

D=M

@SCREEN
A=A+D
M=-1

@LOOP_BLACK
0;JMP

(END_BLACK)
@MAIN_LOOP
0;JMP



(LOOP_WHITE)

@count
D=M

@END_WHITE
D;JEQ

@count
M=D-1

D=M

@SCREEN
A=A+D
M=0

@LOOP_WHITE
0;JMP

(END_WHITE)
@MAIN_LOOP
0;JMP