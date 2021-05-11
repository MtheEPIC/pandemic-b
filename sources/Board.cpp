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
		if (this->cities_pandemic_level.empty())
		{
			return true;
		}
		for (auto i = this->cities_pandemic_level.begin(); i != this->cities_pandemic_level.end(); i++)
		{
			if (i->second != 0)
			{
				return false;
			}
		}
		return true;
	}
	void Board::remove_cures()
	{
		
	}
	void Board::remove_stations()
	{
		
	}
	std::ostream& operator<<(std::ostream& os, const Board& dt)
	{
		return os;
	}
}