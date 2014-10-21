
#include "Enemy.h"

Enemy::Enemy() {
    run = new Animation();
    stand = new Animation();
    curAnim = stand;
    curAnim->restart();
    rightdir = true;
    alive = true;
    attack = true;
}

Enemy::~Enemy() {
    delete run;
    delete stand;
}

bool Enemy::isAlive() {
    return alive;
}

bool Enemy::isAttacking() {
    return attack;
}

void Enemy::setAttack(bool x) {
    attack = x;
}

void Enemy::rightRun() {
    if (!rightdir) {
        rightdir = true;
        setScale(-1, 1);
    }
    if (curAnim != run) {
        curAnim->end();
        curAnim = run;
    }

    if (curAnim->isEnded())curAnim->restart();
    running = true;
}

void Enemy::leftRun() {
    if (rightdir) {
        rightdir = false;
        setScale(1, 1);
    }
    if (curAnim != run) {
        curAnim->end();
        curAnim = run;
    }
    if (curAnim->isEnded())curAnim->restart();
    running = true;
}

void Enemy::standStill() {
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

void Enemy::setPistol() {
    run->addFrame(sf::IntRect(11, 597, 30, 43));
    run->addFrame(sf::IntRect(49, 597, 30, 43));
    run->addFrame(sf::IntRect(84, 597, 30, 43));
    run->addFrame(sf::IntRect(113, 597, 30, 43));
    run->addFrame(sf::IntRect(144, 597, 30, 43));
    run->addFrame(sf::IntRect(180, 597, 30, 43));
    run->addFrame(sf::IntRect(215, 597, 30, 43));
    run->addFrame(sf::IntRect(244, 597, 30, 43));
    run->setAnimationPeriod(40);
    stand->addFrame(sf::IntRect(300, 597, 30, 43));
}

void Enemy::update() {
    if (curAnim->play()) {
        setTextureRect(curAnim->getCurFrame());
    }
    if (running) {
        if (rightdir) {
            vx = 8;
        } else vx = -8;
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
