#include "PlayersList.h"
#include "Game.h"
#include "Probability.h"
#include <cmath>
#include <assert.h>

PlayersList::PlayersList() : 
	_n_alive(0), 
	_n_eliminated(0), 
	_n_vulnerable(0), 
	_n_infected(0), 
	_n_immune(0), 
	_n_doctors(0), 
	_vaccine(false) 
{}
;

PlayersList::~PlayersList()
{
	_alive.clear();
	_eliminated.clear();
	events = std::queue<Event>();
}

PlayersList & PlayersList::operator=(PlayersList & other)
{
	if (this != &other) {
		other._alive.clear();
		other._eliminated.clear();
	}
	return *this;
}

void PlayersList::reset()
{
	_alive.clear();
	_eliminated.clear();
	_n_alive = _n_eliminated = _n_vulnerable = _n_infected = _n_immune = _n_doctors = 0;
	_vaccine = false;
}

void PlayersList::resetEvents()
{
	events = std::queue<Event>();
}

const std::queue<Event> PlayersList::turnEvents() const
{
#ifdef DEBUG
	std::cout << "VULNERABLE: " << _n_vulnerable << " INFECTED: " << _n_infected << " IMMUNE: " << _n_immune << '\n';
#endif
	return events;
}

const std::vector<Person::Score> PlayersList::aliveScore() const
{
	std::vector<Person::Score> ret_val;
	for (Person p : _alive) {
		ret_val.push_back(p.score());
	}
	return ret_val;
}

const std::vector<Person::Score> PlayersList::eliminatedScore() const
{
	std::vector<Person::Score> ret_val;
	for (Person p : _eliminated) {
		ret_val.push_back(p.score());
	}
	return ret_val;
}

int PlayersList::remaining() const
{
	return _alive.size();
}

bool PlayersList::loadNew(std::istream & _in)
{
	std::string name, profession, team;
	getline(_in, name);
	while (!_in.fail()){
		getline(_in, team);
		//If a profession is specified in the next line
		getline(_in, profession);
		if (profession != "\n") {
			//To uppper the profession
			for (char & c : profession)
				c = toupper(c);
			addPlayer({ name, team, profession });
		}
		else {
			addPlayer({ name, team });
		}
		getline(_in, name);
	}
	//After all players have been added we sort the array
	//It will use operator< defined in Person.cpp (by name)
	std::sort(_alive.begin(), _alive.end());

	//After sortin the array, we eliminate duplicated names, no cheating allowed
	auto it_1 = _alive.begin();
	auto it_2 = _alive.begin();
	if(it_2 != _alive.end())
		++it_2;
#ifdef DEBUG
	if (it_1 == it_2) {
		std::cout << "PUNTEROS EMPIEZAN IGUAL\n";
	}
	if (it_1->name() == it_2->name()) {
		std::cout << "NOMBRES EMPIEZAN IGUAL\n";
	}
#endif
	while (it_2 != _alive.end()) {
		if (*it_1 == *it_2) {
#ifdef DEBUG
			std::cout << "ELIMINACION DE DOBLES: " << it_2->name() <<  "\nVULNERABLE: " << _n_vulnerable << " INFECTED: " << _n_infected << " IMMUNE: " << _n_immune << '\n';
#endif
			it_2 = _alive.erase(it_2);
			--_n_alive;
			--_n_vulnerable;

		}

		else {
			++it_1;
			++it_2;
		}
	}
#ifdef DEBUG
	std::cout << "VULNERABLE: " << _n_vulnerable << " INFECTED: " << _n_infected << " IMMUNE: " << _n_immune << '\n';
#endif
	//Infect some players
	int index;
	for (int i = 0; i < Game::INITIAL_INFECTED; ++i) {
		index = rand() % _alive.size();
		--_n_vulnerable;
		++_n_infected;
		_alive[index].infect();
		//EVENT
		events.push({ Event::Type::_NATURAL_INFECTION, 0, _alive[index].score() });
	}

	// Create the teams
	for (int i = 0; i < _n_alive; ++i) {
		_teams.addPlayer(_alive[i].team(), _alive[i]);
	}
	_teams.calculateFairProbModifier();

	return true;
#ifdef DEBUG
	std::cout << "VULNERABLE: " << _n_vulnerable << " INFECTED: " << _n_infected << " IMMUNE: " << _n_immune << '\n';
#endif
}

