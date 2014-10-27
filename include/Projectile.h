/* 
 * File:   Projectile.h
 * Author: jch
 *
 * Created on October 18, 2014, 10:51 PM
 */

#ifndef PROJECTILE_H
#define	PROJECTILE_H

#include <cstdio>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Projectile : public sf::Sprite {
public:
    Projectile();
    ~Projectile();
    bool isActive();
    void update();
    void rightFly();
    void leftFly();
    void setBullet();
    void fire();
    void deactivate();

private:
    bool active;
    bool rightdir;
    float vx, vy, vxmax, vymax, vxmin, vymin;
    float ax, ay;
    Animation *curAnim;
    Animation *fired;
};

#endif	/* PROJECTILE_H */

