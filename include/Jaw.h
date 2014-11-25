#ifndef JAW_H
#define JAW_H

#include <cstdio>
#include <iostream>

#include "Actor.h"

class Jaw:public Actor{
public:
    Jaw(std::string config, std::string texture);
    Jaw(std::string config, sf::Texture& t);
    void attack(Actor& actor);
    void die();
    void setBondLocation(sf::Vector2f bondLoc);
    void Update(float elapsedTime);
    void setBoundary(float left, float up, float right, float lower);
    bool lowCollide();
    void checkForBond();
    
private:
    sf::Vector2i lowerright, upperleft;
    bool hasSeenBond = false;
    sf::Vector2i bondLoc;
    bool rightpressed = false;
    bool leftpressed = false;
};


#endif
