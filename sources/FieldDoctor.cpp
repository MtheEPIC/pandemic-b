#include "FieldDoctor.hpp"

namespace pandemic {
	FieldDoctor::FieldDoctor(Board& game_board, City init_city) : Player(game_board, init_city)
	{
		
	}
	FieldDoctor::~FieldDoctor()
	{
		
	}
	Player& FieldDoctor::treat(City city)
	{
		if(this->get_pandemic_levels()[city] == 0)
		{
			throw std::logic_error("cant treat a city if there is no disease");
		}
		if(this->curr_city != city && !this->is_neighbour_city(city))
		{
			throw std::logic_error("can only treat a disease in the current and neighbour cities");	
		}
		if (this->cures.contains(this->card_colors[city]))
		{
			this->set_pandemic_levels(city, 0);
		}
		else
		{
			this->set_pandemic_levels(city, -1);
		}
		return *this;
	}
	std::string FieldDoctor::role()
	{
		return "FieldDoctor";
	}
}