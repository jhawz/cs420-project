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
#include "Jaw.h"
#include "Co.h"
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
        std::cout << "deleting tiles" << std::endl;
        
        for (int i = 0; i < enemyList.size(); i++)
        {
            delete enemyList[i];
        }
        enemyList.clear();
        std::cout << "Deleting Enemies" << std::endl;
        
        for (int i = 0; i < powerupList.size(); i++)
        {
            delete powerupList[i];
        }
        powerupList.clear();
        
        std::cout <<"deleting powerups" << std::endl;
        
        delete bond;
        std::cout << "deleting bond" << std::endl;
        
        if (curLevel == 20)
        {
            std::cout << "SHOULD NOT BE DELETING JAW" << std::endl;
            delete jaw;
            delete co;
        }
    }
    void setBackGround(VisibleGameObject* backGround);
    VisibleGameObject* getBackground();
    std::string getLevelString();
    bool setLevelString(std::string levelString);
    void loadLevel(int levelVal);
    void loadSpecifiedLevel(std::string file, int backgroundVal);
    std::vector<std::string> getTileCodes();
    std::vector<int> getTileColList();
    std::vector<Tile*>& getTileList();
    std::vector<Enemy*>& getEnemyList();
    std::vector<Powerup*>& getPowerupList();
    std::vector<int> getExitCodes();
    Bond* getBond();
    Tile* buildATile(sf::Texture& sheet, int positionInFrames, 
    int mapPositionInFrames);
    Enemy* buildAnEnemy(sf::Texture& sheet, int positionInFrames, 
    int mapPositionInFrames);
    Bond* buildABond(sf::Texture& sheet, int positionInFrames, 
    int mapPositionInFrames);
    Powerup* buildAPowerup(sf::Texture& sheet, int positionInFrames, 
    int mapPositionInFrames);
    Jaw* buildAJaw(sf::Texture& sheet, int positionInFrames, int mapPositionInFrames);
    Co* buildACo(sf::Texture& sheet, int mapPositionInFrames);
    bool isRealObjectOnMap(int objectCode);
    bool isTile(int objectCode, std::vector<int>& mapIDs);
    bool isEnemy(int objectCode, std::vector<int>& mapIDs);
    bool isBond(int objectCode, std::vector<int>& mapIDs);
    bool isPowerup(int objectCode, std::vector<int>& mapIDs);
    bool isExitTile(int mapPositionInFrames);
    Jaw* getJaws();
    Co* getCo();
    int const tilesPerRow = 100;
    int const tileHeight = 32;
    int const tileWidth = 32;
    sf::Vector2f bondStartLoc;
private:
    VisibleGameObject* backGround;
    sf::Texture levelTiles;
    sf::Texture enemySheet;
    sf::Texture bondSheet;
    std::vector<std::string> tileCodeList;
    std::vector<int> tileExitList;
    std::vector<int> tileColList;
    std::vector<Tile*> tileList;
    std::vector<Enemy*> enemyList;
    std::vector<Powerup*> powerupList;
    Bond* bond;
    Jaw* jaw;
    Co* co;
    sf::Time period;
    sf::Clock clock;
    int curLevel;
};
#endif	/* LEVEL_H */