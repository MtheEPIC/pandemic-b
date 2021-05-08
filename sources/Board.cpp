#include "Board.hpp"

namespace pandemic {
	int& Board::operator[](City city)
	{
		return this->cities_pandemic_level[city];
	}
	bool Board::is_clean()
	{
		return true;
	}
	std::ostream& operator<<(std::ostream& os, const Board& dt)
	{
		return os;
	}
}