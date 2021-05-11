#pragma once
#include "Player.hpp"

namespace pandemic {
	class Scientist : public Player
	{
	public:
		Scientist(Board& game_board, City init_city, int card_for_cure);
		~Scientist();
		static std::string role();
	};
}