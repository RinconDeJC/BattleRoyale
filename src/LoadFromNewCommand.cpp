#include "LoadFromNewCommand.h"

LoadFromNewCommand::LoadFromNewCommand(std::string fileName) :
	Command("new", 'n', "[N] new/n [O] nombre del archivo de carga. Carga una nueva partida a partir del fichero especificado + \".txt\""),
	_fileName(fileName)
{
}

LoadFromNewCommand::~LoadFromNewCommand()
{
}

Command * LoadFromNewCommand::parse(std::stringstream& ss)
{
	std::string input;
	ss >> input;
	if (input == _name || input.length() == 1 && input.at(0) == _short_code) {
		parseOptions(ss);
		return  new LoadFromNewCommand(_fileName);
	}
	return nullptr;
}

void LoadFromNewCommand::parseOptions(std::stringstream & ss)
{
	try {
		ss >> _fileName;
		if (ss.fail())
			//Default option = default_load
			_fileName = "default_load";
		return;
	}
	catch (std::exception &e) {
		throw std::domain_error("Parametro de archivo de carga incorrecto" + std::string(e.what()));
	}
	char test;
	ss >> test;
	if (!ss.fail()) {
		throw std::domain_error("Demasiados argumentos");
	}
}


void LoadFromNewCommand::run(bool &exit)
{
	std::ifstream input;
	input.open(_controller->path() + _fileName + ".txt");
	if (input.is_open()) {
		std::queue<Event> eventos = _controller->game().loadNew(input);
		std::cout << "Introduce un nombre para la partida: ";
		std::string name;
		std::cin >> name;
		std::cin.ignore(100, '\n');
		_controller->game().setName(name);
		std::vector<std::pair<Profession, std::vector<std::pair<std::string, std::string>>>> professions = _controller->game().profession();
		_controller->display().showProfesisons(professions, name);
		_controller->display().showGame(eventos, _controller->game().gameName());

	}
	else throw std::domain_error("No se ha podido abrir el archivo: " + _fileName + ".txt en el directorio " + _controller->path());
}
