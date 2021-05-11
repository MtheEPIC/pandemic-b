#pragma once
#include "City.hpp"
#include <iostream>
#include <unordered_map>

namespace pandemic {
	typedef std::unordered_map<City, int> M;
	class Board
	{
	public:
		M cities_pandemic_level;
		Board();
		Board(Board&);
		int& operator[](City);
		bool is_clean();
		void remove_cures();
		void remove_stations();
	};
	std::ostream& operator<<(std::ostream& os, const Board& dt);
	
}