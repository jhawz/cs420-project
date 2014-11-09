#include "Bond.h"

Bond::Bond(std::string config,std::string texture):Actor::Actor(){
    pugi::xml_document doc;
    doc.load_file(config.c_str());
    
    pugi::xml_node bondnode=doc.child("root").find_child_by_attribute("Actor", "name", "Bond");
    
    if (bondnode.empty()) {
        //if there is an error in node initialization
        std::cout<<"Can't find Bond actor node..."<<std::endl;
        return;
    }
    std::cout<<"start preparing frames"<<std::endl;
    prepareFrameInfo(bondnode);
    std::cout<<"Finish preparing frames"<<std::endl;
    Load(texture);
    jumping=false;
    sf::Image *img=new sf::Image();
    if (!img->loadFromFile(texture)) {
        return;
    }
    setOriginalImg(*img);
}

void Bond::jump(){
    if (jumping) {
        return;
    }
    animReq("jump_prepare", false);
    vy=-9.99;
    ay=0.5;
    jumping=true;
    animReq("jump_up", false);
}

void Bond::setBoundary(float left, float up, float right, float lower){
    upperleft=sf::Vector2f(left,up);
    lowerright=sf::Vector2f(right,lower);
}

bool Bond::lowCollide(){
    return GetPosition().y+64>=lowerright.y;
}

void Bond::Update(float elapsedTime){
    Actor::Update(elapsedTime);
    if (!lowCollide()) {
        if (ay==0) {
            ay=0.1;
            jumping=true;
            animReq("jump_fall", false);
            std::cout<<"Falling"<<std::endl;
        }
        else if (vy>-6&&vy<6){
            animReq("jump_float", false);
        }
        else if (vy>6){
            animReq("jump_fall", false);
        }
    }
    else{
        jumping=false;
        SetPosition(GetPosition().x, lowerright.y);
        if (vx==8) {
            rightRun();
        }
        else if (vx==-8){
            leftRun();
        }
        else if (vx==0){
            standStill();
        }
    }
}

void Bond::crouchStill(){
    if (!alive) {
        return;
    }
    animReq("crouch", false);
}

void Bond::upshoot(){
    if (!alive)return;
    if (shootlocked)return;
    
    animReq("up_shoot", shootlocked);
    shootlocked=true;
    clock.restart();
}

void Bond::downshoot(){
    if (!alive)return;
    if (shootlocked)return;
    
    animReq("down_shoot", shootlocked);
    shootlocked=true;
    clock.restart();
}

void Bond::crouchshoot(){
    if (!alive)return;
    if (shootlocked)return;
    
    animReq("crouch_shoot", shootlocked);
    shootlocked=true;
    clock.restart();
}

