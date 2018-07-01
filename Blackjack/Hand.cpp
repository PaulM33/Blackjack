#include "Hand.hpp"
using namespace std;

unsigned Hand::addCard(unsigned& total, Card c) {
	return total += c.rank;
}

// Function to check the winner
string Hand::checkWinner(unsigned blackjack, unsigned dealer, unsigned player) {
	string feedback;

	// if player cards are equal to 21
	if (player == blackjack) {
		// if dealer cards are not equal to 21
		if (dealer != blackjack)
			feedback = "BLACKJACK!!! You won";
		// if dealer cards are equal to 21
		else if (dealer == blackjack)
			feedback = "PUSH!!! it's a draw";
	}
	// if player cards are not equal to 21 
	else if (player != blackjack) {
		if (player > blackjack && dealer <= blackjack)
			feedback = "BUST!!! You lost";
		else if (player > blackjack && dealer > blackjack)
			feedback = "DOUBLE BUST!!! No winner";
		else if (player < blackjack) {
			if (dealer > blackjack)
				feedback = "Congrats. You won";
			else if (dealer < blackjack && player > dealer)
				feedback = "Congrats. You Won";
			else if (dealer <= blackjack && player < dealer)
				feedback = "Sorry. You lost";
		}
	}

	return feedback;
}

// Function to calculate points
void Hand::calcPoints(unsigned blackjack, unsigned player, unsigned dealer, double& playerPot, double& dealerPot, double playerBet) {
	// if player has a blackjack
	if (player == blackjack) {
		// if dealer doesn't have a blackjack
		if (dealer != blackjack) {
			playerBet *= Hand::NATURAL;
			playerPot += playerBet;
			dealerPot += playerBet;
		}
	}
	// if player doesn't have a blackjack
	else if (player != blackjack) {
		// if player cards are over 21 and dealer cards are under or equal to 21
		if (player > blackjack && dealer <= blackjack) { 
			playerPot -= playerBet;
			dealerPot += playerBet;
		}
		// if player cards are under 21
		else if (player < blackjack) {
			// if dealer cards are over 21
			if (dealer > blackjack) {
				playerPot += playerBet;
				dealerPot -= playerBet;
			}
			// if dealer cards are under 21 and player cards are over dealer's 
			else if (dealer < blackjack && player > dealer) {
				playerPot += playerBet;
				dealerPot -= playerBet;
			}
			// if dealer cards are under or equal to 21 and player 
			else if (dealer <= blackjack && player < dealer) {
				playerPot -= playerBet;
				dealerPot += playerBet;
			}
		}
	}
}