// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Start: infinite loop
(INPUTCHECK)
	// Keyboard = KBD (address 24576 in hack) -> input to D-register
	@KBD
	D = M
	
	@tofillornottofill
	M = 0

	// If input == 0: jump to display -> setting pixels to 0 (0 = 0 16 bits)
	@DISPLAY
	D ; JEQ
	
	// else: jump to display with pixels to 1 (-1 = 1 16 bits)
	@tofillornottofill
	M = -1
	
@DISPLAY
0 ; JMP
	
	
(DISPLAY)
	@SCREEN
	D = A
	@screenindex
	M = D

	// traverse through addresses (8192 (word [32] * row [256]) via pointer arithmetic and set values to the tofillornottofill variable
	(FILLING)
		
		@tofillornottofill
		D = M
		
		@screenindex
		A = M  
		// Pixels in next memory address
		M = D 
		
		@screenindex		
		M = M + 1
		
		
		// Continue loop until all rows are done (8192 rows between start and end)
		@KBD
		D = A
		@screenindex 
		D = D - M
	
	@FILLING
	D ; JGT



@INPUTCHECK
0 ; JMP




