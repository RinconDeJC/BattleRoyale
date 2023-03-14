#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "Person.h"


class Event
{
public:
	enum Type {
		_DUEL,
		_PIZZA_FLEE,
		_INFECTED_ON_DUEL,
		_FIND_VACCINE,
		_STEAL_VACCINE,
		_GET_VACCINATED,
		_GET_CURED,
		_NATURAL_INFECTION,
		_NEW_PLAYER,
		_INFECTION_ELIMINATION,
		_WINNER
	};

protected:
	Type _type;
	int _time;
	const Person::Score _score_1;
	const Person::Score _score_2;


public:
	Event(Type type, int time);

	Event(Type type, int time, const Person::Score s1, const Person::Score s2 = {});

	Event(Event const& e);

	std::pair< const Person::Score, const Person::Score> score() const;

	int time() const;

	Type type() const;

	const char* typeToC_String() const;
	
};


#endif

