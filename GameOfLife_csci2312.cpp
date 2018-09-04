#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "GameOfLife_csci2312.h"
using namespace csci2312;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::ios;
Cell::Cell()
//     POSTCONDITION: Creates a dark/dead Cell
{
	state = false; //Creates a dead cell by default
}

Cell::Cell(bool inputState)
//     POSTCONDITION: Creates a cell at a given state
{
	state = inputState; //Creates a cell and set it to given state
}

Cell::~Cell() //Deconstructor
			  //		POSTCONDITION: Destructs cell
{
}

void Cell::setState(bool newState)
//     POSTCONDITION: Cell's state is set to the new state
{
	state = newState; //Sets state to given state
}

bool Cell::getState() const 
{
	return state; // Returns the state of the Cell
}

char Cell::getFace() const 
{
	if (state == true) // Returns the face of the cell based on the state
		return alive;
	else
		return dead;
}

GameOfLife::GameOfLife()
//       POSTCONDITION: Creates a maximum size matrix of dark cells
{
	boardSize = MAX_BOARD;
}

GameOfLife::GameOfLife(size_t size)
//       PRECONDITION: boardSize is not greater than MAX_BOARD  
//       POSTCONDITION: Creates a boardSize-size matrix of dark cells. Sets boardSize private member.
{
	if (size > MAX_BOARD)		// Checks to see if size is greater than the maximum size
	{
		cout << "Size selected is too large, creating board of maximum size." << endl; // User error message
		size = MAX_BOARD;						// Sets size to maximum
	}
	boardSize = size;								// Sets size of board to be evaluated to user given size.
}

GameOfLife::~GameOfLife()
//		POSTCONDITION: Destructs GameOfLife matrix
{
}

int GameOfLife::seedBoard(string fileName)
//     FUNCIONALITY: Initializes the board; reads the configuration of lit from a text file. Returns 0/1 for sucsess/failure
//     POSTCONDITION: Board is successfully seeded with a known predictable pattern, method returns 0 (zero) to indicate success.  
//                    If the operation failed (could not open the file, wrong file format, etc), the function returns 1.
{
	int horiz = 1;		//Initializes horizontal start point to one (to leave halo area cleared)
	int vert = 1;		// Same as above, except for vertical
	string add;			// Sets variable for input stream storage
	ifstream myFile;	// Sets variable for input file stream
	myFile.open(fileName, ios::in);		// Opens file
	if (myFile.is_open())				//Checks to see if file is open
	{
		int count = 0;					// sets count to 0
		while (!myFile.eof())			//Checks to make sure file isn't ended
		{
			getline(myFile, add, ' ');		// reads file seperated by space
			count++;						// increases count
		}
		if (count != boardSize*boardSize)	// Checks if the number of items to read from the file is the same number of objects in the grid
		{
			cout << count;
			cout << "File incorrect size" << endl;		//User error message
			myFile.close();			// Closes file
			return 1;
		}
		myFile.clear();				// Resets EOF flag
		myFile.seekg(0, ios::beg);	// sets read head to the beginning of file

		while (!myFile.eof())		
		{
			getline(myFile, add, ' ');
			if ((add != "0") && (add != "1"))		// Checks to see if read object is anything other than '1' or '0'
			{
				cout << "File incorrect format" << endl;	// Error message
				return 1;
			}
		}
		myFile.clear();
		myFile.seekg(0, ios::beg);

		{
			if ((vert == 0) || (horiz == 0))				
				currentLife[vert][horiz].setState(false);		// Sets the halo to false (if it was seeded improperly)
			for (vert = 1; vert <= boardSize; vert++)			// Steps through the vertical members array
			{
				for (horiz = 1; horiz <= boardSize; horiz++)	// Steps through the horizontal members of the array
				{
					getline(myFile, add, ' ');					// Reads from fie
					if (add == "0")								// If the input is '0'
						currentLife[vert][horiz].setState(false);	//Sets cell to false (dead)

					else
						currentLife[vert][horiz].setState(true);	// Sets cell to true (alive)

				}
			}
		}
	}
	else
	{
		myFile.close();
		cout << "Unable to open file" << endl;		// Error message to user
		return 1;
	}
	myFile.close();
	return 0;
}

