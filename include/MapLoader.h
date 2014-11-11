#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "VisibleGameObject.h"
#include "Tile.h"
using namespace std;

class MapLoader {
private:
	std::vector<string> tileSet;
	std::vector<sf::Sprite> spriteArray;
        std::vector<Tile*> tileList;//Is going to replace the spriteArray/tileSet
	sf::Texture tileSheet;
        static const int mapWidth = 100;
        static const int tileSheetWidth = 15;
        static const int tileSheetHeight = 15;
        int testValue;
        
public:
	MapLoader();
        ~MapLoader();
        void init();
	void loadMap(std::string fileName);
	std::string splitString(std::string dat, char &delim);
	std::vector<sf::Sprite> getSprites();
        std::vector<string> getTileCodes();
        std::vector<Tile*> getTiles();
        VisibleGameObject* getBackground(int worldCode);
        bool collidedWith(sf::IntRect otherObj);
        int getTestValue();
};

#endif