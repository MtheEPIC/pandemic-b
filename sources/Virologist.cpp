#include "Virologist.hpp"

namespace pandemic {
	Virologist::Virologist(Board& game_board, City init_city) : Player(game_board, init_city)
	{
		
	}
	Virologist::~Virologist()
	{
		
	}
	Player& Virologist::treat(City city)
	{
		if(this->get_pandemic_levels()[city] == 0)
		{
			throw std::logic_error("cant treat a city if there is no disease");
		}
		if(this->curr_city != city)
		{
			if (this->has_card(city))
			{
				this->remove_card(city);
			}
			else
			{
				throw std::logic_error("can't treat a disease in a city you're not in unless you have the proper card");
			}
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
	std::string Virologist::role()
	{
		return "Virologist";
	}
}