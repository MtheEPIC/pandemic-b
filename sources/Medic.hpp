#pragma once
#include "Player.hpp"

namespace pandemic {
	class Medic : public Player
	{
	public:
		Medic(Board& game_board, City init_city);
		~Medic();
		Player& treat(City);
		static std::string role();
	};
}