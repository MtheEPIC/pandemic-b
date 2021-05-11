#include "Scientist.hpp"

namespace pandemic {
	Scientist::Scientist(Board& game_board, City init_city, int card_for_cure) : Player(game_board, init_city, card_for_cure)
	{
		
	}
	Scientist::~Scientist()
	{
		
	}
	std::string Scientist::role()
	{
		return "Scientist";
	}
}