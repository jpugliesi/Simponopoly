//Space.cpp
#include "Space.h"
#include <string>
#include <sstream>

	/***** Constructors *****/

	Space::Space(){
		ownable = true;
		numPlayersOnSpace = 0;
		//NOT PERMANENT: 
	}
	Space::Space(std::string newName, int newNextSpace, bool canOwn){
		numPlayersOnSpace = 0;
		name = newName;
		ownable = canOwn;
		//action = theAction; need to make a copy function for this to work 
		nextSpace = newNextSpace;
	}
	Space::~Space(){

	}

	/***** Functions *****/

	//returns whether or not a space can be owned
	bool Space::isOwnable(){
		return ownable;
	}

	//sets the name of the space
	void Space::setName(std::string newName){
		name = newName;
	}

	//gets the name of the space
	std::string Space::getName(){
		return name;
	}

	void Space::setAction(Action anAction){
		//Need to make a copy function within the action class
	}

	void Space::setNextSpace(int newNextSpace){
		nextSpace = newNextSpace;
	}

	//adds player aPlayer to the currentPlayers array
	void Space::addPlayerToSpace(Player aPlayer){
		for(int i = 0; i < 4; i++){
			if(currentPlayers[i].getPiece() == ""){
				currentPlayers[i] = aPlayer;
				numPlayersOnSpace++;
				break;
			}
		}
		//currentPlayers[numPlayersOnSpace++] = aPlayer;
	}

	//returns the array of players currently on the space
	Player* Space::getPlayersOnSpace(){
		return currentPlayers; //could be wrong, check back that pointers are good
	}

	//returns a string of the pieces of players currently on the space
	std::string Space::playersOnSpaceToString(){
		std::stringstream ss;
		for(int i = 0; i < 4; i ++){
			if(currentPlayers[i].getPiece() != ""){
				ss << currentPlayers[i].getPiece() << " ";
			}
		}
		std::string result = ss.str();
		return result;
	}

	//removes a player from the space
	void Space::removePlayerFromSpace(Player aPlayer){
		Player empty;
		for(int i = 0; i < 4; i++){
			if(currentPlayers[i].getPiece() == aPlayer.getPiece()){
				currentPlayers[i] = empty;
				numPlayersOnSpace--;
				break;
			}
		}
	}

	std::string Space::getOwner(){
		return owner.getPiece();
	}
	void Space::setOwner(Player newOwner){
		owner = newOwner;
	}



