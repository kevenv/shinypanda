#ifndef SPE_CONFIG_H
#define SPE_CONFIG_H

#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <typeinfo>
#include "Log.h"

namespace spe
{

class Config
{
public:
    Config();
    ~Config();

    bool parse(const char* filePath);
    bool isKeyExists(const std::string& key) const;
    template <typename T>
	T getValue(const std::string& key, T const &defaultValue = T()) const
	{
		if(!isKeyExists(key)) {
            return defaultValue;
        }

		return stringToType<T>(_map.find(key)->second);
	}
	std::string getArray(const std::string& key) const;
    inline const std::string& getFilePath() const { return _filePath; }
    inline const bool isParsed() const { return _parsed; }

private:
    std::map<std::string, std::string> _map;
    bool _parsed;
    std::string _filePath;

    bool parseSection(const std::string& section, std::ifstream& file, int& lineNb);
    bool parseLine(const std::string& section, const std::string& line, std::ifstream& file, int& lineNb);
    void extractArray(const std::string& section, const std::string& line, std::ifstream& file, int& lineNb);
    void extractLine(const std::string& section, const std::string& line, std::ifstream& file, int& lineNb);
    void extractKey(std::string& key, size_t const& sepPos, const std::string& line) const;
    void extractValue(std::string& value, size_t const& sepPos, const std::string& line) const;

    static bool lineHasKey(const std::string& line);
    static bool lineHasValue(const std::string& line);
    static bool lineHasSeparator(const std::string& line);

    bool isKey(const std::string& line, int lineNb) const;
    bool isArray(const std::string& line) const;
    static bool isComment(const std::string& line);
    static bool isEmpty(const std::string& line);
    static bool isSection(const std::string& line);

    static void putbackIntoStream(std::ifstream& file, const std::string& line);
    template <typename T>
	static T stringToType(const std::string& value)
	{
		std::istringstream istr(value);
		T type;
		if (!(istr >> type)) {
            Log(ERROR) << "Config: Not a valid type '" + (std::string)typeid(T).name() + "'";
		}

		return type;
	}
};

}

#endif
