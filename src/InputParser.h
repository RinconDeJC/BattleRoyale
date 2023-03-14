#ifndef INPUT_PARSER_H
#define INPUT_PARSER_H

#include <string>
#include <vector>

//from: https://stackoverflow.com/questions/865668/how-to-parse-command-line-arguments-in-c
class InputParser {
public:
    InputParser(int& argc, char** argv) {
        for (int i = 1; i < argc; ++i)
            this->tokens.push_back(std::string(argv[i]));
    }
    /// @author iain
    /// modified to eliminate error from std::find
    const std::string& getCmdOption(const std::string& option) const {
        /*
        std::vector<std::string>::const_iterator itr;
        itr = std::find(this->tokens.begin(), this->tokens.end(), option);
        if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
            return *itr;
        }
        static const std::string empty_string("");
        return empty_string;
        */
        std::size_t index = 0;
        while(index < tokens.size()){
            if(option.compare(tokens[index]) == 0){
                if(++index != tokens.size())
                    return tokens[index];
                else{
                    return std::string("");
                }
            } 
            ++index;
        }
        static const std::string empty_string("");
        return empty_string;
    }
    /// @author iain
    bool cmdOptionExists(const std::string& option) const {
        std::size_t index = 0;
        while(index < tokens.size() && option.compare(tokens[index]) != 0){
            ++index;
        }
        return index != tokens.size();
    }
private:
    std::vector <std::string> tokens;
};

#endif