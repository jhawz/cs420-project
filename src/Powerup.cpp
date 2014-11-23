#include "Powerup.h"

Powerup::Powerup(std::string config,std::string texture){
    objectType="Powerup";
    pugi::xml_document doc;
    doc.load_file(config.c_str());
    
    pugi::xml_node bulletnode = doc.child("root").find_child_by_attribute("Object", "name", "Powerup");
    if (bulletnode.empty()) {
        std::cout << "Can't find Bond actor node..." << std::endl;
        return;
    }
    prepareFrameInfo(bulletnode);
    Load(texture);
    used=false;
}
Powerup::Powerup(std::string config, sf::Texture& t, int sheetPositionInFrames)
{
    objectType="Powerup";
    type = 5;
    pugi::xml_document doc;
    doc.load_file(config.c_str());
    
    pugi::xml_node bulletnode = 
            doc.child("root").find_child_by_attribute("Object", "name", 
            "Powerup");
    if (bulletnode.empty()) {
        std::cout << "Can't find Bond actor node..." << std::endl;
        return;
    }
    
    prepareFrameInfo(bulletnode);
    
    sf::Vector2i sheetPos(sheetPositionInFrames % 10, (sheetPositionInFrames / 10));
    
    Load(t, sheetPos, sf::Vector2i(32, 64));
    used=false;
}

void Powerup::prepareFrameInfo(pugi::xml_node& node){
    std::istringstream ss(std::string(node.child("Animation_List").text().as_string()));
    std::string token;
    while (std::getline(ss, token,',')) {
        pugi::xml_node curnode=node.find_child_by_attribute("Animation", "name", token.c_str());
        Animation* a=new Animation();
        a->loadFromXml(curnode);
        animations.insert(std::pair<std::string,Animation*>(token,a));
    }
    curAnim=NULL;
    animReq("still");
}

void Powerup::animReq(std::string animName){
    if (curAnim!=animations[animName]) {
        if(curAnim!=NULL){curAnim->end();}
        curAnim=animations[animName];
    }
    if (curAnim->isEnded()) {
        curAnim->restart();
    }
}

void Powerup::Update(float elapsedTime){
    if (curAnim->play()) {
        GetSprite().setTextureRect(curAnim->getCurFrame());
    }
    else if (curAnim==animations["explode"]){
        animReq("disappear");
    }
}

void Powerup::disappear(){
    animReq("explode");
    used=true;
}

bool Powerup::isDead(){
    return used;
}