#include "Enemy.h"
#include "ServiceLocator.h"

Enemy::Enemy(std::string config, std::string texture, std::string name) : Actor::Actor() {
    pugi::xml_document doc;
    doc.load_file(config.c_str());

    pugi::xml_node enemynode = doc.child("root").find_child_by_attribute("Actor"
            , "name", name.c_str());

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
    type = VisibleGameObject::ENEMY;
    GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, 0);
    attackRate = 2.0;
}
Enemy::Enemy(std::string config, sf::Texture& t, std::string name, float fireRate) : Actor::Actor() {
    pugi::xml_document doc;
    doc.load_file(config.c_str());
    
    pugi::xml_node enemynode = doc.child("root").find_child_by_attribute("Actor"
            ,"name", name.c_str());
    
    if (enemynode.empty()) {
        //if there is an error in node initialization
        return;
    }
    prepareFrameInfo(enemynode);
    Load(t, sf::Vector2i(0, 0), sf::Vector2i(32, 64));
    sf::Image *img = new sf::Image();
    alive = true;
    type = VisibleGameObject::ENEMY;
    rightpressed = true;
    GetSprite().setOrigin(GetSprite().getGlobalBounds().width / 2, 0);
    attackRate = fireRate;
}
void Enemy::leftwalk() {
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
void Enemy::rightwalk() {
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
void Enemy::Update(float elapsedTime) {
    Actor::Update(elapsedTime);

    if (!lowCollide()) {
        if (ay == 0)
            ay = 2;
    } else if (lowCollide()) {
        // jumping = false;
        ay = 0;
        vy = 0;
        SetPosition(GetPosition().x, lowerright.y - 64);
       // standStill();
    } if (rightpressed) {
            rightRun();
        } else if (leftpressed) {
            leftRun();
        } else if (isCurAnim("run")) {
            standStill();
        }
    //establish movement
     if (isAlive())
        {
        patrol();
        }   
}
void Enemy::patrol(){
    
    if (isAttacking)
    {
        if (bondLoc.x < GetPosition().x)
        {
            if (!attackingLeft)
            {
                GetSprite().setScale(1, 1);
                standStill();
                setFacingLeft();
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
                standStill();
                setFacingRight();
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
bool Enemy::attackCheck()
{
    //Ensure that bond is in range...
    if (bondLoc.x - GetPosition().x < 200 
            && bondLoc.x - GetPosition().x > -200
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
void Enemy::straightShoot()
{
        if ((shotClock.getElapsedTime().asSeconds() >= attackRate) 
                && isAlive()){
            setFiring(true);
            Actor::attack();
            ServiceLocator::GetAudio()->PlaySound("sounds/pistol.ogg");
            shotClock.restart();
        }
}
void Enemy::rightRun()
{
    Actor::rightRun();
    GetSprite().setScale(-1, 1);
}

bool Enemy::isAlive(){
    return alive;
}

void Enemy::leftRun()
{
    Actor::leftRun();
    GetSprite().setScale(1,1);
}
void Enemy::setBoundary(float left, float up, float right, float lower) {
    upperleft = sf::Vector2f(left, up);
    lowerright = sf::Vector2f(right, lower);
}
bool Enemy::lowCollide() {
    return GetPosition().y + 64 >= lowerright.y;
}
bool Enemy::rightCollide() {
    return GetPosition().x >= lowerright.x;
}

bool Enemy::leftCollide() {
    return GetPosition().x <= upperleft.x;
}
void Enemy::setOrigPos(sf::Vector2f loc)
{
    origPos = loc;
}
sf::Vector2f Enemy::getBondLocation(){
    return bondLoc;
}
void Enemy::setBondLocation(sf::Vector2f bL){
    bondLoc = bL;
}
