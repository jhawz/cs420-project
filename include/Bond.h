#ifndef BOND_H
#define	BOND_H

#include <iostream>
#include <string>
#include "stdafx.h"
#include "Animation.h"
#include "pugixml.hpp"
#include "Actor.h"

class Bond:public Actor{
public:
    Bond(std::string config,std::string texture);
    Bond(std::string config, sf::Texture& t);
    void Update(float elapsedTime);
    void jump();
    void leftRun();
    void rightRun();
    void standStill();
    void straightShoot();
    void upshoot();
    void downshoot();
    void crouchStill();
    void crouchshoot();
    void setBoundary(float left, float up, float right, float lower);
    sf::IntRect getBoundary();
    void input();
    int jumpDelay = 10;
    sf::Clock shotClock;
private:
    bool lowCollide();
    bool leftCollide();
    bool rightCollide();
    bool topCollide();
    bool jumping;
    int lives;
    sf::Vector2f upperleft,lowerright;
};

#endif
