#include "SaveCommand.h"



SaveCommand::SaveCommand(std::string fileName) :
	Command("save", 's', "[N] save/s [O] nombre del archivo de guardado. Guarda la partida en el fichero especificado + \".txt\""),
	_fileName(fileName)
{
}

SaveCommand::~SaveCommand()
{
}

Command * SaveCommand::parse(std::stringstream& ss)
{
	std::string input;
	ss >> input;
	if (input == _name || input.length() == 1 && input.at(0) == _short_code) {
		parseOptions(ss);
		return  new SaveCommand(_fileName);
	}
	return nullptr;
}

void SaveCommand::parseOptions(std::stringstream & ss)
{
	try {
		ss >> _fileName;
		if (ss.fail())
			//Default option = default_save
			_fileName = "default_save";
			return;
	}
	catch (std::exception &e) {
		throw std::domain_error("Parametro de archivo de guardado incorrecto" + std::string(e.what()));
	}
	char test;
	ss >> test;
	if (!ss.fail()) {
		throw std::domain_error("Demasiados argumentos");
	}
}


void SaveCommand::run(bool &exit)
{
	std::ofstream out;
	try {
		out.open(_controller->path() + _fileName + "_save.txt");
	}
	catch (std::exception & e) {
		throw std::domain_error("Error en apertura del archivo " + _fileName + " " + e.what());
	}
	if (!out.is_open()) {
		throw std::domain_error("No se pudo abrir el archivo " + _fileName + ".txt en el directorio " + _controller->path());
	}
	_controller->game().serialize(out);
	out.close();
}
