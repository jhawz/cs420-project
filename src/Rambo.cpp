//
//  Rambo.cpp
//  jamesrambotest
//
//  Created by gyp on 10/12/14.
//  Copyright (c) 2014 gyp. All rights reserved.
//

#include "Rambo.h"

Rambo::Rambo() {
    alive = true;
    run = new Animation();
    stand = new Animation();
    straightShoot = new Animation();
    upShoot = new Animation();
    downShoot = new Animation();
    jumpPrepare = new Animation();
    jumpUp = new Animation();
    jumpFloat = new Animation();
    jumpFall = new Animation();
    crouch = new Animation();
    crouchShoot = new Animation();
    die = new Animation();
    curAnim = stand;
    curAnim->restart();
    rightdir = true;
    shootlocked = false;
    ax = 0;
    ay = 0;
    gunshot.loadFromFile("sounds/gun.wav");
    pistol.setBuffer(gunshot);
}

Rambo::~Rambo() {
    delete run;
    delete stand;
}

void Rambo::setOriginalImg(sf::Image &image) {
    imgOrigin = &image;
}

bool Rambo::isAlive() {
    return alive;
}

bool Rambo::isRunning() {
    return running;
}

bool Rambo::getRight() {
    return rightdir;
}

void Rambo::rightRun() {
    if (jumping)return;
    if (!alive)return;
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
    if (jumping)return;
    if (!alive)return;
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
    if (jumping)return;
    if (!alive)return;
    if (curAnim != stand) {
        curAnim->end();
        curAnim = stand;
    }
    curAnim->restart();
    running = false;
    vx = 0;
    vy = 0;
    ax = 0;
    ay = 0;
    //vxmax=0;vymax=0;
    //vxmin=0;vymin=0;
    //ax=0;ay=0;
}

void Rambo::shoot() {
    if (jumping)return;
    if (running) return;
    if (!alive)return;
    /*if (shootlocked){
        if (curAnim==straightShoot) {
            curAnim->end();
        }
        return;
    }*/
    curAnim->end();
    pistol.play();
    curAnim = straightShoot;
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    running = false;
}

void Rambo::upshoot() {
    if (jumping)return;
    if (!alive)return;
    /*if (shootlocked){
        if (curAnim==upShoot) {
            curAnim->end();
        }
        return;
    }*/
    curAnim->end();
    curAnim = upShoot;
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    running = false;
}

void Rambo::downshoot() {
    if (jumping)return;
    if (!alive)return;
    /*if (shootlocked){
        if (curAnim==downShoot) {
            curAnim->end();
        }
        return;
    }*/
    curAnim->end();
    curAnim = downShoot;
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    running = false;
}

void Rambo::crouchStill() {
    if (!alive)return;
    curAnim->end();
    curAnim = crouch;
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    running = false;
}

void Rambo::crouchshoot() {
    if (!alive)return;
    curAnim->end();
    curAnim = crouchShoot;
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    running = false;
}

void Rambo::shotDead() {
    if (!alive)return;
    if (curAnim != die)curAnim->end();
    curAnim = die;
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    alive = false;
}

