/* 
 * File:   Jaw.h
 * Author: jch
 *
 * Created on October 18, 2014, 10:51 PM
 */

#ifndef JAW_H
#define	JAW_H

#include "stdafx.h"
#include "Animation.h"
#include "pugixml.hpp"
#include "Actor.h"

class Jaw : public Actor {
public:
    Jaw(std::string config,std::string texture);
    Jaw(std::string config,sf::Texture& t);
    void leftwalk();
    void rightwalk();
    void patrol();
    void straightShoot();
    void Update(float elapsedTime);
    void setBoundary(float left, float up, float right, float lower);
    bool lowCollide();
    bool leftCollide();
    bool rightCollide();
    void rightRun();
    void leftRun();
    void setOrigPos(sf::Vector2f o);
    bool isAlive();
    void setBondLocation(sf::Vector2f bL);
    bool attackCheck();
    void runCheck();
    bool attackingLeft;
    bool attackingRight;
    sf::Vector2f getBondLocation();
    sf::Clock shotClock;
    float attackRate;
    void die();
    bool bondInRange();
    bool grabbedBond = false;
    private:
            sf::Vector2f upperleft,lowerright;
            sf::Vector2f origPos;
            bool isAttacking = false;
            sf::Vector2f bondLoc;
};
#endif	/* JAW_H */