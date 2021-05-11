#pragma once
#include "Player.hpp"

namespace pandemic {
	class OperationsExpert : public Player
	{
	public:
		OperationsExpert(Board& game_board, City init_city);
		~OperationsExpert();
		Player& build();
		static std::string role();
	};
}