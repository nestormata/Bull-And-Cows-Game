/*
 The game logic (no view code nor direct user interation).
 The game is a simple guess the word game based on Mastermind
*/
#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	OK,
	Not_Isogramm,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	const int32 INITIAL_TRY = 1;
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const;
	bool IsGameWon() const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	bool bGameIsWon;
	FString MyHiddenWord;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
	bool IsSameLengthAsHiddenWord(FString) const;
};