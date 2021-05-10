#include "Board.hpp"

namespace pandemic {
	Board::Board()
	{
		
	}
	Board::Board(Board& other)
	{
		this->cities_pandemic_level = other.cities_pandemic_level;
	}
	int& Board::operator[](City city)
	{
		return this->cities_pandemic_level[city];
	}
	bool Board::is_clean()
	{
		return true;
	}
	Board Board::remove_cures()
	{
		return *this;
	}
	std::ostream& operator<<(std::ostream& os, const Board& dt)
	{
		return os;
	}
}