#ifndef BULLET_H
#define BULLET_H

#include <stdio.h>
#include "stdafx.h"
#include "Animation.h"
#include "pugixml.hpp"
#include "VisibleGameObject.h"

class Bullet:public VisibleGameObject{
public:
    Bullet(std::string config,std::string texture,int direction);
    void setBoundary(float left,float right);
    void Update(float elapsedTime);
    bool isDead();
    void straightLeft();
    void straightRight();
    void upLeft();
    void upRight();
    void downLeft();
    void downRight();
private:
    enum{right,left,upright,upleft,downright,downleft};
    void prepareFrameInfo(pugi::xml_node& node);
    void animReq(std::string animName);
    float vx,vy;
    float leftBoundary,rightBoundary;
    bool to_delete;
    std::map<std::string,Animation*> animations;
    Animation *curAnim;
};

#endif
