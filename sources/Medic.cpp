#include "Medic.hpp"

namespace pandemic {
	Medic::Medic(Board& game_board, City init_city) : Player(game_board, init_city)
	{
		
	}
	Medic::~Medic()
	{
		
	}
	Player& Medic::treat(City city)
	{
		if(this->get_pandemic_levels()[city] == 0)
		{
			throw std::logic_error("cant treat a city if there is no disease");
		}
		if(this->curr_city != city && !this->is_neighbour_city(city))
		{
			throw std::logic_error("can only treat a disease in the current and neighbour cities");	
		}
		this->set_pandemic_levels(city, 0);
		return *this;
	}
	std::string Medic::role()
	{
		return "Medic";
	}
}