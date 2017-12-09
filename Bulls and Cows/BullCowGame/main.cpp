/*
This is the console executable that makes use of the BullCowClass.
This acts as the view in a MVC pattern, and is responsible for all user interaction. For game logic, see the FBullCowGame class.
*/
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();
void PrintGameSummary();

FBullCowGame BCGame;	//instantiate a new game

//the entry point for our application
int main() {
	
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	return 0;
}



void PrintIntro() {
	//Introduce the game
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop for the guess while the game is not won
	//and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess(); 

		//submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		//Print number of bulls and cows
		std::cout << "Bulls = "  << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n";

	}


	//TODO add a game summary
	PrintGameSummary();
	return;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again with the same word? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}

//loop continually until the user gives valid input
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";

	do {
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\nTry " << CurrentTry << " of " << BCGame.GetMaxTries() << std::endl;

		std::cout << "Enter your guess: ";
		std::getline(std::cin, Guess);

	 Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram word.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a lowercase word.\n\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); //keep looping until we get a valid input
	return Guess;

}

void  PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Well done! You won this game, bruv!\n";
	}
	else {
		std::cout << "Better luck next time, fam.\n";
	}

	return;
}