void GameOfLife::seedBoard(size_t seeds)

//     FUNCTIONALITY:  Initializes the board with seeds-number of lit cells at randomly generated locations. 
//     PRECONDITION: Number of seeds requested is not greater than maximum matrix capacity  
//     POSTCONDITION: Board is successfully seeded
{
	srand(time(NULL));  // Seeds the random number to the runtime
	int hrand = 0;		// initializes int to hold random horizontal position
	int vrand = 0;		// initializes int to hold random vertical position
	while (seeds > 0)	// Checks to see if number of total seeds has been met, loops until it has
	{
		vrand = rand() % (boardSize + 1);		// Gets random number for vrand
		hrand = rand() % (boardSize + 1);		// Gets random number for hrand
		if (currentLife[vrand][hrand].getState() == false)		// Checks to see if cell selected is dead
		{
			currentLife[vrand][hrand].setState(true);		// Brings the cell to life
			seeds -= 1;										// Decreases number of seeds by 1
		}
	}
}

void GameOfLife::run() 

//     FUNCTIONALITY: Starts the simulation.  Asks a user if to generate another iteration, or if to end
//     POSTCONDITION: Simulation has run
{
	int horiz = 0;		// Holds horizontal coordinate
	int vert = 0;		// Holds vertical coordinate
	int aliveCount = 0;		// Counter for number of alive squares surrounding cell
	char input = ' ';		// Initializes user input variable to ' '
	while (input != 'Q')	// Loops until user input is 'Q'
	{

		for (vert = 1; vert <= boardSize; vert++)		// Steps through array
		{
			for (horiz = 1; horiz <= boardSize; horiz++)	// Steps through array for each member
			{
				aliveCount = 0;			// Resets aliveCount to zero

				if (currentLife[vert - 1][horiz - 1].getState() == true) //If Top Left Cell is alive
					aliveCount += 1;									//Iterates aliveCount

				if (currentLife[vert - 1][horiz].getState() == true) // If Top Cell is alive
					aliveCount += 1;
				
				if (currentLife[vert - 1][horiz + 1].getState() == true) // If Top Right Cell is alive
					aliveCount += 1;
				
				if (currentLife[vert][horiz - 1].getState() == true) // If Left Cell is alive
					aliveCount += 1;
				
				if (currentLife[vert][horiz + 1].getState() == true) // If Right Cell is alive
					aliveCount += 1;
				
				if (currentLife[vert + 1][horiz - 1].getState() == true) // If Bottom Left Cell is alive
					aliveCount += 1;
				
				if (currentLife[vert + 1][horiz].getState() == true)//If Bottom Cell is alive
					aliveCount += 1;
				
				if (currentLife[vert + 1][horiz + 1].getState() == true) //If Bottom Right Cell is alive
					aliveCount += 1;
				
				if (executeRules(aliveCount, currentLife[vert][horiz].getState())) //calls executeRules, if true
				{
					nextLife[vert][horiz].setState(true);	// Sets the cell in the next generation at the coordinate to alive
				}
				else
					nextLife[vert][horiz].setState(false);	// Sets the cell in the next generation at the coordinate to dead

			}
		}

		for (vert = 1; vert <= boardSize; vert++)
		{
			for (horiz = 1; horiz <= boardSize; horiz++)
			{
				cout << currentLife[vert][horiz].getFace() << "   ";	// Prints current generation
			}
			cout << "\n" << endl;
		}

		for (vert = 1; vert <= boardSize; vert++)
		{
			for (horiz = 1; horiz <= boardSize; horiz++)
			{
				currentLife[vert][horiz].setState(nextLife[vert][horiz].getState());	// Copies nextLife to currentLife, cell by cell
			}
		}

		cout << "Please press any key for next generation, or press 'Q' to quit" << endl;	//User prompt
		cin >> input;	// User input

	}
}

