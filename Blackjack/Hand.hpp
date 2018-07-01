#pragma once

#include <vector>
#include "Card.hpp"
using namespace std;

class Hand {
	using PlayerHand = vector < Card >;
	using DealerHand = vector < Card >;
	double const NATURAL = 1.5;
public:
	PlayerHand playerHand;
	DealerHand dealerHand;

	unsigned const BLACKJACK = 21;
	double const MAX_BET = 200.00;
	double const MIN_BET = 20.00;
	double playerPot = 1000.00;
	double dealerPot = 1000.00;
	double playerBet = 0.00;
	unsigned playerTotal;
	unsigned dealerTotal;

	unsigned addCard(unsigned&, Card);
	string checkWinner(unsigned, unsigned, unsigned);
	void calcPoints(unsigned, unsigned, unsigned, double&, double&, double);
};