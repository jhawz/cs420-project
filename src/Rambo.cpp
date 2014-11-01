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
    run=new Animation();
    stand=new Animation();
    straightShoot=new Animation();
    upShoot=new Animation();
    downShoot=new Animation();
    jumpPrepare=new Animation();
    jumpUp=new Animation();
    jumpFloat=new Animation();
    jumpFall=new Animation();
    crouch=new Animation();
    crouchShoot=new Animation();
    die=new Animation();
    curAnim=stand;
    curAnim->restart();
    rightdir=true;
    shootlocked=false;
    ax=0;ay=0;
}

Rambo::~Rambo(){
    delete run;
    delete stand;
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
    if (curAnim!=run) {
        curAnim->end();
        curAnim=run;
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
    if (curAnim!=run) {
        curAnim->end();
        curAnim=run;
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
    if (curAnim!=stand) {
        curAnim->end();
        curAnim=stand;
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
    curAnim=straightShoot;
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
    curAnim=upShoot;
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
    curAnim=downShoot;
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    running=false;
}

void Rambo::crouchStill(){
    if (!alive)return;
    curAnim->end();
    curAnim=crouch;
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    running=false;
}

void Rambo::crouchshoot(){
    if (!alive)return;
    curAnim->end();
    curAnim=crouchShoot;
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    running=false;
}

void Rambo::shotDead(){
    if (!alive)return;
    if(curAnim!=die)curAnim->end();
    curAnim=die;
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    alive=false;
}

void Rambo::prepareFrameInfo(pugi::xml_node& node){
    pugi::xml_node runnode=node.find_child_by_attribute("Animation", "name", "run");
    run->loadFromXml(runnode);
    pugi::xml_node strshootnode=node.find_child_by_attribute("Animation", "name", "straight_shoot");
    straightShoot->loadFromXml(strshootnode);
    pugi::xml_node upshootnode=node.find_child_by_attribute("Animation", "name", "up_shoot");
    upShoot->loadFromXml(upshootnode);
    pugi::xml_node dshootnode=node.find_child_by_attribute("Animation", "name", "down_shoot");
    downShoot->loadFromXml(dshootnode);
    pugi::xml_node standnode=node.find_child_by_attribute("Animation", "name", "stand");
    stand->loadFromXml(standnode);
    pugi::xml_node jprepnode=node.find_child_by_attribute("Animation", "name", "jump_prepare");
    jumpPrepare->loadFromXml(jprepnode);
    pugi::xml_node jupnode=node.find_child_by_attribute("Animation", "name", "jump_up");
    jumpUp->loadFromXml(jupnode);
    pugi::xml_node jflnode=node.find_child_by_attribute("Animation", "name", "jump_float");
    jumpFloat->loadFromXml(jflnode);
    pugi::xml_node jfallnode=node.find_child_by_attribute("Animation", "name", "jump_fall");
    jumpFall->loadFromXml(jfallnode);
    pugi::xml_node crouchnode=node.find_child_by_attribute("Animation", "name", "crouch");
    crouch->loadFromXml(crouchnode);
    pugi::xml_node cshootnode=node.find_child_by_attribute("Animation", "name", "crouch_shoot");
    crouchShoot->loadFromXml(cshootnode);
    pugi::xml_node dienode=node.find_child_by_attribute("Animation", "name", "die");
    die->loadFromXml(dienode);
}


void Rambo::update(){
    if (curAnim->play()) {
        setTextureRect(curAnim->getCurFrame());
        lowerBound=getLowBound();
    }
    else if (!shootlocked){
        if (curAnim==straightShoot||curAnim==upShoot||curAnim==downShoot) {
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
                if (curAnim!=jumpFloat) {
                    curAnim->end();
                    curAnim=jumpFloat;
                    if (curAnim->isEnded())curAnim->restart();
                }
            }
            else if(vy>8){
                if (curAnim!=jumpFall) {
                 curAnim->end();
                 curAnim=jumpFall;
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
    curAnim=jumpPrepare;
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
    //while (!curAnim->isEnded());
    vy=-9.99;
    ay=0.5;
    jumping=true;
    if (curAnim!=jumpUp) {
        curAnim->end();
        curAnim=jumpUp;
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
