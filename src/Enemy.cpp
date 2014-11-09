
#include "Enemy.h"


Enemy::Enemy(std::string config,std::string texture,std::string name){
        pugi::xml_document doc;
        doc.load_file(config.c_str());
        
        pugi::xml_node enemynode=doc.child("root").find_child_by_attribute("Actor", "name", name.c_str());
        
        if (enemynode.empty()) {
            //if there is an error in node initialization
            return;
        }
        prepareFrameInfo(enemynode);
        Load(texture);
}

void Enemy::leftwalk(){
    if (!alive)return;
    if (!rightdir) {
        rightdir=true;
        GetSprite().setScale(1, 1);
    }
    animReq("walk", false);
    vx=2;vy=0;
    ax=0;ay=0;
}

void Enemy::rightwalk(){
    if (!alive)return;
    if (rightdir) {
        rightdir=false;
        GetSprite().setScale(-1,1);
    }
    animReq("walk", false);
    vx=-2;vy=0;
    ax=0;ay=0;
}
