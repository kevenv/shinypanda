
#include "Config.h"

#include <fstream>
#include <string>
#include "Log.h"

namespace spe
{

Config::Config()
{
    _parsed = false;
    _filePath = "";

    //Log(ERROR) << "CONFIG: DON'T EVEN TRY TO RUN THAT!!";
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
    _parsed = true;
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
            putbackIntoStream(file, line);
            break; //end of section
        }
        //skip comments & empty lines
        else if(isComment(line) ||
                isEmpty(line)) {
            continue;
        }
        //parse line
        else if(parseLine(section, line, file, lineNb)) {
            continue;
        }
        else {
            Log(ERROR) << "Config: invalid line at '" << lineNb << "' : " << line;
            return false;
        }
    }

    return true;
}

bool Config::parseLine(const std::string& section, const std::string& line, std::ifstream& file, int& lineNb)
{
    if(isKey(line, lineNb)) { //key = value
        extractLine(section, line, file, lineNb);
    }
    else if(isArray(line)) { //array
        extractArray(section, line, file, lineNb);
    }
    else { //else crap
        return false;
    }

    return true;
}

void Config::extractLine(const std::string& section, const std::string& line, std::ifstream& file, int& lineNb)
{
    std::string temp = line;
    temp.erase(0, temp.find_first_not_of(" \t\r\n\v\f"));
    size_t sepPos = temp.find('=');

    std::string key;
    std::string value;
    extractKey(key, sepPos, temp);
    key = section.substr(1, section.length()-2) + "." + key;
    extractValue(value, sepPos, temp);

    if (!isKeyExists(key)) {
        _map.insert(std::pair<std::string, std::string>(key, value));
    }
    else {
        Log(ERROR) << "Config: Can only have unique key names!";
    }
}

void Config::extractKey(std::string& key, size_t const& sepPos, const std::string& line) const
{
    key = line.substr(0, sepPos);
    if (key.find('\t') != line.npos || key.find(' ') != line.npos)
        key.erase(key.find_first_of(" \t\r\n\v\f"));
}

void Config::extractValue(std::string& value, size_t const& sepPos, const std::string& line) const
{
    value = line.substr(sepPos + 1);
    value.erase(0, value.find_first_not_of(" \t\r\n\v\f"));
    value.erase(value.find_last_not_of(" \t\r\n\v\f") + 1);
}

void Config::extractArray(const std::string& section, const std::string& line, std::ifstream& file, int& lineNb)
{
    std::string array = line;
    std::string lineTmp;
    while(std::getline(file, lineTmp)) {
        lineNb++;

        if(isSection(lineTmp)) {
            lineNb--;
            putbackIntoStream(file, lineTmp);
            break; //end of section
        }
        //skip comments & empty lines
        else if(isComment(lineTmp) ||
                isEmpty(lineTmp)) {
            continue;
        }
        //parse array
        else {
            array += ":" + lineTmp;
        }
    }

    std::string key = section.substr(1, section.length()-2) + "=" + array;
    extractLine(section, key, file, lineNb);
}

bool Config::isKeyExists(const std::string& key) const
{
    return _map.find(key) != _map.end();
}

std::string Config::getArray(const std::string& key) const
{
    if (isKeyExists(key)) {
        return _map.find(key)->second;
    }
    else {
        return "";
    }
}

bool Config::lineHasKey(const std::string& line)
{
    std::string temp = line;
    temp.erase(0, temp.find_first_not_of(" \t\r\n\v\f"));
    return (temp[0] != '=');
}

bool Config::lineHasValue(const std::string& line)
{
    for(int i = line.find('=') + 1; i < line.length(); i++) {
        if(line[i] != ' ') {
            return true;
        }
    }

    return false;
}

bool Config::lineHasSeparator(const std::string& line)
{
    return line.find('=') != std::string::npos;
}

bool Config::isKey(const std::string& line, int lineNb) const
{
    if(!lineHasSeparator(line)) {
        //Log(ERROR) << "Config: no '=' separator at '" << lineNb << "' : " << line;
        return false;
    }

    if(!lineHasKey(line)) {
        //Log(ERROR) << "Config: no key at '" << lineNb << "' : " << line;
        return false;
    }

    if(!lineHasValue(line)) {
        //Log(ERROR) << "Config: no value at '" << lineNb << "' : " << line;
        return false;
    }

    return true;
}

bool Config::isArray(const std::string& line) const
{
    return true; //TODO
}

bool Config::isComment(const std::string& line)
{
    //#comment
    return line[0] == '#';
}

bool Config::isEmpty(const std::string& line)
{
    return (line.find_first_not_of(" \t\r\n\v\f") == line.npos);
}

bool Config::isSection(const std::string& line)
{
    //[SECTION]
    return (line[0] == '[' && line[line.length()-1] == ']');
}

void Config::putbackIntoStream(std::ifstream& file, const std::string& line)
{
    for(int i = line.length(); i >= 0; i--) {
        file.putback(line[i]);
    }
}

}
