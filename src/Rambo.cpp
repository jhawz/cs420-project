//
//  Rambo.cpp
//  jamesrambotest
//
//  Created by gyp on 10/12/14.
//  Copyright (c) 2014 gyp. All rights reserved.
//

#include "Rambo.h"

Rambo::Rambo(){
    alive=true;
    rightdir=true;
    shootlocked=false;
    ax=0;ay=0;
}

Rambo::~Rambo(){
    
}

void Rambo::setOriginalImg(sf::Image &image){
    imgOrigin=&image;
}

bool Rambo::isAlive(){
    return alive;
}

void Rambo::rightRun(){
    if (jumping)return;
    if (!alive)return;
    if (!rightdir) {
        rightdir=true;
        setScale(1, 1);
    }
    if (curAnim!=animations["run"]) {
        curAnim->end();
        curAnim=animations["run"];
    }
    
    if(curAnim->isEnded())curAnim->restart();
    running=true;
    vy=0;
    ax=0;ay=0;
}

void Rambo::leftRun(){
    if (jumping)return;
    if (!alive)return;
    if (rightdir) {
        rightdir=false;
        setScale(-1,1);
    }
    if (curAnim!=animations["run"]) {
        curAnim->end();
        curAnim=animations["run"];
    }
    if(curAnim->isEnded())curAnim->restart();
    running=true;
    vy=0;
    ax=0;ay=0;
}

void Rambo::standStill(){
    running=false;
    if (jumping)return;
    if (!alive)return;
    if (curAnim!=animations["stand"]) {
        curAnim->end();
        curAnim=animations["stand"];
    }
    curAnim->restart();
    vy=0;ay=0;
    vx=0;ax=0;
    //vxmax=0;vymax=0;
    //vxmin=0;vymin=0;
    //ax=0;ay=0;
}

void Rambo::shoot(){
    if (jumping)return;
    if (!alive)return;
    /*if (shootlocked){
        if (curAnim==straightShoot) {
            curAnim->end();
        }
        return;
    }*/
    curAnim->end();
    curAnim=animations["straight_shoot"];
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    running=false;
}

void Rambo::upshoot(){
    if (jumping)return;
    if (!alive)return;
    /*if (shootlocked){
        if (curAnim==upShoot) {
            curAnim->end();
        }
        return;
    }*/
    curAnim->end();
    curAnim=animations["up_shoot"];
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    running=false;
}

void Rambo::downshoot(){
    if (jumping)return;
    if (!alive)return;
    /*if (shootlocked){
        if (curAnim==downShoot) {
            curAnim->end();
        }
        return;
    }*/
    curAnim->end();
    curAnim=animations["down_shoot"];
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    running=false;
}

void Rambo::crouchStill(){
    if (!alive)return;
    curAnim->end();
    curAnim=animations["crouch"];
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    running=false;
}

void Rambo::crouchshoot(){
    if (!alive)return;
    curAnim->end();
    curAnim=animations["crouch_shoot"];
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    running=false;
}

void Rambo::shotDead(){
    if (!alive)return;
    if(curAnim!=animations["die"])curAnim->end();
    curAnim=animations["die"];
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    alive=false;
}

void Rambo::prepareFrameInfo(pugi::xml_node& node){
    std::istringstream ss(std::string(node.child("Animation_List").text().as_string()));
    std::string token;
    while (std::getline(ss, token,',')) {
        pugi::xml_node curnode=node.find_child_by_attribute("Animation", "name", token.c_str());
        Animation* a=new Animation();
        a->loadFromXml(curnode);
        animations.insert(std::pair<std::string,Animation*>(token,a));
    }
    curAnim=animations["stand"];
    curAnim->restart();
}


void Rambo::update(){
    if (curAnim->play()) {
        setTextureRect(curAnim->getCurFrame());
        lowerBound=getLowBound();
    }
    else if (!shootlocked){
        if (curAnim==animations["straight_shoot"]||curAnim==animations["up_shoot"]||curAnim==animations["down_shoot"]) {
            clock.restart();
            shootlocked=true;
        }
    }
    if (shootlocked&&clock.getElapsedTime().asMilliseconds()>1000) {
        //shootlocked=false;
    }
    if (running) {
        if (rightdir) {
            vx=8;
        }
        else vx=-8;
    }
    
    vx+=ax;
    vy+=ay;
    
    move(vx, vy);
    
    if (jumping) {
        if (!lowCollide(400)) {
            if (vy<8&&vy>-8){
                if (curAnim!=animations["jump_float"]) {
                    curAnim->end();
                    curAnim=animations["jump_float"];
                    if (curAnim->isEnded())curAnim->restart();
                }
            }
            else if(vy>8){
                if (curAnim!=animations["jump_fall"]) {
                 curAnim->end();
                 curAnim=animations["jump_fall"];
                 if (curAnim->isEnded())curAnim->restart();
                 }
            }
        }
        else{
            jumping=false;
            //standStill();
            if (running) {
                if (rightdir) {
                    rightRun();
                }
                else leftRun();
            }
            else standStill();
            setPosition(getPosition().x, 400);
            jumping=false;
        }
    }
}

void Rambo::jump(){
    if (jumping) {
        return;
    }
    //running=false;
    curAnim->end();
    curAnim=animations["jump_prepare"];
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    //while (!curAnim->isEnded());
    vy=-9.99;
    ay=0.5;
    jumping=true;
    if (curAnim!=animations["jump_up"]) {
        curAnim->end();
        curAnim=animations["jump_up"];
        if (curAnim->isEnded())curAnim->restart();
    }
    move(0, 1);
}

int Rambo::getLowBound(){
    int upmost=curAnim->getCurFrame().top;
    int lowermost=upmost+curAnim->getCurFrame().height-1;
    int leftmost=curAnim->getCurFrame().left;
    int rightmost=curAnim->getCurFrame().width+leftmost-1;
    bool atMiddle;
    for (int i=leftmost; i<=rightmost; i++) {
        if (imgOrigin->getPixel(i, lowermost)!=sf::Color::White) {
            return lowermost;
        }
    }
    while (lowermost-upmost>=1) {
        atMiddle=false;
        int middle=(upmost+lowermost)/2;
        for (int i=leftmost; i<=rightmost; i++) {
            if (imgOrigin->getPixel(i, middle)!=sf::Color::White) {
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
    return lowermost;
}

void Rambo::setMoving(bool moving){
    running=moving;
}

bool Rambo::lowCollide(int ground){
    float collideLine=getPosition().y;//+lowerBound;
    if (collideLine>=ground-1) {
        return true;
    }
    else return false;
}
