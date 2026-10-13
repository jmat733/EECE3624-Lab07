/***************************************************************************
 * Lab07.c (barebones starter code version)
 *
 *   Created: 10/13/2026
 *    Author: Jake Matthews
 * Processor: ATmega128A (on a ReadyAVR)
 *
 * This code creates a triangle pattern using a 1 dimensional array
 * using black (*) and white ( ) characters and updates the array on every iteration
 **************************************************************************/

/* your #include file declaration(s) go here */
#include "UARTLibrary.h"

/* your #define declarations go here */
#define BaudRate 9600
#define DataBits 8
#define StopBits 1
#define NoParity 0
#define ArraySize 61
#define Generations 122
// prototype subroutine definitions
void initializeArray(unsigned char *cp);
void displayArray(unsigned char *cp);
void updateArray(unsigned char *cp);

int main(void)
{
	// create a 61-char array
	unsigned char cells[ArraySize];

	// Initialize the UART
	// ProfNote:  Understand the UARTLibary.h before blindly running the next line!
	uart_init(BaudRate, DataBits, StopBits, NoParity);
	
	// ProfNote:  Initial Testing Only!  Comment out after UART confirmed working!
	//while (1) {
		//uart_tx('H');uart_tx('e');uart_tx('l');uart_tx('l');uart_tx('o');uart_tx('\r');uart_tx('\n');
	//	uart_tx('W');uart_tx('o');uart_tx('r');uart_tx('l');uart_tx('d');uart_tx('!');uart_tx('\r');uart_tx('\n');
	//}
	
    initializeArray(cells);
	
	for (int gen = 0; gen < Generations; gen++) {
		displayArray(cells);  // Display current array
		updateArray(cells);   // Update current array for next generation
	}
	while (1) {
		// when done
	}
}

/* your subroutines go here */
void initializeArray(unsigned char *cp){
	for (int i = 0; i < ArraySize; i++) {
		*(cp + i) = ' ';
	}
	// Place a single '*' character in the middle at index 30
	*(cp + 30) = '*';
}
void displayArray(unsigned char *cp){
	// ProfNote:  Look through your line using "uart_tx(<char>)" to print one character at a time.
	// At the end of the line, use "uart_tx('\r'); uart_tx('\n');" to print a new line to keep your
	// output aligned properly.
	for (int i = 0; i < ArraySize; i++) {
		uart_tx(*(cp + i));
	}
	// Print a new line to align the output properly on the terminal
	uart_tx('\r');
	uart_tx('\n');
}
void updateArray(unsigned char *cp){
	unsigned char next[ArraySize];
	
	// The first and last cells of the array are always white
	next[0] = ' ';
	next[ArraySize - 1] = ' ';
	
	
	for (int i = 1; i < ArraySize - 1; i++) {
		unsigned char left   = *(cp + i - 1);
		unsigned char center = *(cp + i);
		unsigned char right  = *(cp + i + 1);
		
		// Rules
		// Rule 4: * _ _ -> *
		// Rule 5: _ * * -> *
		// Rule 7: _ _ * -> *
		// All other combinations result in ' ' (white)
		if ((left == ' ' && center == ' ' && right == '*') || (left == ' ' && center == '*' && right == '*') || (left == '*' && center == ' ' && right == ' ')) {
			next[i] = '*';
			} else {
			next[i] = ' ';
		}
	}
	
	// Copy the new generation back into the current array using memcpy
	memcpy(cp, next, ArraySize);
}
