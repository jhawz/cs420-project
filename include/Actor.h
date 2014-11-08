#ifndef ACTOR_H
#define	ACTOR_H

#include "stdafx.h"
#include "Animation.h"
#include "pugixml.hpp"
#include "VisibleGameObject.h"

class Actor:public VisibleGameObject{
public:
    void prepareFrameInfo(pugi::xml_node& node);
    void Update(float elapsedTime);
    void rightRun();
    void leftRun();
    void standStill();
    void attack();
    void die();
    void animReq(std::string animName,bool withlock);
    
protected:
    int getLowBound();
    sf::Clock clock;
    sf::Time shootWait;
    bool alive;
    bool rightdir;
    bool running;
    bool shootlocked;
    int lowerBound;
    float vx,vy;
    float ax,ay;
private:
    std::map<std::string,Animation*> animations;
    Animation *curAnim;
    sf::Image *image;
};

#endif
