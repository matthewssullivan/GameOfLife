#include <iostream>
#include <fstream>
#include <string>
#include "GameOfLife_csci2312.h"

using namespace csci2312;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::ios;

int main()
{
	char prompt;		// User input value
	int size = 100;		// initializes size of board variable to 100
	cout << "Welcome to my Game of Life simulation! \n" << endl;
	cout << "If you would like the default 30X30 board, please enter '1'." << endl;	// message to user
	cout << "If you would like to select a smaller size, please enter '2'." << endl;
	cin >> prompt;															// user input
	while ((prompt != '1') && (prompt != '2'))			// Loops and checks to see if input is acceptable
	{
		cout << "You did not input an appropriate input. Please enter 1 or 2 or press Ctrl +C to exit" << endl;		// error message
		cin >> prompt;		// New user input
	}

	if (prompt == '1')
	{
		size = 30;
	}
	else
	{
		while (size > 30)		// Ensures size is less than or equal to 30
		{
			cout << "Please enter the size of the board, less than or equal to 30." << endl;	// Enters size of board
			cin >> size;
		}
	}

	GameOfLife Life(size);			// Creates current generation of user input size

	cout << "If you would like to seed the board randomly, please enter '1'." << endl;		//user prompts
	cout << "If you would like to seed the board from a file, please enter '2'." << endl;
	cin >> prompt;
	while ((prompt != '1') && (prompt != '2'))		// Checks to see if prompts were good
	{
		cout << "You did not input an appropriate input. Please enter 1 or 2 or press Ctrl +C to exit" << endl;
		cin >> prompt;
	}

	if ((prompt == '2') && (Life.seedBoard("GameOfLifeInput1.txt") == 0))		// If file loading is successful
		cout << "File loaded" << endl;			// Confirmation message
	else                                 // if file loading fails or if user selects it
	{
		cout << "Seeding randomly" << endl;
		int numberAlive;
		cout << "Please enter in integers the number of alive cells you would like" << endl;
		cin >> numberAlive;
		while (numberAlive > (size*size))		// ensures number of alive cells not greater than total number of cells
		{
			cout << "The size you entered is too large, please enter a number smaller than the number of cells in the matrix." << endl;
			cin >> numberAlive;
		}
		Life.seedBoard(numberAlive);	// Seeds the board randomly
	}

	cout << "If you would like to prompt the game for each iteration enter '1'." << endl;
	cout << "If you would like to run the game for a number of iterations enter '2'." << endl;

	cin >> prompt;
	while ((prompt != '1') && (prompt != '2'))		// Checks user input
	{
		cout << "You did not input an appropriate input. Please enter 1 or 2 or press Ctrl +C to exit" << endl;
		cin >> prompt;
	}
	if (prompt == '1')
	{
		Life.run();
	}

	else
	{
		int runs;
		cout << "Enter number of runs you wish to perform." << endl;
		cin >> runs;
		Life.run(runs);
	}

	cout << "Thank you for running this program!" << endl;
	system("PAUSE");
	return 0;

}