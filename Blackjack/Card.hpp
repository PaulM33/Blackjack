#pragma once
#include <vector>
using namespace std;

// card enumeration
enum CardSuit { CLUBS, DIAMONDS, HEARTS, SPADES };
enum CardRank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK = 10, QUEEN = 10, KING = 10 };

class Card {
	using Deck = vector < Card >;

public:
	CardSuit suit;
	CardRank rank;
	Deck deck;

	int operator+(Card const& c);
};