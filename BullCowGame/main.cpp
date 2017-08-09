/*
 This is the console executable, that makes use of the BullCow class.
 This acts as the view in the MVC pattern, and is responsible for all
 user interaction. For game logice see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// functions prototypes
void PrintIntro();
FText GetValidGuess();
void PlayGame();
void PrintGuess(FText guess, FBullCowCount counts);
bool AskToPlayAgain();
bool CheckForErrorsAndReport(EGuessStatus status);
void PrintGameSummary();

FBullCowGame game; // Instantiate a new game, which we reuse across plays


int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	return 0;
}

// A single play to completetion
void PlayGame()
{
	game.Reset();
	int32 maxTries = game.GetMaxTries();
	int32 currentTries = game.GetCurrentTry();

	FText guess = "";
	while (!game.IsGameWon() && currentTries <= maxTries)
	{
		guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount counts = game.SubmitValidGuess(guess);
		// Print number of bulls and cows
		PrintGuess(guess, counts);
		currentTries = game.GetCurrentTry();
	}
	PrintGameSummary();
	return;
}

void PrintGameSummary()
{
	if (game.IsGameWon()) {
		std::cout << "== Congratulations!! You dit it!!! ==";
	}
	else {
		std::cout << "== Better luck next time. ==";
	}
	std::cout << std::endl << std::endl;
	return;
}

bool CheckForErrorsAndReport(EGuessStatus status)
{
	switch (status)
	{
		case EGuessStatus::Not_Isogramm:
			std::cout << "Please enter a word without repeating letters" << std::endl;
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << game.GetHiddenWordLength() << " letter word." << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter only lowercase letters" << std::endl;
			break;
		case EGuessStatus::OK:
		default:
			return true;
			break;
	}
	std::cout << std::endl;
	return false;
}

// Ask the guess
FText GetValidGuess()
{	
	int32 currentTry = game.GetCurrentTry();
	FText guess = "";
	bool isGuessValid = false;
	do {
		std::cout << "Try " << currentTry << " of " << game.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, guess);

		EGuessStatus status = game.CheckGuessValidity(guess);
		isGuessValid = CheckForErrorsAndReport(status);
	} while (!isGuessValid);
	return guess;
}

// Repeat the guess back
void PrintGuess(FText guess, FBullCowCount counts)
{
	//std::cout << "You entered: " << guess << std::endl;
	std::cout << "Bulls = " << counts.Bulls;
	std::cout << ". Cows = " << counts.Cows << std::endl << std::endl;
	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? ";
	FText response = "";
	std::getline(std::cin, response);
	return response.length() > 0 && (response[0] == 'y' || response[0] == 'Y');
}

void PrintIntro()
{
	int32 hiddenWordLength = game.GetHiddenWordLength();

	std::cout << "Welcome to Bulls and Cows, a fun word game" << std::endl;
	std::cout << "Can you guess the " << hiddenWordLength;
	std::cout << " letter isogram I'm thinking off?" << std::endl;
	std::cout << std::endl;

	return;
}
