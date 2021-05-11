#include "Virologist.hpp"

namespace pandemic {
	Virologist::Virologist(Board& game_board, City init_city) : Player(game_board, init_city)
	{
		
	}
	Virologist::~Virologist()
	{
		
	}
	std::string Virologist::role()
	{
		return "Virologist";
	}
}