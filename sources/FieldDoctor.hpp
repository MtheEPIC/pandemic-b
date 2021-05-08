#pragma once
#include "Player.hpp"

namespace pandemic {
	class FieldDoctor : public Player
	{
	public:
		FieldDoctor(Board, City);
		~FieldDoctor();
	};
}