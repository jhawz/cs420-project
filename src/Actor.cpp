//
//  Actor.cpp
//  jamesrambotest
//
//  Created by gyp on 11/4/14.
//  Copyright (c) 2014 gyp. All rights reserved.
//

#include "Actor.h"
#include <cstddef>

Actor::Actor(){
    vx=0;vy=0;
    ax=0;ay=0;
    alive=true;
    rightdir=true;
    shootlocked=false;
    GetSprite().setTextureRect(sf::IntRect(0, 0, 32, 64));
}

void Actor::prepareFrameInfo(pugi::xml_node& node){
    int t=node.attribute("attack_lock").as_int();
    shootWait=sf::milliseconds(t);
    std::istringstream ss(std::string(node.child("Animation_List").text().as_string()));
    std::string token;
    while (std::getline(ss, token,',')) {
        pugi::xml_node curnode=node.find_child_by_attribute("Animation", "name", token.c_str());
        Animation* a=new Animation();
        a->loadFromXml(curnode);
        animations.insert(std::pair<std::string,Animation*>(token,a));
    }
    curAnim=NULL;
    animReq("stand", false);
}

void Actor::animReq(std::string animName, bool withlock){
    if (curAnim!=animations[animName]&&!withlock) {
        if(curAnim!=NULL){curAnim->end();}
        curAnim=animations[animName];
    }
    else if (withlock){
        return;
    }
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
}

void Actor::rightRun(){
    if (!alive)return;
    if (!rightdir) {
        rightdir=true;
        GetSprite().setScale(1, 1);
    }
    animReq("run", false);
    vx=8;vy=0;
    ax=0;ay=0;
}

void Actor::rightMove()
{
    vx=8;
}

void Actor::leftMove()
{
    vx=-8;
}

void Actor::leftRun(){
    if (!alive)return;
    if (rightdir) {
        rightdir=false;
        GetSprite().setScale(-1,1);
    }
    animReq("run", false);
    vx=-8;vy=0;
    ax=0;ay=0;
}
float Actor::getLowBound(){
    int upmost=curAnim->getCurFrame().top;
    int lowermost=upmost+curAnim->getCurFrame().height-1;
    int leftmost=curAnim->getCurFrame().left;
    int rightmost=curAnim->getCurFrame().width+leftmost-1;
    bool atMiddle;
    for (int i=leftmost; i<=rightmost; i++) {
        if (image->getPixel(i, lowermost)!=sf::Color::White) {
            return lowermost;
        }
    }
    while (lowermost-upmost>=1) {
        atMiddle=false;
        int middle=(upmost+lowermost)/2;
        for (int i=leftmost; i<=rightmost; i++) {
            if (image->getPixel(i, middle)!=sf::Color::Transparent) {
                atMiddle=true;
                break;
            }
        }
        if (atMiddle) {
            upmost=middle;
        } else {
            lowermost=middle;
        }
    }
    return lowermost-curAnim->getCurFrame().top;
}

void Actor::attack(){
    if (!alive)return;
    if (shootlocked)return;
    
    animReq("straight_shoot", shootlocked);
    shootlocked=true;
    clock.restart();
}

void Actor::die(){
    if (!alive)return;
    vx=0;vy=0;ax=0;ay=0;
    animReq("die", false);
    alive=false;
}

void Actor::standStill(){
    if (!alive) {
        return;
    }
    vx=0;vy=0;ax=0;ay=0;
    animReq("stand", false);
}

void Actor::Update(float elapsedTime){
    vx+=ax*elapsedTime;
    vy+=ay*elapsedTime;
    sf::Vector2f pos=GetPosition();
    SetPosition(pos.x+vx*elapsedTime, pos.y+vy*elapsedTime);
    if (curAnim->play()) {
        GetSprite().setTextureRect(curAnim->getCurFrame());
     //   lowerBound = getLowBound();
    }
    if (shootlocked) {
        sf::Time waited=clock.getElapsedTime();
        if (waited>shootWait) {
            shootlocked=false;
        }
    }

}

void Actor::setOriginalImg(sf::Image &img){
    image=&img;
}

bool Actor::hasAnimation(std::string name){
    return (animations.find(name)!=animations.end());
}

bool Actor::isCurAnim(std::string name){
    return curAnim==animations[name];
}

void Actor::setLeftPress(bool p){
    leftpressed=p;
}

void Actor::setRightPress(bool p){
    rightpressed=p;
}

void Actor::setUpPress(bool p){
    uppressed=p;
}

void Actor::setDownPress(bool p){
    downpressed=p;
}

void Actor::setBoundary(float left, float up, float right, float lower) {
    upperleft = sf::Vector2f(left, up);
    lowerright = sf::Vector2f(right, lower);
}

bool Actor::lowCollide() {
   // return GetPosition().y + lowerBound >= lowerright.y;
    return GetPosition().y >= lowerright.y;
}

bool Actor::IsAlive(){
    return alive;
}