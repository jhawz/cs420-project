#ifndef POWERUP_H
#define POWERUP_H


#include <stdio.h>
#include "stdafx.h"
#include <sstream>
#include "VisibleGameObject.h"
#include "Animation.h"


class Powerup:public VisibleGameObject{
public:
    Powerup(std::string config,std::string texture);
    void Update(float elapsedTime);
    void disappear();
    bool isDead();
private:
    bool used;
    void prepareFrameInfo(pugi::xml_node& node);
    void animReq(std::string animName);
    std::map<std::string,Animation*> animations;
    Animation *curAnim;
};

#endif
