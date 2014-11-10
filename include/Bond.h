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
private:
    bool lowCollide();
    bool jumping;
};

#endif
