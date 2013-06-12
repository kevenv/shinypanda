
#include "Config.h"

#include <fstream>
#include <string>
#include "Log.h"

namespace spe
{

Config::Config()
{
    _initialized = false;
    _filePath = "";

    Log(ERROR) << "CONFIG: DON'T EVEN TRY TO RUN THAT!!";
}

Config::~Config()
{

}

bool Config::parse(const char* filePath)
{
    std::ifstream file;
    file.open(filePath);

    if(!file) {
        Log(ERROR) << "Can't open config file '" << filePath << "'";
        return false;
    }

    std::string line;
    int lineNb = 0;
    while(std::getline(file, line)) {
        lineNb++;

        //find section
        if(isSection(line)) {
            if(!parseSection(line, file, lineNb)) {
                return false;
            }
        }
        //skip comments & empty lines
        else if(!isComment(line) &&
                !isEmpty(line)) {
            //otherwise flag line
            Log(ERROR) << "Config: invalid line at '" << lineNb << "' : " << line;
            return false;
        }
    }

    file.close();
    _initialized = true;
    _filePath = filePath;
    return true;
}

bool Config::parseSection(const std::string& section, std::ifstream& file, int& lineNb)
{
    std::string line;
    while(std::getline(file, line)) {
        lineNb++;

        if(isSection(line)) {
            lineNb--;
            for(int i = line.length(); i >= 0; i--) {
                file.putback(line[i]);
            }
            break; //end of section
        }
        //skip comments & empty lines
        else if(isComment(line) ||
                isEmpty(line)) {
            continue;
        }
        //parse line
        if(parseLine(line, lineNb)) {
            Log() << line;
            continue;
        }
        else {
            Log(ERROR) << "Config: invalid line at '" << lineNb << "' : " << line;
            return false;
        }

        Log() << line;
    }

    return true;
}

bool Config::parseLine(const std::string& line, int lineNb)
{
    //key = value
    if(line.find('=') != std::string::npos) { //jey = value

    }
    else if(true) { //detect array format
    }
    else { //else crap
        Log(ERROR) << "Config: invalid line at '" << lineNb << "' : " << line;
        return false;
    }

    return true;
}

bool Config::isComment(const std::string& line) const
{
    //#comment
    return line[0] == '#';
}

bool Config::isEmpty(const std::string& line) const
{
    return (line.find_first_not_of(" \t\r\n\v\f") == line.npos);
}

bool Config::isSection(const std::string& line) const
{
    //[SECTION]
    return (line[0] == '[' && line[line.length()-1] == ']');
}

}