void Rambo::prepareFrameInfo() {
    run->addFrame(sf::IntRect(14, 129, 25, -42));
    run->addFrame(sf::IntRect(44, 129, 25, -42));
    run->addFrame(sf::IntRect(76, 129, 25, -42));
    run->addFrame(sf::IntRect(109, 129, 25, -42));
    run->addFrame(sf::IntRect(140, 129, 25, -42));
    run->addFrame(sf::IntRect(172, 129, 25, -42));
    run->addFrame(sf::IntRect(205, 129, 25, -42));
    run->addFrame(sf::IntRect(237, 129, 25, -42));
    run->setAnimationPeriod(40);
    straightShoot->addFrame(sf::IntRect(7, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(40, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(40, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(40, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(40, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(40, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(40, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(40, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(71, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(71, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(71, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(71, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(71, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(71, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(71, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(109, 320, 25, -42));
    straightShoot->addFrame(sf::IntRect(138, 320, 25, -42));
    straightShoot->setAnimationPeriod(100);
    straightShoot->setRepeatable(false);
    upShoot->addFrame(sf::IntRect(193, 323, 31, -50));
    upShoot->addFrame(sf::IntRect(226, 323, 31, -50));
    upShoot->addFrame(sf::IntRect(257, 323, 31, -50));
    upShoot->addFrame(sf::IntRect(293, 323, 31, -50));
    upShoot->addFrame(sf::IntRect(321, 323, 31, -50));
    upShoot->setAnimationPeriod(40);
    upShoot->setRepeatable(false);
    downShoot->addFrame(sf::IntRect(385, 323, 31, -42));
    downShoot->addFrame(sf::IntRect(418, 323, 31, -42));
    downShoot->addFrame(sf::IntRect(449, 323, 31, -42));
    downShoot->addFrame(sf::IntRect(484, 323, 31, -42));
    downShoot->addFrame(sf::IntRect(513, 323, 31, -42));
    downShoot->setAnimationPeriod(40);
    downShoot->setRepeatable(false);
    stand->addFrame(sf::IntRect(7, 320, 25, -42));
    stand->setRepeatable(true);
    jumpPrepare->addFrame(sf::IntRect(606, 64, 25, -55));
    jumpPrepare->addFrame(sf::IntRect(606, 64, 25, -55));
    jumpPrepare->addFrame(sf::IntRect(606, 64, 25, -55));
    jumpPrepare->addFrame(sf::IntRect(606, 64, 25, -55));
    jumpUp->addFrame(sf::IntRect(606, 64, 25, -55));
    //jumpUp->addFrame(sf::IntRect(775,129,25,-42));
    jumpFloat->addFrame(sf::IntRect(674, 64, 25, -55));
    jumpFall->addFrame(sf::IntRect(771, 128, 25, -42));
    jumpPrepare->setAnimationPeriod(80);
    jumpPrepare->setRepeatable(false);
    jumpUp->setRepeatable(true);
    jumpFloat->setRepeatable(true);
    jumpFall->setRepeatable(true);
    crouch->addFrame(sf::IntRect(38, 64, 25, -42));
    crouchShoot->addFrame(sf::IntRect(582, 323, 25, -42));
    crouchShoot->addFrame(sf::IntRect(615, 323, 25, -42));
    crouchShoot->addFrame(sf::IntRect(646, 323, 25, -42));
    crouchShoot->addFrame(sf::IntRect(683, 323, 25, -42));
    crouchShoot->addFrame(sf::IntRect(717, 323, 25, -42));
    crouchShoot->addFrame(sf::IntRect(745, 323, 25, -42));
    crouchShoot->setAnimationPeriod(40);
    crouchShoot->setRepeatable(false);
    die->addFrame(sf::IntRect(2, 194, 30, -42));
    die->addFrame(sf::IntRect(2, 194, 30, -42));
    die->addFrame(sf::IntRect(2, 194, 30, -42));
    die->addFrame(sf::IntRect(2, 194, 30, -42));
    die->addFrame(sf::IntRect(2, 194, 30, -42));
    die->addFrame(sf::IntRect(2, 194, 30, -42));
    die->addFrame(sf::IntRect(2, 194, 30, -42));
    die->addFrame(sf::IntRect(38, 194, 30, -42));
    die->addFrame(sf::IntRect(38, 194, 30, -42));
    die->addFrame(sf::IntRect(38, 194, 30, -42));
    die->addFrame(sf::IntRect(38, 194, 30, -42));
    die->addFrame(sf::IntRect(38, 194, 30, -42));
    die->addFrame(sf::IntRect(38, 194, 30, -42));
    die->addFrame(sf::IntRect(68, 194, 30, -42));
    die->addFrame(sf::IntRect(100, 194, 30, -42));
    die->setAnimationPeriod(100);
    die->setRepeatable(false);
}

void Rambo::update() {
    if (curAnim->play()) {
        setTextureRect(curAnim->getCurFrame());
        lowerBound = getLowBound();
    } else if (!shootlocked) {
        if (curAnim == straightShoot || curAnim == upShoot || curAnim == downShoot) {
            clock.restart();
            shootlocked = true;
        }
    }
    if (shootlocked && clock.getElapsedTime().asMilliseconds() > 1000) {
        //shootlocked=false;
    }
    if (running) {
        if (rightdir) {
            vx = 4;
        } else vx = -4;
    }

    vx += ax;
    vy += ay;

    move(vx, vy);

    if (jumping) {
        if (!lowCollide(340)) {
            if (vy < 8 && vy>-8) {
                if (curAnim != jumpFloat) {
                    curAnim->end();
                    curAnim = jumpFloat;
                    if (curAnim->isEnded())curAnim->restart();
                }
            } else if (vy > 8) {
                if (curAnim != jumpFall) {
                    curAnim->end();
                    curAnim = jumpFall;
                    if (curAnim->isEnded())curAnim->restart();
                }
            }
        } else {
            jumping = false;
            standStill();
            setPosition(getPosition().x, 340);
        }
    }
}

void Rambo::jump() {
    //running=false;
    curAnim->end();
    curAnim = jumpPrepare;
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    //while (!curAnim->isEnded());
    vy = -15.99;
    ay = 0.5;
    jumping = true;
    if (curAnim != jumpUp) {
        curAnim->end();
        curAnim = jumpUp;
        if (curAnim->isEnded())curAnim->restart();
    }
    move(0, 1);
}

int Rambo::getLowBound() {
    int upmost = curAnim->getCurFrame().top;
    int lowermost = upmost + curAnim->getCurFrame().height - 1;
    int leftmost = curAnim->getCurFrame().left;
    int rightmost = curAnim->getCurFrame().width + leftmost - 1;
    bool atMiddle;
    for (int i = leftmost; i <= rightmost; i++) {
        if (imgOrigin->getPixel(i, lowermost) != sf::Color::White) {
            return lowermost;
        }
    }
    while (lowermost - upmost >= 1) {
        atMiddle = false;
        int middle = (upmost + lowermost) / 2;
        for (int i = leftmost; i <= rightmost; i++) {
            if (imgOrigin->getPixel(i, middle) != sf::Color::White) {
                atMiddle = true;
                break;
            }
        }
        if (atMiddle) {
            upmost = middle;
        } else {
            lowermost = middle;
        }
    }
    return lowermost;
}

bool Rambo::lowCollide(int ground) {
    float collideLine = getPosition().y; //+lowerBound;
    if (collideLine >= ground - 1) {
        return true;
    } else return false;
}
