#include <cstdio>
#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <string>
#include <sfml/Graphics.hpp>
#include <sfml/System/Time.hpp>
#include "Animation.h"
#include "pugixml.hpp"

#ifndef RAMBO_H
#define RAMBO_H

class Rambo:public sf::Sprite{
public:
    Rambo();
    ~Rambo();
    void setOriginalImg(sf::Image &image);
    void prepareFrameInfo(pugi::xml_node& node);
    void setMoving(bool moving);
    void update();
    void rightRun();
    void leftRun();
    void standStill();
    void jump();
    void shoot();
    void upshoot();
    void downshoot();
    void crouchStill();
    void crouchshoot();
    void shotDead();
    bool isAlive();
    bool lowCollide(int ground);
    
private:
    int getLowBound();
    sf::Clock clock;
    bool jumping;
    bool alive;
    bool rightdir;
    bool running;
    bool shootlocked;
    int lowerBound;
    float vx,vy,vxmax,vymax,vxmin,vymin;
    float ax,ay;
    std::map<std::string,Animation*> animations;
    Animation *curAnim;
    sf::Image *imgOrigin;
};


#endif /* defined(__Rambo__) */
