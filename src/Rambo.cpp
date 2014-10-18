#include "Rambo.h"

Rambo::Rambo() {
    run = new Animation();
    stand = new Animation();
    shortJump = new Animation();
    curAnim = stand;
    curAnim->restart();
    rightdir = true;
}

Rambo::~Rambo() {
    delete run;
    delete stand;
    delete shortJump;
}

void Rambo::rightRun() {
    if (!rightdir) {
        rightdir = true;
        setScale(1, 1);
    }
    if (curAnim != run) {
        curAnim->end();
        curAnim = run;
    }

    if (curAnim->isEnded())curAnim->restart();
    running = true;
}

void Rambo::leftRun() {
    if (rightdir) {
        rightdir = false;
        setScale(-1, 1);
    }
    if (curAnim != run) {
        curAnim->end();
        curAnim = run;
    }
    if (curAnim->isEnded())curAnim->restart();
    running = true;
}

void Rambo::standStill() {
    if (curAnim != stand) {
        curAnim->end();
        curAnim = stand;
    }
    curAnim->restart();
    running = false;
    vx = 0;
    vy = 0;
    //vxmax=0;vymax=0;
    //vxmin=0;vymin=0;
    //ax=0;ay=0;
}

void Rambo::prepareFrameInfo() {
    run->addFrame(sf::IntRect(7, 221, 25, 42));
    run->addFrame(sf::IntRect(35, 221, 25, 42));
    run->addFrame(sf::IntRect(69, 221, 25, 42));
    run->addFrame(sf::IntRect(99, 221, 25, 42));
    run->addFrame(sf::IntRect(129, 221, 25, 42));
    run->addFrame(sf::IntRect(161, 221, 25, 42));
    run->addFrame(sf::IntRect(199, 221, 25, 42));
    run->addFrame(sf::IntRect(230, 221, 25, 42));
    run->setAnimationPeriod(40);
    stand->addFrame(sf::IntRect(12, 36, 25, 42));
    shortJump->addFrame(sf::IntRect(19, 319, 20, 28));
    shortJump->addFrame(sf::IntRect(46, 300, 26, 46));
    shortJump->addFrame(sf::IntRect(83, 295, 17, 51));
}

void Rambo::update() {
    if (curAnim->play()) {
        setTextureRect(curAnim->getCurFrame());
    }
    if (running) {
        if (rightdir) {
            vx = 8;
        } else vx = -8;
    }
    if (!shortJumping) {
        vy = 0;
    } 
    else {
        vy = -4;
    }
    /*if (vx<vxmax&&vx>vxmin) {
        vx+=ax;
    }
    if (vx>=vxmax||vx<=vxmin) {
        vx=0;
    }
    if (vy<vymax&&vy>vymin) {
        vy+=ay;
    }
    if (vy>=vymax||vy<=vymin) {
        vy=0;
        vymin=0;
        vymax=0;
    }*/

    move(vx, vy);
}

void Rambo::jump() {
    /*running=false;
    vy=-15.99;
    vymax=16;
    vymin=-16;
    ay=0.5;*/
    if (curAnim != shortJump) {
        curAnim->end();
        curAnim = shortJump;
        shortJumping = true;
    }
    if (curAnim->isEnded())curAnim->restart();
}
