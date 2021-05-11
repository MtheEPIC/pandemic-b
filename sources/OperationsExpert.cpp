#include "OperationsExpert.hpp"

namespace pandemic {
	OperationsExpert::OperationsExpert(Board& game_board, City init_city) : Player(game_board, init_city)
	{
		
	}
	OperationsExpert::~OperationsExpert()
	{
		
	}
	Player& OperationsExpert::build()
	{
		if (this->has_research_station(this->curr_city))
		{
			return *this;
		}
		this->research_stations.push_back(this->curr_city);
		return *this;
	}
	std::string OperationsExpert::role()
	{
		return "OperationsExpert";
	}
}