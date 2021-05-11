#pragma once
#include "Player.hpp"

namespace pandemic {
	class FieldDoctor : public Player
	{
	public:
		FieldDoctor(Board& game_board, City init_city);
		~FieldDoctor();
		Player& treat(City);
		static std::string role();
	};
}