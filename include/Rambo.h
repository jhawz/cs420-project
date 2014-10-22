#ifndef __Rambo__
#define __Rambo__

#include <cstdio>
#include <iostream>
#include <sfml/Graphics.hpp>
#include <sfml/System/Time.hpp>
#include "Animation.h"

class Rambo:public sf::Sprite{
public:
    Rambo();
    ~Rambo();
    void setOriginalImg(sf::Image &image);
    void prepareFrameInfo();
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
    Animation *curAnim;
    Animation *run;
    Animation *stand;
    Animation *straightShoot;
    Animation *upShoot;
    Animation *downShoot;
    Animation *jumpPrepare;
    Animation *jumpUp;
    Animation *jumpFloat;
    Animation *jumpFall;
    Animation *crouch;
    Animation *crouchShoot;
    Animation *die;
    sf::Image *imgOrigin;
};

#endif /* defined(__Rambo__) */
