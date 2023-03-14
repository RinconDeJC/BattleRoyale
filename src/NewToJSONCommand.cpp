#include "NewToJSONCommand.h"
#include <unordered_map>

NewToJSONCommand::NewToJSONCommand(std::string fileName) :
	Command("new_json", 'w', "[N] new_json/w [O] nombre del archivo de carga. Carga una nueva partida a partir del fichero especificado + \".txt\" y lo guarda en un archivo json"),
	_fileName(fileName)
{
}


NewToJSONCommand::~NewToJSONCommand()
{
}

Command* NewToJSONCommand::parse(std::stringstream& ss)
{
	std::string input;
	ss >> input;
	if (input == _name || input.length() == 1 && input.at(0) == _short_code) {
		parseOptions(ss);
		return  new NewToJSONCommand(_fileName);
	}
	return nullptr;
}

void NewToJSONCommand::parseOptions(std::stringstream& ss)
{
	try {
		ss >> _fileName;
		if (ss.fail())
			//Default option = default_load
			_fileName = "default_load";
		return;
	}
	catch (std::exception& e) {
		throw std::domain_error("Parametro de archivo de carga incorrecto" + std::string(e.what()));
	}
	char test;
	ss >> test;
	if (!ss.fail()) {
		throw std::domain_error("Demasiados argumentos");
	}
}

const std::string _START = "__FIRST_ELEMENT__";
typedef std::string name;
typedef std::string profession;
typedef std::string team;
//Auxiliar function
bool lower(std::string s1, std::string s2) {
	return s2 == _START || s1 < s2;
}

// Precondition: each profession's vector is sorted.
// Complexity O(number of professions * maximum number of names with same profession)
// We could say it is linear as the number of profession is fixed by the game.
void convert(
	std::vector<std::pair<name, std::pair<team, profession>>>& ret_val,
	std::vector<std::pair<Profession, std::vector<std::pair<name, team>>>>& professions
)
{
	std::unordered_map<profession, std::pair<std::vector<std::pair<name, team>>*, std::vector<std::pair<name, team>>::iterator>> it_map;
	// map with key profession and value a pair <vector*, vector::iterator>.
	// we need both in order to see if the iterator has reached the end

	//Initialize the iterators map
	auto it_vect = professions.begin();
	while (it_vect != professions.end()) {
		it_map[it_vect->first.getStringVal()] = std::make_pair(&(it_vect->second), it_vect->second.begin());
		++it_vect;
	}

	//Sort them into new vector
	std::pair<name, team> comparer;
	auto control_iterator = it_map.begin();
	bool finished = false;
	while (!finished) {
		comparer = { _START, "" };
		auto it = it_map.begin();
		while(it != it_map.end()) {
			// if the itearator ahsnt reached end() and the value is lower set it
			if (it->second.second != it->second.first->end()
				&&
				lower(it->second.second->first, comparer.first))
			{
				comparer.first = it->second.second->first;
				comparer.second = it->second.second->second;
				control_iterator = it;
			}
			++it;
		}
		//Add pair <name, profession> to return vector
		ret_val.push_back(std::make_pair(comparer.first, std::make_pair(comparer.second, control_iterator->first )));
		//Advance the vector with the name we just added
		++control_iterator->second.second;
		//Check if every iterator has reached the end
		finished = true;
		for (auto _pair : it_map) {
			finished &= _pair.second.second == _pair.second.first->end();
		}
	}
}

void NewToJSONCommand::run(bool& exit)
{
	std::ifstream input;
	input.open(_controller->path() + _fileName + ".txt");
	if (input.is_open()) {
		std::queue<Event> eventos = _controller->game().loadNew(input);
		std::vector<std::pair<Profession, std::vector<std::pair<name, team>>>> professions = _controller->game().profession();
		std::vector<std::pair<name, std::pair<team, profession>>> converted;
		convert(converted, professions);
		_controller->JSONOutput().writeInitialPlayerList(converted);
		_controller->JSONOutput().writeTeamsList(_controller->game().team_list());
		_controller->JSONOutput().writeOut(eventos, _controller->game().remaining());
	}
	else throw std::domain_error("No se ha podido abrir el archivo: " + _fileName + ".txt");
}


