#include "Jaw.h"

Jaw::Jaw(std::string config, std::string texture):Actor::Actor(){
    objectType="Jaw";
    pugi::xml_document doc;
    doc.load_file(config.c_str());
    
    pugi::xml_node jawnode = doc.child("root").find_child_by_attribute("Actor", "name", "Jaw");
    
    if (jawnode.empty()) {
        //if there is an error in node initialization
        std::cout << "Can't find Bond actor node..." << std::endl;
        return;
    }
    //  std::cout << "start preparing frames" << std::endl;
    prepareFrameInfo(jawnode);
    // std::cout << "Finish preparing frames" << std::endl;
    Load(texture);
    sf::Image *img = new sf::Image();
    if (!img->loadFromFile(texture)) {
        return;
    }
    setOriginalImg(*img);
    type = VisibleGameObject::JAWS;
    alive = true;
    lives=12;
    
}

Jaw::Jaw(std::string config, sf::Texture& t):Actor::Actor()
{
        objectType="Jaw";
    pugi::xml_document doc;
    doc.load_file(config.c_str());
    
    pugi::xml_node jawnode = doc.child("root").find_child_by_attribute("Actor", "name", "Jaw");
    
    if (jawnode.empty()) {
        //if there is an error in node initialization
        std::cout << "Can't find Bond actor node..." << std::endl;
        return;
    }
    //  std::cout << "start preparing frames" << std::endl;
    prepareFrameInfo(jawnode);
    // std::cout << "Finish preparing frames" << std::endl;
    Load(t, sf::Vector2i(0,0), sf::Vector2i(32, 64));

    type = VisibleGameObject::JAWS;
    alive = true;
    lives=12;
}

void Jaw::attack(Actor& actor){
    if (actor.type==VisibleGameObject::BOND &&closeContact(actor)) {
        Actor::attack();
    }
}

void Jaw::Update(float elapsedTime) {
    Actor::Update(elapsedTime);

        SetPosition(GetPosition().x, 480);
        standStill();
     if (rightpressed) {
            rightRun();
        } else if (leftpressed) {
            leftRun();
        } else if (isCurAnim("run")) {
            standStill();
        }
   // checkForBond();
    if (hasSeenBond)
    {
        SetPosition(bondLoc.x + 32, bondLoc.y);
        std::cout << "Jaws Location: " << GetPosition().x << "," << GetPosition().y << std::endl;
    }
    //establish movement
//     if (isAlive())
//        {
//        patrol();
//        }   
}

void Jaw::checkForBond(){
    if (GetPosition().x - bondLoc.x >= -400 && GetPosition().x - bondLoc.x <= 400)
    {
        hasSeenBond = true;
    }
}

void Jaw::die()
{
    lives--;
    if (lives <= 0)
    {
        Actor::die();
    }
    else
    {
        animReq("hurt", false);
    }
}

void Jaw::setBoundary(float left, float up, float right, float lower)
{
    lowerright = sf::Vector2i(right, lower);
    upperleft = sf::Vector2i(left, up);
}

void Jaw::setBondLocation(sf::Vector2f loc)
{
    //bondLoc = sf::Vector2i(loc.x, loc.y);
    //std::cout << "bond location is: " << bondLoc.x << "," << bondLoc.y << std::endl;
}

bool Jaw::lowCollide() {
    return GetPosition().y + 64 >= lowerright.y;
}