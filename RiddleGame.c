/* This Number Riddle Puzzle game works by utilizing char array generated in sequence,
then randomized and printed in a matrix form according to input from the user. We then use the
location of the characters and empty cell to move and swap the values, and selection structures
to define conditions and implementing them. */

/* Initializing C Libraries. */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//Function protoypes:
void random(char *array, int size);
void display(char *array, int size, int cols);
int winCheck(char *array, int size);


int main() {
	// Printing intro.
	printf("Number Riddle Puzzle Game v1.1.\nProgrammed by: Afrasiyab Khan.\n"); 

	/* Taking number of rows and columns as input from the user, respectively. */
	int rows, cols;
	
	do {
		printf("Enter the Number of Rows (3 - 8): "); // Inputting number of rows
		scanf("%d", &rows);
	} while (rows < 3 || rows > 8);  // Using loop to make sure values entered are within bounds.

	do {
		printf("Enter the Number of Columns (3 - 8): "); // Inputting number of columns
		scanf("%d", &cols);
	} while (cols < 3 || cols > 8); // Using loop to make sure values entered are within bounds.

	/* Initiliazing array depending on the RowsxCols input
	from the user. The array is a char array because
	we can store a blank ' ' value in char to create the empty cell. */

	int size = rows * cols;
	char array[size];

	/* Calling the random function. This randomizes the array. */
	random(array, size);

	printf("\n"); // Skipping a line for tidyness.

	/* Calling the display function. This displays the array. */
	display(array, size, cols);

	int n;
	int loc, move, count = 1;
	do {
		printf("(MOVE#%d), Enter the Number you want to move (0 to exit): ", count++);
		scanf("%d", &n);

		/* Condition for exiting if the user enters 0. */
		if (n == 0) {
			printf("Goodbye!\n");
			return 0;
		}

		/* Condition for getting location of the number the user wants
		to move in the array. */
		for (int x = 0; x < size; x++) {
			if (array[x] == n) {
				move = x;
			}
		}

		/* Condition for finding out the location of the
		blank/empty cell. */
		for (int x = 0; x < size; x++) {
			if (array[x] == ' ') {
				loc = x;
			}
		}

		/* Condition for moving the entered number up/down and left or right. */
		if ((move == loc + 1 || move == loc - 1 || move == loc + cols || move == loc - cols)){
			/* Checking for Invalid moves: */

			if ((loc % cols == 0 && move == loc - 1) || ((loc + 1) % cols == 0 && move % cols == 0)) {
				printf("This cell can't move!\n"); // Printing error message if the value is invalid.
			}
			else {
				char temp = array[move]; // Swapping values.
				array[move] = array[loc];
				array[loc] = temp;
			}
		}
		else {
			printf("This cell can't move!\n"); // Printing error message if the value is invalid.
		}

		// Again, calling the display function to print out the array.
		display(array, size, cols);

		/* Calling the WinCheck function to check for win (if the numbers are arranged or not).
		If yes, winning message is printed. */
		if (winCheck(array, size) == 1) {
			break;
		}

	} while (1); // Using infinite loop to keep the game running until the user wins or exits.

	printf("\nCongratulations, You Won!\n");					// Printing winning message.
	printf("Enter 1 to re-play or any other number to Exit: "); // Restart or end
	scanf("%d", &n);

	/* Condition for restarting the game. If the user enters 1, main function
	will be called again and screen will be cleared and the code will re-run. */
	if (n == 1) {
		system("CLS"); // To clear screen.
		main();
	}
	else {
		printf("Goodbye!\n");
	}
	return 0;
}

/* Function to randomly generate the array. */
void random(char *array, int size) {

	/* Filling the char array in sequence, with one empty cell. */
	for (int i = 0; i < size - 1; i++) {
		*(array + i) = i + 1;
	}
	//Accomodating whitespace.
	*(array + (size - 1)) = ' ';

	/* Randomly shuffling the array to create a randomly
	generated RowsxCols array/matrix. */

	// Making sure a new shuffle is done everytime the code is run.
	srand(time(NULL)); 
	for (int i = 0; i < size; i++) {
		char temp = *(array + i);
		int randomIndex = rand() % size;

		*(array + i) = *(array + randomIndex);
		*(array + randomIndex) = temp;
	}
}

/* Function to print out the array. */
void display(char *array, int size, int cols) {
	for (int x = 0; x < size; x++) {
		printf("\t");

		/* In ASCII, the value of blank space is 32.
		So, if the char's ASCII value is 32, a %c character
		will be printed, and a blank cell will be made. */

		if (*(array + x) == 32) {
			printf("%c", *(array + x)); 	// Printing Character's Symbol.
		}
		/* Else the ASCII value will be printed, filling the array. */
		else {
			printf("%d", *(array + x)); 	// Printing character's ASCII code.
		}
		//Formatting:
		printf("\t|");

		if ((x + 1) % cols == 0) {	// Skipping line after reaching column's desired length.
			printf("\n\n"); 		// Moving on two lines for cleanliness.
		}
	}
}

/* Function to check for win.
This function returns 0 or 1 depending on the sequence of numbers.
It is a win if this function returns 1. */
int winCheck(char *array, int size) {
	/* Checking if all the values are in sequence in the array/matrix. */
	int check = 0;
	if (*(array + (size - 1)) == ' ') {
		check = 0;
		for (int i = 0; i < size - 2; i++) { // Checking if all the values from 1 to size are in sequence.
			if (*(array + i) != i + 1) {
				check = 1;
			}
		}
		if (check == 0) {
			return 1;
		}
	}
	else {
		return 0;
	}
}