void PlayersList::loadSave(std::istream & _in)
{
	_in >> _n_vulnerable >> _n_infected >> _n_immune >> _n_doctors;
	char aux_c;
	_in >> aux_c;
	_vaccine = aux_c == 'Y';
	_in >> _n_alive;
	_in.get();
	_alive.reserve(_n_alive);
	for (int i = 0; i < _n_alive; ++i) {
		_alive.push_back(Person::load(_in));
	}
	_in >> _n_eliminated;
	_in.get();
	_eliminated.reserve(_n_eliminated);
	for (int i = 0; i < _n_eliminated; ++i) {
		_eliminated.push_back(Person::load(_in));
	}

	for (int i = 0; i < _n_alive; ++i) {
		_teams.addPlayer(_alive[i].team(), _alive[i]);
	}
	for (int i = 0; i < _n_eliminated; ++i) {
		_teams.addPlayer(_eliminated[i].team(), _eliminated[i]);
	}
	_teams.calculateFairProbModifier();

}

bool PlayersList::finished() const
{
	return _alive.size() == 1;
}

Person::Score PlayersList::winner() const
{
	return _alive.front().score();
}

void PlayersList::simulate(int _time)
{
	int index_1;
	int index_2;
	do {
		//Chose the players about to fight
		index_1 = rand() % _alive.size();
		index_2 = rand() % _alive.size();
		while (index_1 == index_2)
			index_2 = rand() % _alive.size();
#ifdef DEBUG
		assert (_alive[index_1] != _alive[index_2]);


		if (_alive[index_1].name() == _alive[index_2].name())
			throw std::domain_error("Mismo jugador en duelo");
#endif
		//repeat until a duel has been finished
	} while (!duel(_alive[index_1], _alive[index_2], _time));
}

void PlayersList::curePlayers(int _time)
{

	if (_alive.size() <= Game::ONLY_DUELS)
		return;
	for (Person & p : _alive) {
		//Players get cured by themselves
		if (p.infected() && Probability::naturallyCurePlayer(p, _n_doctors)) {
			--_n_infected;
			++_n_immune;
			p.beatInfection();
			//EVENT
			events.push({Event::Type::_GET_CURED, _time, p.score()});
		}
	}
}

void PlayersList::checkInfections(int _time)
{
	if (_alive.size() <= Game::ONLY_DUELS)
		return;
	auto it = _alive.begin();
	try {
		while (it != _alive.end()) {
			if (it->infected()) {
				if (Probability::eliminateFromInfection(*it, _teams.fairProbModifier(it->team()), _n_doctors)) {
					//EVENT
					events.push({ Event::Type::_INFECTION_ELIMINATION, _time, it->score() });
					it->killed_by(std::string("LA ENFERMEDAD"), _time);
					it = eliminatePlayer(it);
					
				}
				else {
					it->one_day_infected();
					++it;
				}
			}

			else if (Probability::naturallyInfect(_n_infected, _n_alive, _n_doctors, _n_vulnerable)) {
				--_n_vulnerable;
				++_n_infected;
				it->infect();
				//EVENT
				events.push({ Event::Type::_NATURAL_INFECTION, _time, it->score() });
				++it;
			}
			else
				++it;
		}
	}
	catch (std::exception & e) {
#ifdef PREVENTION
		system("pause");
#endif
	}
}

void PlayersList::vaccinatePlayers(int _time)
{
	if (_alive.size() <= Game::ONLY_DUELS)
		return;
	if (_vaccine) {
		for (Person & p : _alive) {
			if (!p.infected() && !p.immune() && Probability::vaccinatePlayer(_n_alive, _n_infected)) {
				--_n_vulnerable;
				++_n_immune;
				p.makeImmune();
				//The ROBBERS and the POLITICIANS steal the vaccine if they are vaccinated
				if (p.profession() == Profession::ROBBER || p.profession() == Profession::POLITICIAN) {
					_vaccine = false;
					//EVENT
					events.push({ Event::Type::_STEAL_VACCINE, _time, p.score() });
					break;
				}
				else {
					//EVENT
					events.push({ Event::Type::_GET_VACCINATED, _time, p.score() });
				}
			}
		}
	}
}

void PlayersList::findVaccine(int _time)
{
	if (_alive.size() <= Game::ONLY_DUELS)
		return;
	//VACCINE releated curing
	if (!_vaccine && Probability::findCure(_n_doctors)) {
		_vaccine = true;
		//EVENT
		events.push({ Event::Type::_FIND_VACCINE, _time });
	}
}

std::vector<Person>::iterator PlayersList::eliminatePlayer(Person const & p)
{
	auto it = std::lower_bound(_alive.begin(), _alive.end(), p);
	try {
		if (it != _alive.end() && *it == p) {
			assert(p == *it);
			return eliminatePlayer(it);
		}
	}
	catch (std::exception & e) {
#ifdef PREVENTION
		system("pause");
#endif
	}
	

	return std::vector<Person>::iterator();
}

