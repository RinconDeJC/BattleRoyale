#include "LoadFromSaveCommand.h"

LoadFromSaveCommand::LoadFromSaveCommand(std::string fileName) :
	Command("load", 'l', "[N] load/l [O] nombre del archivo de carga. Carga una partida preexistente a partir del fichero especificado + \".txt\""),
	_fileName(fileName)
{
}

LoadFromSaveCommand::~LoadFromSaveCommand()
{
}

Command * LoadFromSaveCommand::parse(std::stringstream& ss)
{
	std::string input;
	ss >> input;
	if (input == _name || input.length() == 1 && input.at(0) == _short_code) {
		parseOptions(ss);
		return  new LoadFromSaveCommand(_fileName);
	}
	return nullptr;
}

void LoadFromSaveCommand::parseOptions(std::stringstream & ss)
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


void LoadFromSaveCommand::run(bool &exit)
{
	std::ifstream input;
	input.open(_controller->path() + _fileName + Controller::_SAVE_SUFFIX + ".txt");
	if (input.is_open()) {
		_controller->game().loadSave(input);
		_controller->game().setName(_fileName);
	}
	else throw std::domain_error("No se ha podido abrir el archivo: " + _fileName + ".txt en el directorio " + _controller->path());
}