void GameOfLife::run(unsigned int numberOfRounds)
//     FUNCTIONALITY: Starts the simulation.  
//     POSTCONDITION: Simulation has run
{
	int horiz = 0;
	int vert = 0;
	int aliveCount = 0;
	while (numberOfRounds > 0)		// Check number that number of rounds is still positive.
	{

		for (vert = 1; vert <= boardSize; vert++)		// Steps through array
		{
			for (horiz = 1; horiz <= boardSize; horiz++)	// Steps through array for each member
			{
				aliveCount = 0;			// Resets aliveCount to zero

				{if (currentLife[vert - 1][horiz - 1].getState() == true) //If Top Left Cell is alive
					aliveCount += 1;									//Iterates aliveCount

				if (currentLife[vert - 1][horiz].getState() == true) // If Top Cell is alive
					aliveCount += 1;

				if (currentLife[vert - 1][horiz + 1].getState() == true) // If Top Right Cell is alive
					aliveCount += 1;

				if (currentLife[vert][horiz - 1].getState() == true) // If Left Cell is alive
					aliveCount += 1;

				if (currentLife[vert][horiz + 1].getState() == true) // If Right Cell is alive
					aliveCount += 1;

				if (currentLife[vert + 1][horiz - 1].getState() == true) // If Bottom Left Cell is alive
					aliveCount += 1;

				if (currentLife[vert + 1][horiz].getState() == true)//If Bottom Cell is alive
					aliveCount += 1;

				if (currentLife[vert + 1][horiz + 1].getState() == true) //If Bottom Right Cell is alive
					aliveCount += 1;
				}
				if (executeRules(aliveCount, currentLife[vert][horiz].getState())) //calls executeRules, if it returns true
				{
					nextLife[vert][horiz].setState(true);	// Sets the cell in the next generation at the coordinate to alive
				}
				else
					nextLife[vert][horiz].setState(false);	// Sets the cell in the next generation at the coordinate to dead

			}
		}

		for (vert = 1; vert <= boardSize; vert++)
		{
			for (horiz = 1; horiz <= boardSize; horiz++)
			{
				cout << currentLife[vert][horiz].getFace() << "   ";	// Prints current generation
			}
			cout << "\n" << endl;
		}

		for (vert = 1; vert <= boardSize; vert++)
		{
			for (horiz = 1; horiz <= boardSize; horiz++)
			{
				currentLife[vert][horiz].setState(nextLife[vert][horiz].getState());	// Copies nextLife to currentLife, cell by cell
			}
		}
		numberOfRounds -= 1;	// Decrements number of rounds
		system("CLS");			// Clears screen

	}
	cout << "Final Generation: " << endl;
	for (vert = 1; vert <= boardSize; vert++)
	{
		for (horiz = 1; horiz <= boardSize; horiz++)
		{
			cout << currentLife[vert][horiz].getFace() << "   ";	// Prints current generation
		}
		cout << "\n" << endl;
	}
}

bool GameOfLife :: executeRules(unsigned int countAlive, bool currentState)
//POSTCONDITION: Returns true if the next generation of this cell should be alive, false if it should be dead
{
	if (currentState == false)		// If the cell is currently dead
	{
		if (countAlive == 3)		// If there are 3 alive cells surrounding the cell
		{
			return true;			// The cell should be alive in the next generation
		}
		else 
			return false;			// The cell should be dead in the next generation
	}
	else                   // If the cell is currently alive
	{
		if ((countAlive < 2) || (countAlive > 3))	// if there are less than 2 neighbors, or more than 3 neighbors that are alive
			return false;							// The cell should be dead
		else
			return true;							// The cell should be alive
	}
}