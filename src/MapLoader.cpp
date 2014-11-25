#include <string>
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include "MapLoader.h"

MapLoader::MapLoader()
{
	tileSheet.loadFromFile("textures/TiledEight32New.png");
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
        std::string firstIDString;
	std::ifstream reader(fileName);
        int count = 0;
        
        //load in tileTypes on map. These are single line strings containing:
        //firstgid
        while (std::getline(reader, readString, ',') && 
                readString.find("BEGINTILES") == string::npos)
        {
            firstIDList.push_back(std::stoi(readString));
        }
        //now get actual objects
	count = 0;
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
            bg->Load("textures/Background1.png");
            break;
        case 2:
            bg->Load("textures/Background2.png");
            break;
        case 3:
            bg->Load("textures/Background3.png");
            break;
        case 4:
            bg->Load("textures/Background4.png");
            break;
        default:
            bg->Load("textures/Background4.png");
            
    }
    bg->SetPosition(0, 0);
    
    return bg;
}
std::vector<std::string> MapLoader::getTileCodes()
{
    return tileSet;
}

std::vector<int> MapLoader::getFirstIDs()
{
    return firstIDList;
}