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
private:
    bool lowCollide();
    bool leftCollide();
    bool rightCollide();
    bool topCollide();
    bool jumping;
    sf::Vector2f upperleft,lowerright;
};

#endif
