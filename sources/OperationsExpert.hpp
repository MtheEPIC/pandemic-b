#pragma once
#include "Player.hpp"

namespace pandemic {
	class OperationsExpert : public Player
	{
	public:
		OperationsExpert(Board, City);
		~OperationsExpert();
	};
}