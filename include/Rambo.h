#ifndef __Rambo__
#define __Rambo__

#include <cstdio>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Rambo : public sf::Sprite {
public:
    Rambo();
    ~Rambo();
    void prepareFrameInfo();
    void update();
    void rightRun();
    void leftRun();
    void standStill();
    void jump();

private:
    bool rightdir;
    bool running;
    float vx, vy, vxmax, vymax, vxmin, vymin;
    float ax, ay;
    Animation *curAnim;
    Animation *run;
    Animation *stand;
};

#endif /* defined(__Rambo__) */
