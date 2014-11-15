
#include "Enemy.h"


Enemy::Enemy(std::string config,std::string texture,std::string name):Actor::Actor(){
        pugi::xml_document doc;
        doc.load_file(config.c_str());
        
        pugi::xml_node enemynode=doc.child("root").find_child_by_attribute("Actor", "name", name.c_str());
        
        if (enemynode.empty()) {
            //if there is an error in node initialization
            return;
        }
        prepareFrameInfo(enemynode);
        Load(texture);
        sf::Image *img=new sf::Image();
        if (!img->loadFromFile(texture)) {
                return;
        }
        setOriginalImg(*img);
        alive = true;
        type = 2;
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

void Enemy::Update(float elapsedTime)
{
    Actor::Update(elapsedTime);
  //  std::cout << " In Enemy Update " << "Low Collide = " << lowerright.y << std::endl;

    if (!lowCollide()) {
        if (ay == 0)
            ay = 2;
    }
    else if (lowCollide()) {
       // jumping = false;
        ay = 0;
        vy = 0;
        SetPosition(GetPosition().x, lowerright.y - 64);
            standStill();
    } else  {
        if (rightpressed) {
            rightRun();
        } else if (leftpressed) {
            leftRun();
        } else if (isCurAnim("run")) {
            standStill();
        }
    }
    
    }

    void Enemy::setBoundary(float left, float up, float right, float lower) {
        upperleft = sf::Vector2f(left, up);
        lowerright = sf::Vector2f(right, lower);
}

    bool Enemy::lowCollide() {
    return GetPosition().y + 64 >= lowerright.y;
}

