#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include "Card.hpp"
#include "Hand.hpp"
using namespace std;

// card enumeration
//enum CardSuit { CLUBS, DIAMONDS, HEARTS, SPADES };
//enum CardRank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK = 10, QUEEN = 10, KING = 10 };

// overload console output operator
ostream& operator << (ostream& os, Card const& card) {
	string strSuit;

	switch (card.suit) {
	case CLUBS:
		strSuit = "Clubs";
		break;
	case DIAMONDS:
		strSuit = "Diamonds";
		break;
	case HEARTS:
		strSuit = "Hearts";
		break;
	case SPADES:
		strSuit = "Spades";
		break;
	}

	static char const* ranks[] = {
		"", "ACE", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"
	};

	os << ranks[card.rank] << " of " << strSuit;
	return os;
}

Card tmpCard;
Hand tmpHand;

int main(int argc, char* argv[]) {
	// check argument count
	if (argc != 2) {
		cout << "USAGE: Blackjack.exe <string>" << endl;
		return -1;
	}

	string player = argv[1];
	bool retry = true;

	// opening statement
	cout << "Hello " << player << "\n" << endl;

	do {
		tmpCard.deck.clear();
		tmpHand.playerHand.clear();
		tmpHand.dealerHand.clear();

		// create deck
		for (int suit = SPADES; suit >= CLUBS; --suit) {
			for (int rank = ACE; rank <= KING; ++rank) {
				tmpCard.deck.push_back(Card{ (CardSuit)suit, (CardRank)rank });
			}
		}

		// shuffle deck
		std:shuffle(tmpCard.deck.begin(), tmpCard.deck.end(), default_random_engine((unsigned)time(0)));

		//cout << endl;

		// dealer's hand
		for (size_t i = 0; i < 2; ++i)
			tmpHand.dealerHand.push_back(tmpCard.deck[i]);

		// remove dealt cards
		for (size_t i = 0; i < 2; ++i)
			tmpCard.deck.erase(tmpCard.deck.begin());

		// player's hand
		for (size_t i = 0; i < 2; ++i) {
			// shuffle the deck
			std::shuffle(tmpCard.deck.begin(), tmpCard.deck.end(), default_random_engine((unsigned)time(0)));

			// deal card to player
			tmpHand.playerHand.push_back(tmpCard.deck[i]);
		}

		// remove dealt cards
		for (size_t i = 0; i < 2; ++i)
			tmpCard.deck.erase(tmpCard.deck.begin());

		// get card totals
		tmpHand.playerTotal = tmpHand.playerHand[0] + tmpHand.playerHand[1];
		tmpHand.dealerTotal = tmpHand.dealerHand[0] + tmpHand.dealerHand[1];

		// reveal cards
		// dealer's other card is the hole card
		cout << "Dealer's hand: " << endl;
		cout << tmpHand.dealerHand[0] << "\n" << endl;

		cout << player << "'s hand: " << endl;
		cout << tmpHand.playerHand[0] << "\n" << tmpHand.playerHand[1] << "\n" << endl;

		if (tmpHand.playerTotal <= tmpHand.BLACKJACK) {
			unsigned playerAction;

			do {
				bool action = false;

				do {
					// ask for a hit or stand
					cout << "1-Hit  2-Stand" << endl;
					cin >> playerAction;

					if (playerAction == 1 || playerAction == 2)
						action = false;
					else {
						action = true;
						cin.clear();
						cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
						cout << "Please select 1 or 2" << endl;
					}

				} while (action == true);

				cout << endl;

				// if player chose to hit
				if (playerAction == 1) {
					// add card to player's hand
					for (size_t i = 0; i < 1; ++i) {
						tmpHand.playerHand.push_back(tmpCard.deck[i]);

						// calculate player's total
						tmpHand.addCard(tmpHand.playerTotal, tmpCard.deck[i]);
					}

					// remove the dealt cards
					for (size_t i = 0; i < 1; ++i)
						tmpCard.deck.erase(tmpCard.deck.begin());

					// print player's hand
					cout << player << "'s hand: " << endl;
					for (auto u : tmpHand.playerHand)
						cout << u << endl;

					cout << endl;
				}

			} while (tmpHand.playerTotal <= tmpHand.BLACKJACK && playerAction == 1);


			// if the player stand's or is bust
			if (playerAction == 2 || tmpHand.playerTotal > tmpHand.BLACKJACK) {
				cout << "Dealer's Hand: " << endl;
				cout << tmpHand.dealerHand[0] << "\n" << tmpHand.dealerHand[1] << "\n" << endl;

				if (tmpHand.dealerTotal < 17) {
					do {
						cout << "dealer hits" << "\n" << endl;

						// add card to dealer's hand
						for (size_t i = 0; i < 1; ++i) {
							tmpHand.dealerHand.push_back(tmpCard.deck[i]);

							// calculate dealer's total
							tmpHand.addCard(tmpHand.dealerTotal, tmpCard.deck[i]);
						}

						// remove dealt card
						for (size_t i = 0; i < 1; ++i)
							tmpCard.deck.erase(tmpCard.deck.begin());

						// print dealer's hand
						cout << "Dealer's hand: " << endl;
						for (auto p : tmpHand.dealerHand)
							cout << p << endl;

						cout << endl;

					} while (tmpHand.dealerTotal < 17);
				}
			}
		}

		// reveal the winner
		cout << tmpHand.checkWinner(tmpHand.BLACKJACK, tmpHand.dealerTotal, tmpHand.playerTotal) << endl;

		// ask user if they would like to play again
		bool invalidRetry = true;
		unsigned selectRetry = 0;

		do {
			cout << "1-Retry 2-Quit" << endl;
			cin >> selectRetry;

			if (selectRetry == 1) {
				invalidRetry = false;
				retry = true;
			}
			else if (selectRetry == 2) {
				invalidRetry = false;
				retry = false;
				cout << "GoodBye :)" << endl;
			}
			else {
				invalidRetry = true;
				cout << "Please select (1/2)" << endl;
			}
			
		} while (invalidRetry == true);

	} while (retry == true);
}