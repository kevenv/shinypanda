#include "tests.h"

#include <iostream>
#include <sstream>
#include "Log.h"
#include "Config.h"
#include "tinyxml2.h"

namespace spe
{

void startTests()
{
    //test_log();
    //test_config();
    //test_tmx();
}

void test_log()
{
    std::string logPath = "";//TEST_FOLDER_PATH;
    logPath += "test/test.log";

	Log::init(logPath.c_str(), true);

	Log() << "int " << 23 << " test";
	Log() << "long " << 1e32 << " test";
	Log() << "float " << 3.3f << " test";
	Log() << "double " << 3.3123312 << " test";
	Log() << "char " << 'g' << " test";
	Log() << "str " << " balbla" << " test";

	Log() << "test " << 32 << " after"; //single line

	Log() << "test1" << std::endl; //multi lines
	Log() << "test2" << std::endl;
	Log() << "test3";

	Log(DEBUG) << "DEBU GUB UBGEUB EBUE 1" << std::endl;
	Log(WARNING) << "DEBU GUB UBGEUB EBUE 2" << std::endl;
	Log(ERROR) << "DEBU GUB UBGEUB EBUE 3";

	Log(ERROR) << "ERREEUR AHAHHA";
	Log(ERROR) << "ERREEUR2 AHAHHA";
	Log(WARNING) << "ERREEUR2 AHAHHA";

	Log(ERROR) << "test1" << std::endl; //multi lines
	Log() << "test2" << std::endl;
	Log() << "test3";

	Log::close();
}

void test_config()
{
    Config cfg;
    bool success = cfg.parse("test.cfg");
    if(success) {
        Log() << "Config file parsed successfully";

        std::cout << cfg.isKeyExists("engine.fps") << std::endl;

        int fps = cfg.getValue<int>("engine.fps");
        std::cout << fps << std::endl;

        bool fullscreen = cfg.getValue<bool>("engine.fullscreen");
        std::cout << fullscreen << std::endl;

        std::string assetPath = cfg.getValue<std::string>("map.assetPath");
        std::cout << assetPath << std::endl;

        float depth = cfg.getValue<float>("map.depth");
        std::cout << depth << std::endl;

        std::string rawMap = cfg.getArray("map.map");
        std::cout << rawMap << std::endl;

        int x = cfg.getValue<int>("map.x");
        std::cout << x << std::endl;

        int y = cfg.getValue<int>("map.y");
        std::cout << y << std::endl;

        std::stringstream sstream;
        sstream << rawMap;
        char crap;
        int map[y][x];
        for(int j = 0; j < y; j++) {
            for(int i = 0; i < x; i++) {
               sstream >> map[j][i];
               std::cout << map[j][i] << " ";
            }
            sstream >> crap;
            std::cout << std::endl;
        }
    }
}

void test_tmx()
{
    //load tmx
    tinyxml2::XMLDocument doc;
    doc.LoadFile("test.tmx");
    tinyxml2::XMLElement* mapElement = doc.FirstChildElement("map");

    //load tileset infos
    tinyxml2::XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
    const tinyxml2::XMLAttribute* tilesizeAttr = tilesetElement->FirstAttribute()->Next()->Next();
    int tilesize = tilesizeAttr->IntValue();
    std::cout << "tilesize= "<< tilesize << std::endl;

    //load map layers
    tinyxml2::XMLElement* fgLayerElement = mapElement->FirstChildElement("layer");

    for(int i = 0; i < 3; i++) {
        const char* fgLayerName = fgLayerElement->FirstAttribute()->Value();
        int fgX = fgLayerElement->FirstAttribute()->Next()->IntValue();
        int fgY = fgLayerElement->FirstAttribute()->Next()->Next()->IntValue();
        std::cout << "fg name= " << fgLayerName << std::endl;
        std::cout << fgX << "," << fgY << std::endl;
        //load map
        tinyxml2::XMLElement* fgData = fgLayerElement->FirstChildElement("data");
        tinyxml2::XMLElement* tile = fgData->FirstChildElement("tile");
        for(int y = 0; y < fgY; y++) {
            for(int x = 0; x < fgX; x++) {
                std::cout << tile->FirstAttribute()->IntValue() << " ";
                tile = tile->NextSiblingElement("tile");
            }

            std::cout << std::endl;
        }
        fgLayerElement = fgLayerElement->NextSiblingElement("layer");

        std::cout << std::endl;
    }
}

}