void PlayersList::serialize(std::ostream & output)
{
	output << _n_vulnerable << " " << _n_infected << " " << _n_immune << 
		" " << _n_doctors << " " << (_vaccine ? 'Y' : 'N') << '\n';
	//ALIVE
	output << _n_alive << '\n';
	for (Person p : _alive) {
		p.serialize(output, true);
	}
	//ELIMINATED
	output << _n_eliminated << '\n';
	for (Person p : _eliminated) {
		p.serialize(output, false);
	}
}

std::vector<std::pair<Profession, std::vector<std::pair<std::string, std::string>>>> PlayersList::profession()
{
	std::vector<std::pair<Profession, std::vector<std::pair<std::string, std::string>>>> ret_val = std::vector<std::pair<Profession, std::vector<std::pair<std::string, std::string>>>>();

	for (Profession p : Profession::getValues()) {
		ret_val.push_back(std::make_pair(p, std::vector<std::pair<std::string, std::string>>()));
	}
	for (auto player = _alive.begin(); player != _alive.end(); ++player) {
		int i = 0;
		bool found = false;
		while(i < ret_val.size() && !found){
			if (ret_val[i].first == player->profession()) {
				ret_val[i].second.push_back({ player->name(), player->team() });
				found = true;
			}
			++i;
		}
	}

	return ret_val;
}

const std::unordered_map<std::string, std::vector<Person>>& PlayersList::team_list() const
{
	return _teams.team_list();
}

std::vector<Person>::iterator PlayersList::eliminatePlayer(std::vector<Person>::iterator & it)
{
	//Counters update
	if (it->profession() == Profession::DOCTOR) --_n_doctors;
	if (it->infected()) --_n_infected;
	else if (it->immune()) --_n_immune;
	else --_n_vulnerable;
	++_n_eliminated;
	--_n_alive;
	try {
		_eliminated.push_back(*it);
	}
	catch (std::exception & e) {
#ifdef PREVENTION
		system("pause");
#endif
	}


	return  _alive.erase(it);
}

#ifdef DEBUG
void PlayersList::writeAlive()
{
	for (Person p : _alive) {
		std::cout << p.score()._name << " ," << p.profession().getStringVal()<< '\n';
	}
	std::cout << "DOCTORS: " << _n_doctors << '\n';
}

void PlayersList::writeEliminated()
{
	for (Person p : _eliminated) {
		std::cout << p.score()._name << " ," << p.profession().getStringVal() << '\n';
	}
	std::cout << "DOCTORS: " << _n_doctors << '\n';
}
#endif

//PROTECTED

void PlayersList::addPlayer(Person const & p)
{
	_alive.push_back(p);
	++_n_alive;
	++_n_vulnerable;
	if (p.profession() == Profession::DOCTOR) {
		++_n_doctors;
	}
	//EVENT
	Event e = Event(Event::Type::_NEW_PLAYER, 0, p.score());
	const Person::Score* s = &p.score();
	events.push(e);
}

bool PlayersList::duel(Person & p1, Person & p2, int _time)
{
	//Fleeing chance for pizza man
	if (p1.profession() == Profession::PIZZA_MAN
		&&
		Probability::fleeProb())
	{
		//EVENT
		events.push({ Event::Type::_PIZZA_FLEE, _time, p1.score(), p2.score() });
		return false;
	}

	if (p2.profession() == Profession::PIZZA_MAN
		&&
		Probability::fleeProb())
	{
		//EVENT
		events.push({ Event::Type::_PIZZA_FLEE, _time, p2.score(), p1.score() });
		return false;
	}

	//DUEL
	bool firstWins = Probability::firstWins(p1, _teams.fairProbModifier(p1.team()), p2, _teams.fairProbModifier(p2.team()));
	Person* winner = firstWins ? &p1 : &p2;
	Person* loser = firstWins ? &p2 : &p1;
	
	//Notify each Person Score of result
	loser->killed_by(*winner, _time);
	winner->has_killed(*loser);
	//EVENT
	events.push({ Event::Type::_DUEL, _time, winner->score(), loser->score() });
	//Result notification
	try {
		

		//Try to infect after duel
		if (Probability::infectPlayer(*loser, *winner)) {
			loser->has_infected();
			winner->infect();
			--_n_vulnerable;
			++_n_infected;
			//EVENT
			events.push({ Event::Type::_INFECTED_ON_DUEL, _time, winner->score(), loser->score() });
		}

		eliminatePlayer(*loser);
	}
	catch (std::exception & e) {
#ifdef PREVENTION
		system("pause");
#endif
	}
	
	return true;
}
