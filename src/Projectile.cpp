
#include "Projectile.h"

Projectile::Projectile() {
    fired = new Animation();
    curAnim = fired;
    curAnim->restart();
    rightdir = true;
    active = false;
    vy=0;
}

Projectile::~Projectile() {
    delete fired;
}

bool Projectile::isActive() {
    return active;
}

void Projectile::fire(){
    active = true;
}

void Projectile::deactivate(){
    active = false;
}

void Projectile::rightFly() {
    if (!rightdir) {
        rightdir = true;
        setScale(-1, 1);
    }
    if (curAnim != fired) {
        curAnim->end();
        curAnim = fired;
    }

    if (curAnim->isEnded())curAnim->restart();
    active = true;
}

void Projectile::leftFly() {
    if (rightdir) {
        rightdir = false;
        setScale(1, 1);
    }
    if (curAnim != fired) {
        curAnim->end();
        curAnim = fired;
    }
    if (curAnim->isEnded())curAnim->restart();
    active = true;
}

void Projectile::setBullet() {
    fired->addFrame(sf::IntRect(485, 481, 2, 8));
    fired->setRepeatable(true);
    fired->setAnimationPeriod(40);
}

void Projectile::update() {
    if (curAnim->play()) {
        setTextureRect(curAnim->getCurFrame());
    }
    if (active) {
        if (rightdir) {
            vx = 8;
        } else vx = -8;
    }
    move(vx, vy);
}
