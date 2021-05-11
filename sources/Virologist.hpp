#pragma once
#include "Player.hpp"

namespace pandemic {
	class Virologist : public Player
	{
	public:
		Virologist(Board& game_board, City init_city);
		~Virologist();
		Player& treat(City);
		static std::string role();
	};
}