#ifndef SPE_CONFIG_H
#define SPE_CONFIG_H

#include <string>

/***************************
*                          *
* DANGER - IN DEV - DANGER *
*                          *
****************************/

namespace spe
{

class Config
{
public:
    Config();
    ~Config();

    bool parse(const char* filePath);

    inline const std::string& getFilePath() const { return _filePath; }

private:
    bool _initialized;
    std::string _filePath;

    bool parseSection(const std::string& section, std::ifstream& file, int& lineNb);
    bool parseLine(const std::string& line, int lineNb);

    bool isComment(const std::string& line) const;
    bool isEmpty(const std::string& line) const;
    bool isSection(const std::string& line) const;
};

}

#endif
