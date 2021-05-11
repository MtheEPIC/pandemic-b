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
		if(this->curr_city != city)
		{
			throw std::logic_error("can only treat a disease in the current and neighbour cities");	
		}
		this->set_pandemic_levels(city, 0);
		return *this;
	}
	void Medic::auto_cure(City city)
	{
		if(this->is_cure(city)){
			this->set_pandemic_levels(city, 0);
		}
	}
	Player& Medic::drive(City dest_city){
		Player::drive(dest_city);
		this->auto_cure(dest_city);
		return *this;
	}

	Player& Medic::fly_direct(City dest_city){
		Player::fly_direct(dest_city);
		this->auto_cure(dest_city);
		return *this;
	}

	Player& Medic::fly_charter(City dest_city){
		Player::fly_charter(dest_city);
		this->auto_cure(dest_city);
		return *this;
	}

	Player& Medic::fly_shuttle(City dest_city){
		Player::fly_shuttle(dest_city);
		this->auto_cure(dest_city);
		return *this;
	}
	std::string Medic::role()
	{
		return "Medic";
	}
}