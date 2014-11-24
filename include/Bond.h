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
    void transform();
    void jumpShoot();
    int getState();
    int getBondState();
    void setBoundary(float left, float up, float right, float lower);
    void die();
    sf::IntRect getBoundary();
    void input();
    int jumpDelay = 10;
    bool godMode = false;
    sf::Clock shotClock;
    int getRamboState();
private:
    int state;
    enum{BOND,RAMBO};
    bool lowCollide();
    bool leftCollide();
    bool rightCollide();
    bool topCollide();
    bool jumping;
    int lives = 3;
    sf::Vector2f upperleft,lowerright;
    sf::Clock transformClock;
    sf::Time transformDuration;
};
#endif