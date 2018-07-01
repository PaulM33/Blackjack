#include "Card.hpp"

int Card::operator+(Card const& c) {
	return (this->rank + c.rank);
}