// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// for (int i = 0; i < R1; ++i){
//			sum += R0;
//	}

// Grab value from R1 to iterate down from - multiplication by adding R0 by R1 times
// loop: i < R1

@R2
M = 0
@R1
D = M

// Iteration starts and decreases from R1 - converted to a positive integer
@i
MD = D

@LOOP
D ; JGE
@i
MD = -D

// Loops -> check for sign of sum after iteration
(LOOP)
@SIGNCHECK
D ; JEQ

// Else, add R0 to R2
@R0
D = M

@R2
M = M + D

// iterate
@i 
MD = M - 1
@LOOP
0;JMP

(SIGNCHECK)
// R0 has control of sign -> just need to check R1 for correct sign
@R1
D = M
@END
D ; JGT

@R2
M = -M


(END)
@END
0;JMP