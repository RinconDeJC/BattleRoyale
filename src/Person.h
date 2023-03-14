#ifndef Person_H
#define Person_H
//#define DEBUG

#include <string>
#include <cmath>
#include <vector>

#include "Profession.h"

class Person {
public:
	struct Score {
		std::string _name;
		std::string _team;
		std::string _prof;
		std::vector<std::string> _kills;
		std::string _killed_by;
		int _n_days_infected;
		int _n_days_survived;
		int _n_people_infected;

		Score() : 
			_name(""), 
			_prof(""),
			_team(""),
			_n_days_infected(0), 
			_n_days_survived(0), 
			_n_people_infected(0) 
		{}
		;

		Score(std::string name, std::string team) : 
			_name(name),
			_team(team),
			_n_days_infected(0), 
			_n_days_survived(0), 
			_n_people_infected(0) 
		{}
		;

		Score(Score const& copy) : 
			_name(copy._name),
			_team(copy._team),
			_prof(copy._prof),
			_killed_by(copy._killed_by), 
			_n_days_infected(copy._n_days_infected), 
			_n_days_survived(copy._n_days_survived), 
			_n_people_infected(copy._n_people_infected) 
		{
			std::copy(copy._kills.begin(), copy._kills.end(), back_inserter(_kills));
		}

		void serialize(std::ostream & output, bool alive);

		void load(std::istream & in);
	};


protected:
	std::string _name;
	std::string _team;
	int _kills;
	bool _infected;
	bool _immune;
	int _n_infected;
	Score _score;
	Profession _prof;

public:
	Person();
	Person(std::string name, std::string team);
	Person(std::string name, std::string team, std::string profession);
	Person(Person const& other);
	~Person();

	//Overload of = operator
	Person & operator=(Person const & other);

	bool operator==(Person const& other) const ;

	bool operator!=(Person const& other) const ;

	bool operator<(Person const& other) const ;

	std::string name() const;

	std::string team() const;

	int kills() const;

	bool infected()const;

	bool immune()const;

	int days_infected()const;

	void beatInfection();

	void makeImmune();

	void infect();

	const Score& score()const;

	Profession profession() const;

	void has_killed(Person const& other);

	void has_infected();

	void one_day_infected();

	void killed_by(Person const& other, int time);

	void killed_by(std::string const& infection, int time);

	void serialize(std::ostream & output, bool alive);

	static Person load(std::istream & in);


protected:


	void copia(Person const& other);

	void freePerson();

};



#endif
