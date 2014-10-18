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

class Level {
public:
    Level();
    bool setBackground(sf::Texture backGround);
    bool setMiddleGround(sf::Texture middleGround);
    bool setForeGround(sf::Texture ForeGround);
    std::string getLevelString();
    bool setLevelString(std::string levelString);
    
private:
    sf::Texture backGround;
    sf::Texture middleGround;
    sf::Texture ForeGround;
    std::string levelString;
    sf::Time period;
    sf::Clock clock;
};

#endif	/* LEVEL_H */

