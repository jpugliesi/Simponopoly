#include <iostream>
#include "Game_Board.h"
#include "Space.h"
#include "Player.h"
#include "Action.h"
#include "Card.h"
#include "Bank.h"
#include "Die.h"

void occupyPieces();
int welcome();
int getOption();
int getTurnOption();
int getNumPlayers();

void getPlayerInfo();

void printInstructions(); //to implement
void printAvailablePieces(int *chosenPieces);
bool pieceIsTaken(int *chosenPieces, int choice);

int playTurn(Game_Board &theBoard, Player &thePlayer, Die d1, Die d2, int turn);
int gameOver();

const int NUM_PIECES = 10;

std::string pieces[NUM_PIECES];
int numPlayers;
Player *players;
int turn = 0;

int main(){

	occupyPieces();

	if(welcome()){

		numPlayers = getNumPlayers();
		players = new Player[numPlayers];

		getPlayerInfo();

		Game_Board theBoard(numPlayers);
		Space* go = theBoard.findSpaceByIndex(0);
		for(int i = 0; i < numPlayers; i++){
			players[i].setPosition(0);
			go->addPlayerToSpace(players[i]);
		}
		theBoard.printBoard();

		Die die1;
		Die die2;
		while(!gameOver()){

			Player *playerWithTurn = &(players[turn]);
			turn = playTurn(theBoard, *playerWithTurn, die1, die2, turn);
			theBoard.printBoard();

			if(turn == numPlayers-1){
				turn = 0;
			}else{
				turn++;
			}
			
			std::cout << players[turn].getPiece() << " is up next..." << std::endl;
			if(!getTurnOption()){
				std::cout << "Thanks for Playing" << std::endl;
				return -1;
			}
			

		}

	}

	delete [] players;
	return 1;
}

int playTurn(Game_Board &theBoard, Player &thePlayer, Die d1, Die d2, int turn){

	int v1 = d1.rollDie();
	int v2 = d2.rollDie();
	int moveValue = v1 + v2;

	std::cout << "The " << thePlayer.getPiece() << " is up!" << std::endl;
	std::cout << "Die rolled: " << v1 << " and " << v2 << "." << std::endl;
	std::cout << "The " << thePlayer.getPiece() << " advances " << moveValue << " spaces!" << std::endl;

	int index = thePlayer.getCurrentSpace();
	Space *current = theBoard.findSpaceByIndex(index);
	current->removePlayerFromSpace(thePlayer);

	thePlayer.move(moveValue);
	index = thePlayer.getCurrentSpace();
	Space *newSpace = theBoard.findSpaceByIndex(index);
	newSpace->addPlayerToSpace(thePlayer);

	return turn;
	
}

int gameOver(){
	int over = 0;
	if(turn == -1){
		over = 1;
	}

	return over; //temporary
}

void getPlayerInfo(){
	int chosenPieces[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	for(int i = 0; i < numPlayers; i++){
		printAvailablePieces(chosenPieces);
		std::cout << std::endl;
		std::cout << "Player " << i+1 << ", choose your piece: ";
		int x;

		do{

		std::cin >> x;

		if (std::cin.fail() || (x < 1 || x > NUM_PIECES)){

			std::cin.clear();
			std::cin.ignore(10000, '\n'); //clear inputs up to 10,000 characters, or first newline
			std::cout << "Invalid Choice. Choose from the available pieces: ";
			continue; //jump to while statement
		}else if(pieceIsTaken(chosenPieces, x)){
			std::cin.clear();
			std::cin.ignore(10000, '\n'); //clear inputs up to 10,000 characters, or first newline
			std::cout << "That piece is already taken. Choose a different option: ";
			continue; //jump to while statement
		}

		//a good piece is chosen
		players[i].setPiece(pieces[x-1]);
		std::cout << "\nExcellent Choice, Player " << i+1 << " is now the: " << players[i].getPiece() << std::endl << std::endl;
		chosenPieces[x-1] = 0;
		std::cin.ignore(100000, '\n'); //clear the stream
		break; //exit the loop

		} while(true);
	}
}

bool pieceIsTaken(int *chosenPieces, int choice){
	choice -= 1;
	if(chosenPieces[choice] == 1){
		return false;
	} else if(chosenPieces[choice] == 0){
		return true;
	}
	return true;
}

void printAvailablePieces(int *availablePieces){

	for(int i = 0; i < NUM_PIECES; i++){
		if(availablePieces[i] == 1){
			std::cout << "(" << i+1 << ") " << pieces[i] << std::endl;
		} else{
			std::cout << "X Taken X " << pieces[i] << std::endl;

		}
	}

}

void occupyPieces(){
	pieces[0] = "!";
	pieces[1] = "@";
	pieces[2] = "#";
	pieces[3] = "$";
	pieces[4] = "%";
	pieces[5] = "^";
	pieces[6] = "&";
	pieces[7] = "*";
	pieces[8] = "+";
	pieces[9] = "?";
}

int welcome(){
	std::cout << "***** Welcome to Simponopoly! *****" << std::endl;
	std::cout << "___________________________________" << std::endl;
	std::cout << "Choose an option to get started:" << std::endl;
	std::cout << "\t(1) Print Instructions and Play" << std::endl;
	std::cout << "\t(2) Start the GAME!!!" << std::endl;
	std::cout << "\t(3) Quit" << std::endl;

	int choice = getOption();
	switch(choice){

		case 1: printInstructions();
				return 1;
		case 2: return 1;
		case 3: return 0;

	}
	return 0;
}

void printInstructions(){

}

int getTurnOption(){

	char x;
	std::cout << "Ready to continue (y/n)? " << std::endl;

	do{

	std::cin >> x;

	if (std::cin.fail() || (x != 'y' && x != 'n')){

		std::cin.clear();
		std::cin.ignore(10000, '\n'); //clear inputs up to 10,000 characters, or first newline
		std::cout << "Please Enter a Valid Option (y, n, or enter key): ";
		continue; //jump to while statement

	}

	
	//a good integer entered
	
	std::cin.ignore(100000, '\n'); //clear the stream
	break; //exit the loop

	} while(true);
	
	int goOn;
	if(x == 'y'){
		goOn = 1;
	}else{
		goOn = 0;
	}

	return goOn;

}

int getOption(){

	int x;

	do{

	std::cin >> x;

	if (std::cin.fail() || (x < 1 || x > 3)){

		std::cin.clear();
		std::cin.ignore(10000, '\n'); //clear inputs up to 10,000 characters, or first newline
		std::cout << "Please Enter a Valid Option: ";
		continue; //jump to while statement

	}

	//a good integer entered

	std::cin.ignore(100000, '\n'); //clear the stream
	break; //exit the loop

	} while(true);

	return x;

}

int getNumPlayers(){

	std::cout << "Enter the number of players: ";
	int x;

	do{

	std::cin >> x;

	if (std::cin.fail() || (x < 2 || x > 4)){

		std::cin.clear();
		std::cin.ignore(10000, '\n'); //clear inputs up to 10,000 characters, or first newline
		std::cout << "Invalid Choice. Must be between 2 and 4 players, inclusive: ";
		continue; //jump to while statement

	}

	//a good integer entered

	std::cin.ignore(100000, '\n'); //clear the stream
	break; //exit the loop

	} while(true);

	return x;

}