/* 
 * File:   Enemy.h
 * Author: jch
 *
 * Created on October 18, 2014, 10:51 PM
 */

#ifndef ENEMY_H
#define	ENEMY_H

#include "stdafx.h"
#include "Animation.h"
#include "pugixml.hpp"
#include "Actor.h"

class Enemy : public Actor {
public:
    Enemy(std::string config,std::string texture,std::string name);
    Enemy(std::string config,sf::Texture& t, std::string name, float fireRate);
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
    private:
            sf::Vector2f upperleft,lowerright;
            sf::Vector2f origPos;
            bool isAttacking = false;
            sf::Vector2f bondLoc;
};
#endif	/* ENEMY_H */