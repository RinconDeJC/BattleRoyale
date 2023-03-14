#include "Person.h"

#include <string>
#include <vector>
#include <iostream>



Person::Person() :
	_name(""),
	_kills(0),
	_infected(false),
	_immune(false), 
	_n_infected(0),
	_team("")
{}
;

Person::Person(std::string name, std::string team) :
	_name(name), 
	_kills(0), 
	_infected(false),
	_immune(false), 
	_n_infected(0), 
	_score(name, team),
	_team(team)
{
	_prof = Profession::getProfession();
	_score._prof = _prof.getStringVal();
}

Person::Person(std::string name, std::string team, std::string profession) : 
	_name(name), 
	_kills(0), 
	_infected(false), 
	_immune(false), 
	_n_infected(0), 
	_score(name, team),
	_team(team)
{
	try {
		_prof = Profession::valueOf(profession);
	}
	catch (std::domain_error) {
		_prof = Profession::getProfession();
#ifdef DEBUG
		std::cout << "Se le ha a asignado a " << _name << " una nueva profesion: ";
		std::cout << _prof.getStringVal() << '\n';
#endif
	}
	_score._prof = _prof.getStringVal();
}


Person::Person(Person const& other) 
{
	copia(other);
}

Person::~Person()
{
	freePerson();
}

Person & Person::operator=(Person const& other) 
{
	if (this != &other) {
		copia(other);
	}
	return *this;
}

bool Person::operator==(Person const & other) const 
{
	return _name == other._name;
}

bool Person::operator!=(Person const & other) const 
{
	return !(*this == other);
}

bool Person::operator<(Person const & other) const 
{
	return _name < other._name;
}

std::string Person::name()const 
{
	return _name;
}

std::string Person::team() const
{
	return _team;
}

int Person::kills() const 
{
	return _kills;
}

bool Person::infected() const 
{
	return _infected;
}

bool Person::immune() const 
{
	return _immune;
}

int Person::days_infected() const 
{
	return _n_infected;
}

void Person::beatInfection()
{
	_immune = true;
	_infected = false;
}

void Person::makeImmune() 
{
	_immune = true;
}

void Person::infect() 
{
	if(!_immune)
		_infected = true;
}

const Person::Score & Person::score() const 
{
	return _score;
}

Profession Person::profession() const
{
	return _prof;
}

void Person::has_killed(Person const& other) 
{
	_score._kills.push_back(other._name);
	++_kills;
}

void Person::has_infected()
{
	++this->_score._n_people_infected;
}

void Person::one_day_infected()
{
	++this->_score._n_days_infected;
}

void Person::killed_by(Person const& other, int time) 
{
	_score._killed_by = other._name;
	_score._n_days_survived = time;
}

void Person::killed_by(std::string const& infection, int time)
{
	_score._killed_by = infection;
	_score._n_days_survived = time;
}

void Person::serialize(std::ostream & output, bool alive)
{
	output << _name << '\n';
	output << _team << '\n';
	output << _prof.getStringVal() << " " << _kills << " " << _n_infected << " " <<
		(_infected ? 'T' : 'F') << " " << (_immune ? 'T' : 'F') << '\n';
	_score.serialize(output, alive);
	output << '\n';
}

Person Person::load(std::istream & in)
{
	Person ret_val;
	std::getline(in, ret_val._name);
	std::getline(in, ret_val._team);
	std::string aux;
	in >> aux;
#ifdef DEBUG
	std::cout << aux << " " << "PERSON: " << ret_val._name << '\n';
#endif
	ret_val._prof = Profession::valueOf(aux);
	in >> ret_val._kills >> ret_val._n_infected;
	char aux_c;
	in >> aux_c;
	ret_val._infected = aux_c == 'T';
	in >> aux_c;
	ret_val._immune = aux_c == 'T';
	in.get();
	ret_val._score.load(in);
	in.get();
	return ret_val;
}

// protected

void Person::copia(Person const & other) 
{
	_score = Person::Score(other._score);
	_name = other._name;
	_team = other._team;
	_kills = other._kills;
	_infected = other._infected;
	_immune = other._immune;
	_n_infected = other._n_infected;
	_prof = other._prof;
}

void Person::freePerson()
{
	_score._kills.clear();
}

void Person::Score::serialize(std::ostream & output, bool alive)
{
	output << _name << '\n';
	output << _team << '\n';
	output << _prof << '\n';
	if (alive)
		output << "ALIVE" << '\n';
	else
		output << _killed_by << '\n';
	output << _n_days_infected << " " << _n_people_infected << " " << (alive ? -1 : _n_days_survived) << '\n';
	output << _kills.size() << '\n';
	for (std::string s : _kills) {
		output << s << '\n';
	}
}

void Person::Score::load(std::istream & in)
{
	std::getline(in, _name);
	std::getline(in, _team);
	in >> _prof;
	std::string aux;
	in.get();
	std::getline(in, _killed_by);
	in >> _n_days_infected >> _n_people_infected >> _n_days_survived;
	int size;
	in >> size;
	for (int i = 0; i < size; ++i) {
		in.get();
		std::getline(in, aux);
		_kills.push_back(aux);
	}
	if (size == 0) in.get();

}
