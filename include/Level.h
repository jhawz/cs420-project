/* 
 * File:   Level.h
 * Author: jch
 *
 * Created on October 17, 2014, 8:25 PM
 */

#ifndef LEVEL_H
#define	LEVEL_H

#include <cstdio>
#include <iostream>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "VisibleGameObject.h"
#include "MapLoader.h"
#include "Tile.h"

class Level {
public:

    Level() {

    };
    void setBackGround(VisibleGameObject* backGround);
    VisibleGameObject* getBackground();
    //bool setForeGround(sf::Texture ForeGround);
    std::string getLevelString();
    bool setLevelString(std::string levelString);
    void loadLevel(int levelVal);
    void loadSpecifiedLevel(std::string file);
    std::vector<std::string> getTileCodes();
    std::vector<int> getTileColList();
    std::vector<Tile*> getTileList();
private:
    VisibleGameObject* backGround;
    sf::Texture levelTiles;
    //  sf::Texture middleGround;
    //  sf::Texture ForeGround;
    //std::string levelString;
    std::vector<std::string> tileCodeList;
    std::vector<int> tileColList;
    std::vector<Tile*> tileList;
    sf::Time period;
    sf::Clock clock;
};

#endif	/* LEVEL_H */