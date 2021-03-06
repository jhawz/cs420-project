#ifndef ACTOR_H
#define	ACTOR_H

#include "stdafx.h"
#include <sstream>
#include "Animation.h"
#include "pugixml.hpp"
#include "VisibleGameObject.h"
#include "Bullet.h"

class Actor:public VisibleGameObject{
public:
    Actor();
    void prepareFrameInfo(pugi::xml_node& node);
    void Update(float elapsedTime);
    void rightRun(std::string aname="run");
    void rightMove();
    void leftRun(std::string aname="run");
    void leftMove();
    void standStill(std::string aname="stand");
    void attack(std::string aname="straight_shoot");
    void die();
    void animReq(std::string animName,bool withlock);
    void setOriginalImg(sf::Image &img);
    bool hasAnimation(std::string name);
    bool isCurAnim(std::string name);
    void setLeftPress(bool p);
    void setRightPress(bool p);
    void setUpPress(bool p);
    void setDownPress(bool p);
    void setBoundary(float left,float up,float right,float lower);
    bool lowCollide();
    bool IsAlive();
    void setAlive();
    Animation* getAnim();
        
protected:
    float getLowBound();
    sf::Clock clock;
    sf::Time shootWait;
    bool alive;
    bool rightdir;
    bool shootlocked;
    int lowerBound;
    float vx,vy;
    float ax,ay;
    bool leftpressed,rightpressed,uppressed,downpressed;

private:
    std::map<std::string,Animation*> animations;
    Animation *curAnim;
    sf::Image *image;
    sf::Vector2f upperleft;
    sf::Vector2f lowerright;
};

#endif
