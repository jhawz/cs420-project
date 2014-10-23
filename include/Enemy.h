/* 
 * File:   Enemy.h
 * Author: jch
 *
 * Created on October 18, 2014, 10:51 PM
 */

#ifndef ENEMY_H
#define	ENEMY_H

#include <cstdio>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Enemy : public sf::Sprite {
public:
    Enemy();
    ~Enemy();
    void update();
    void rightRun();
    void leftRun();
    void standStill();
    void shoot();
    void setPistol();
    void setSmg();
    void setMachineGun();
    bool isAlive();
    bool isAttacking();
    void setAttack( bool x);
    

private:
    bool alive;
    bool attack;
    int health;
    bool rightdir;
    bool running;
    float vx, vy, vxmax, vymax, vxmin, vymin;
    float ax, ay;
    Animation *curAnim;
    Animation *run;
    Animation *stand;
};

#endif	/* ENEMY_H */

