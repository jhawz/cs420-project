#include "Jaw.h"

Jaw::Jaw(std::string config, std::string texture) : Actor::Actor() {
    pugi::xml_document doc;
    doc.load_file(config.c_str());

    pugi::xml_node enemynode = doc.child("root").find_child_by_attribute("Actor"
            , "name", "Jaw");

    if (enemynode.empty()) {
        //if there is an error in node initialization
        return;
    }
    prepareFrameInfo(enemynode);
    Load(texture);
    sf::Image *img = new sf::Image();
    if (!img->loadFromFile(texture)) {
        return;
    }
    setOriginalImg(*img);
    alive = true;
    type = VisibleGameObject::JAWS;
    GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, 0);
    attackRate = 4.0;
    rightpressed = true;
    lives = 12;
}
Jaw::Jaw(std::string config, sf::Texture& t) : Actor::Actor() {
    pugi::xml_document doc;
    doc.load_file(config.c_str());
    
    pugi::xml_node enemynode = doc.child("root").find_child_by_attribute("Actor"
            ,"name", "Jaw");
    
    if (enemynode.empty()) {
        //if there is an error in node initialization
        return;
    }
    prepareFrameInfo(enemynode);
    Load(t, sf::Vector2i(0, 0), sf::Vector2i(32, 64));
    sf::Image *img = new sf::Image();
    alive = true;
    type = VisibleGameObject::JAWS;
    rightpressed = true;
    GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, 0);
    attackRate = 4.0;
    lives = 12;
}
void Jaw::leftwalk() {
    if (!alive)return;
    if (!rightdir) {
        rightdir = true;
     //   GetSprite().setScale(-1, 1);
    }
    animReq("walk", false);
    vx = -2;
    vy = 0;
    ax = 0;
    ay = 0;
}
void Jaw::rightwalk() {
    if (!alive)return;
    if (rightdir) {
        rightdir = false;
   //     GetSprite().setScale(1, 1);
    }
    animReq("walk", false);
    vx = 2;
    vy = 0;
    ax = 0;
    ay = 0;
}
void Jaw::Update(float elapsedTime) {
    Actor::Update(elapsedTime);

    if (!lowCollide()) {
        if (ay == 0)
            ay = 2;
    } else if (lowCollide()) {
        // jumping = false;
        ay = 0;
        vy = 0;
        SetPosition(GetPosition().x, lowerright.y - 64);
        //standStill();
    } if (rightpressed) {
            rightRun();
        } else if (leftpressed) {
            leftRun();
        } else if (isCurAnim("run")) {
            standStill();
        }
   // establish movement
     if (isAlive())
        {
        patrol();
        }   
}
void Jaw::patrol(){
    
    if (isAttacking)
    {
        if (bondLoc.x < GetPosition().x)
        {
            if (!attackingLeft)
            {
                GetSprite().setScale(1, 1);
                setFacingLeft();
                straightShoot();
                std::cout << "Attacking!" << std::endl;
                attackingLeft = true;
                attackingRight = false;
                rightpressed = false;
                leftpressed = false;
            }
        }
        else if (bondLoc.x > GetPosition().x)
        {
            if (!attackingRight)
            {
                GetSprite().setScale(-1, 1);
                setFacingRight();
                straightShoot();
                std::cout << "Attacking!" << std::endl;
                attackingRight = true;
                attackingLeft = false;
                rightpressed = false;
                leftpressed = false;
            }
        }
        straightShoot();
    }
    else if (leftCollide() || GetPosition().x < origPos.x - 150)
    {
        rightpressed = true;
        leftpressed = false;
    }
    else if (rightCollide() || GetPosition().x > origPos.x + 150)
    {
        leftpressed = true;
        rightpressed = false;
    }
    
    if (attackCheck())
    {
        isAttacking = true;
    }
    else
    {
        isAttacking = false;
    }
}

bool Jaw::bondInRange()
{
    
    return (GetPosition().x - bondLoc.x >= -50) && 
                (GetPosition().x - bondLoc.x <= 50);
    
}

bool Jaw::attackCheck()
{
    //Ensure that bond is in range...
    if (bondLoc.x - GetPosition().x < 350 
            && bondLoc.x - GetPosition().x > -350
            && bondLoc.y - GetPosition().y < 64
            && bondLoc.y - GetPosition().y > -64)
    {
        //Dumb down difficulty a bit. Enemies only shoot if they see Bond!
        if (GetSprite().getScale().x == 1 && GetPosition().x > bondLoc.x)
        {
            return true;
        }
        else if (GetSprite().getScale().x == -1 && GetPosition().x < bondLoc.x)
        {
            return true;
        }
        else
            return false;
    }
}
void Jaw::straightShoot()
{
        if ((shotClock.getElapsedTime().asSeconds() >= attackRate) 
                && isAlive() && bondInRange()){
            Actor::attack();
            shotClock.restart();
            grabbedBond = true;
        }

}
void Jaw::rightRun()
{
    animReq("run", false);
    vx = 8;
    GetSprite().setScale(-1, 1);
}

bool Jaw::isAlive(){
    return alive;
}

void Jaw::die()
{
    lives--;
    if (lives <= 0)
    {
        Actor::die();
        vy = 0;
        vx = 0;
        animReq("die", false);
    }
}


void Jaw::leftRun()
{
    animReq("run", false);
    vx = -8;
    GetSprite().setScale(1,1);
}
void Jaw::setBoundary(float left, float up, float right, float lower) {
    upperleft = sf::Vector2f(left, up);
    lowerright = sf::Vector2f(right, lower);
}
bool Jaw::lowCollide() {
    return GetPosition().y + 64 >= lowerright.y;
}
bool Jaw::rightCollide() {
    return GetPosition().x + 32 >= lowerright.x;
}

bool Jaw::leftCollide() {
    return GetPosition().x <= upperleft.x;
}
void Jaw::setOrigPos(sf::Vector2f loc)
{
    origPos = loc;
}
sf::Vector2f Jaw::getBondLocation(){
    return bondLoc;
}
void Jaw::setBondLocation(sf::Vector2f bL){
    bondLoc = bL;
}
