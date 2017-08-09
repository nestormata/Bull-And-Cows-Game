#include "FBullCowGame.h"
#include <map>

#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> wordLengthToMaxTries {
		{3, 4}, {4, 7}, {5, 10}, {6, 16}, {7, 20}
	};
	return wordLengthToMaxTries[MyHiddenWord.length()]; 
}


void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "ant";
	MyCurrentTry = INITIAL_TRY;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	if (!IsIsogram(guess)) {
		return EGuessStatus::Not_Isogramm;
	}
	if (!IsLowerCase(guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	if (!IsSameLengthAsHiddenWord(guess)) {
		return EGuessStatus::Wrong_Length;
	}
	return EGuessStatus::OK;
}

// Receives a VALID guess, increments turn, and returns counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	MyCurrentTry++;
	FBullCowCount counts;
	int32 wordLenght = MyHiddenWord.length(); // We assume same lenght as guess

	// loop through all letters in the hidden word
	for (int32 hiddeCounter = 0; hiddeCounter < wordLenght; hiddeCounter++) {
		// loop through all letters in the guess
		for (int32 guessCounter = 0; guessCounter < wordLenght; guessCounter++) {
			// compare letters against the hidden word
			if (MyHiddenWord[hiddeCounter] == guess[guessCounter]) {
				if (hiddeCounter == guessCounter) {
					// if they match then
					counts.Bulls++;
				}
				else {
					// if they don't match then
					counts.Cows++;
				}
			}
		}
	}
	// If all letters are bulls then all letters are in the right place, player won
	if (counts.Bulls == wordLenght) {
		bGameIsWon = true;
	}
	return counts;
}

bool FBullCowGame::IsLowerCase(FString word) const
{
	if (word.length() < 1) { return true; }

	for (auto currentLetter : word) {
		if (!islower(currentLetter)) {
			return false; // If one letter is found as uppercase then we are done
		}
	}
	return true;
}

bool FBullCowGame::IsSameLengthAsHiddenWord(FString guess) const
{
	return GetHiddenWordLength() == guess.length();
}

bool FBullCowGame::IsIsogram(FString word) const
{
	if (word.length() <= 1) { return true; }

	TMap<char, bool> lettersSeen;
	for (auto currentLetter : word) {
		currentLetter = tolower(currentLetter);
		if (lettersSeen[currentLetter]) {
			return false; // We found a repeated letter, this is not an isogramm
		}
		lettersSeen[currentLetter] = true;
	}

	return true;
}
