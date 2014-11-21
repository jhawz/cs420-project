#include "Bullet.h"
void Bullet::prepareFrameInfo(pugi::xml_node& node){
    std::istringstream ss(std::string(node.child("Animation_List").text().as_string()));
    std::string token;
    while (std::getline(ss, token,',')) {
        pugi::xml_node curnode=node.find_child_by_attribute("Animation", "name", token.c_str());
        Animation* a=new Animation();
        a->loadFromXml(curnode);
        animations.insert(std::pair<std::string,Animation*>(token,a));
    }
    curAnim=NULL;
}

void Bullet::animReq(std::string animName){
    if (curAnim!=animations[animName]) {
        if(curAnim!=NULL){curAnim->end();}
        curAnim=animations[animName];
    }
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
}

Bullet::Bullet(std::string config,std::string texture,int direction){
    type = 4;
    vx=0;vy=0;
    objectType="Bullet";
    pugi::xml_document doc;
        GetSprite().setTextureRect(sf::IntRect(896, 0, 32, 64));
    doc.load_file(config.c_str());
    
    pugi::xml_node bulletnode = doc.child("root").find_child_by_attribute("Object", "name", "Bullet");
    
    if (bulletnode.empty()) {
        //if there is an error in node initialization
        std::cout << "Can't find Bond actor node..." << std::endl;
        return;
    }
    //  std::cout << "start preparing frames" << std::endl;
    prepareFrameInfo(bulletnode);
    // std::cout << "Finish preparing frames" << std::endl;
    Load(texture);
    switch (direction) {
        case right:
            straightRight();
            break;
        case left:
            straightLeft();
            break;
        case upleft:
            upLeft();
            break;
        case upright:
            upRight();
            break;
        case downleft:
            downLeft();
            break;
        case downright:
            downRight();
            break;
        default:
            break;
    }
    to_delete=false;
}

void Bullet::setBoundary(float left, float right){
    leftBoundary=left;
    rightBoundary=right;
}

void Bullet::Update(float elapsedTime){
    std::cout << "bullet update" << std::endl;
    if (curAnim!=NULL) {
        if (curAnim->play()) {
            GetSprite().setTextureRect(curAnim->getCurFrame());
        }
        sf::Vector2f pos=GetPosition();
        SetPosition(pos.x+vx*elapsedTime, pos.y+vy*elapsedTime);
        if (pos.x+vx*elapsedTime<=leftBoundary||pos.x+vx*elapsedTime>=rightBoundary) {
            animReq("disappear");
            to_delete=true;
        }
    }
}

bool Bullet::isDead(){
    return to_delete;
}

void Bullet::straightLeft(){
    vx=-16;vy=0;
    animReq("straight");
    GetSprite().setScale(-1, 1);
}

void Bullet::straightRight(){
    vx=16;vy=0;
    animReq("straight");
    GetSprite().setScale(1, 1);
}

void Bullet::upLeft(){
    vx=-12;vy=-12;
    animReq("up");
    GetSprite().setScale(-1, 1);
}

void Bullet::upRight(){
    vx=12;vy=-12;
    animReq("up");
    GetSprite().setScale(1, 1);
}

void Bullet::downLeft(){
    vx=-12;vy=12;
    animReq("down");
    GetSprite().setScale(-1, 1);
}

void Bullet::downRight(){
    vx=12;vy=12;
    animReq("down");
    GetSprite().setScale(1, 1);
}
