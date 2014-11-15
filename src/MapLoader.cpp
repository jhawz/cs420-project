#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "MapLoader.h"

MapLoader::MapLoader()
{
    	sf::Image i;
	i.loadFromFile("textures/TiledEight32New.png");
	i.createMaskFromColor(sf::Color(255, 255, 255));
        tileSheet.loadFromImage(i);
}
MapLoader::~MapLoader()
{

    
}
void MapLoader::init()
{
    
}
void MapLoader::loadMap(std::string fileName)
{
	std::string readString;
	std::ifstream reader(fileName);
	int count = 0;
	while (std::getline(reader, readString, ','))
	{
		int newVal;
		std::istringstream (readString) >> newVal;
                tileSet.push_back(readString);                
		count++;
	}
}
VisibleGameObject* MapLoader::getBackground(int worldCode)
{
    VisibleGameObject* bg = new VisibleGameObject();
    switch (worldCode)
    {
        case 1:
            bg->Load("textures/BackgroundOne_1.png");
            break;
        case 2:
            bg->Load("textures/BackgroundOne_1.png");
            break;
        case 3:
            bg->Load("textures/BackgroundOne_1.png");
            break;
        case 4:
            bg->Load("textures/BackgroundOne_1.png");
            break;
        case 5:
            bg->Load("textures/BackgroundOne_1.png");
            break;
        default:
            break;
            
    }
    bg->SetPosition(0, 0);
    
    return bg;
}
std::string MapLoader::splitString(std::string dat, char &delim)
{
	std::istringstream s(dat);
	std::string result;

	s >> result;

	return result;

}
std::vector<sf::Sprite> MapLoader::getSprites()
{
    return spriteArray;
}

std::vector<std::string> MapLoader::getTileCodes()
{
    return tileSet;
}

std::vector<Tile*> MapLoader::getTiles()
{
    return tileList;
}

int MapLoader::getTestValue()
{
    return testValue;
}