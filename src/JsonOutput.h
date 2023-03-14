#ifndef JSONOUTPUT_H
#define JSONOUTPUT_H

#include "writer.h"
#include "document.h"
#include "Event.h"
#include <queue>
#include <vector>
#include <unordered_map>

class JsonOutput
{
public:

	JsonOutput(std::string const& fn, std::string const& path);

	void writeInitialPlayerList(
		std::vector<std::pair<std::string, std::pair<std::string, std::string>>>& list);

	void writeTeamsList(std::unordered_map<std::string, std::vector<Person>> const& teams);

	void writeOut(std::queue<Event>& events, int remaining);

	void writeWinner(Event& winner);

protected:

	static const char* _EXT;

	std::string _file_name;
	std::string _path;

	void printJSON(rapidjson::Document& doc, std::string fullFileName);

	void startDocument(rapidjson::Document& d, int time, int remaining);

	void writeEvent(Event const& e, rapidjson::Document& d);

	rapidjson::Value scoreJSON(Person::Score const& score, rapidjson::MemoryPoolAllocator<>& allocator);
};
#endif
