#include "Event.h"


Event::Event(Type type, int time) :
	_type(type),
	_time(time)
{}
;
Event::Event(Type type, int time, const Person::Score s1, const Person::Score s2) :
	_type(type),
	_time(time),
	_score_1(s1),
	_score_2(s2)
{}
;
Event::Event(Event const& e) :
	_type(e._type),
	_time(e._time),
	_score_1(e._score_1),
	_score_2(e._score_2)
{}
;

std::pair<const Person::Score, const Person::Score> Event::score() const
{
	return std::make_pair(_score_1, _score_2);
}

int Event::time() const
{
	return _time;
}

Event::Type Event::type() const
{
	return _type;
}

const char* Event::typeToC_String() const
{
	switch(_type) {
	case (_DUEL) :					return "DUEL";
	case (_PIZZA_FLEE) :			return "PIZZA_FLEE";
	case (_INFECTED_ON_DUEL) :		return "INFECTED_ON_DUEL";
	case (_FIND_VACCINE) :			return "FIND_VACCINE";
	case (_STEAL_VACCINE) :			return "STEAL_VACCINE";
	case (_GET_VACCINATED) :		return "GET_VACCINATED";
	case (_GET_CURED) :				return "GET_CURED";
	case (_NATURAL_INFECTION) :		return "NATURAL_INFECTION";
	case (_NEW_PLAYER) :			return "NEW_PLAYER";
	case (_INFECTION_ELIMINATION) :	return "INFECTION_ELIMINATION";
	case (_WINNER) :				return "WINNER";
	}
	return "ERROR";
}
