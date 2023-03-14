#ifndef PROFESSION_H
#define PROFESSION_H

#include <cstdlib>
#include <ctime>
#include <string>
#include <set>
#include <stdexcept>

class Profession {

public:
	//ENUM value DECLARATION:
	static const Profession DOCTOR;
	static const Profession POLICE;
	static const Profession ROBBER;
	static const Profession FIGHTER;
	static const Profession JUNKIE;
	static const Profession POLITICIAN;
	static const Profession PIZZA_MAN;
	static const Profession PERUANO;
	static const Profession NERD;
	static const Profession BULLY;

	///Profession mods
	static const int FLEE_PROB = 250;
	static const int POLICE_DMG = 200;
	static const int FIGHTER_DMG = 100;
	static const int BULLY_DMG = 300;
	static const int PERUANO_DMG = -100;
	
private:
	//Probabilities declarations
	static const int __DOCTOR = 100;
	static const int __POLICE = 100;
	static const int __ROBBER = 100;
	static const int __FIGHTER = 100;
	static const int __RAT = 100;
	static const int __POLITICIAN = 100;
	static const int __PIZZA_MAN = 100;
	static const int __PERUANO = 100;
	static const int __NERD = 100;
	static const int __BULLY = 100;
	static const int TOTAL_PROB = __DOCTOR + __POLICE + __ROBBER + __FIGHTER + __RAT + __POLITICIAN + __PIZZA_MAN + __PERUANO + __NERD + __BULLY;

private:

	std::string mStringVal;

private:
	Profession(const std::string& rStringVal ) :
		mStringVal(rStringVal) 
	{}

public:
	Profession() : mStringVal("UNDEFINED") {};
	// used to store in a set
	inline bool operator<(const Profession& rhs) const {
		return mStringVal < rhs.mStringVal;
	}
	// used for comparisons
	inline bool operator==(const Profession& rhs) const {
		return mStringVal == rhs.mStringVal;
	}
	// used for comparisons
	inline bool operator!=(const Profession& rhs) const {
		return !(this->operator==(rhs));
	}
	inline std::string getStringVal() const {
		return mStringVal;
	}

	static const std::set<Profession>& getValues() {
		static std::set<Profession> gValues;
		if (gValues.empty()) {
			gValues.insert(DOCTOR);
			gValues.insert(POLICE);
			gValues.insert(ROBBER);
			gValues.insert(FIGHTER);
			gValues.insert(JUNKIE);
			gValues.insert(POLITICIAN);
			gValues.insert(PIZZA_MAN);
			gValues.insert(PERUANO);
			gValues.insert(NERD);
			gValues.insert(BULLY);
		}
		return gValues;
	}

	static Profession valueOf(const std::string& rStringVal) {
		for (const auto& next : getValues()) {
			if (next.getStringVal() == rStringVal) {
				return next;
			}
		}
		throw std::domain_error(
			"Illegal Argument: " + rStringVal);
	}

	inline static Profession getProfession() {
		int res = rand() % TOTAL_PROB;
		res -= __DOCTOR;
		if (res <= 0) return DOCTOR;
		res -= __POLICE;
		if (res <= 0) return POLICE;
		res -= __ROBBER;
		if (res <= 0) return ROBBER;
		res -= __FIGHTER;
		if (res <= 0) return FIGHTER;
		res -= __RAT;
		if (res <= 0) return JUNKIE;
		res -= __POLITICIAN;
		if (res <= 0) return POLITICIAN;
		res -= __PIZZA_MAN;
		if (res <= 0) return PIZZA_MAN;
		res -= __PERUANO;
		if (res <= 0) return PERUANO;
		res -= __NERD;
		if (res <= 0) return NERD;
		return BULLY;
	}
};

#endif