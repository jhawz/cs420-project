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
    void leftwalk();
    void rightwalk();
};

#endif	/* ENEMY_H */
