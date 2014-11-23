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
#include "Enemy.h"
#include "Bond.h"
#include "Powerup.h"

class Level {
public:

    Level() {

    };
    ~Level(){
        delete backGround;
        for (int i = 0; i < tileList.size(); i++)
        {
            delete tileList[i];
        }
        tileList.clear();
        
        for (int i = 0; i < enemyList.size(); i++)
        {
            delete enemyList[i];
        }
        enemyList.clear();
        
        for (int i = 0; i < powerupList.size(); i++)
        {
            delete powerupList[i];
        }
        powerupList.clear();
        
        delete bond;
    }
    void setBackGround(VisibleGameObject* backGround);
    VisibleGameObject* getBackground();
    std::string getLevelString();
    bool setLevelString(std::string levelString);
    void loadLevel(int levelVal);
    void loadSpecifiedLevel(std::string file);
    std::vector<std::string> getTileCodes();
    std::vector<int> getTileColList();
    std::vector<Tile*>& getTileList();
    std::vector<Enemy*>& getEnemyList();
    std::vector<Powerup*>& getPowerupList();
    Bond* getBond();
    Tile* buildATile(sf::Texture& sheet, int positionInFrames, int mapPositionInFrames);
    Enemy* buildAnEnemy(sf::Texture& sheet, int positionInFrames, int mapPositionInFrames);
    Bond* buildABond(sf::Texture& sheet, int positionInFrames, int mapPositionInFrames);
    Powerup* buildAPowerup(sf::Texture& sheet, int positionInFrames, int mapPositionInFrames);
    bool isRealObjectOnMap(int objectCode);
    bool isTile(int objectCode, std::vector<int>& mapIDs);
    bool isEnemy(int objectCode, std::vector<int>& mapIDs);
    bool isBond(int objectCode, std::vector<int>& mapIDs);
    bool isPowerup(int objectCode, std::vector<int>& mapIDs);
    void checkIfExitTile(Tile* t, int mapPositionInTiles);
    int const tilesPerRow = 100;
    int const tileHeight = 32;
    int const tileWidth = 32;
private:
    VisibleGameObject* backGround;
    sf::Texture levelTiles;
    sf::Texture enemySheet;
    sf::Texture bondSheet;
    std::vector<std::string> tileCodeList;
    std::vector<int> tileColList;
    std::vector<Tile*> tileList;
    std::vector<Enemy*> enemyList;
    std::vector<Powerup*> powerupList;
    Bond* bond;
    sf::Time period;
    sf::Clock clock;
};
#endif	/* LEVEL_H */