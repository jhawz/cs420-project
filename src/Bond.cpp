#include <SFML/Window/Keyboard.hpp>

#include "Bond.h"

Bond::Bond(std::string config, std::string texture) : Actor::Actor() {

    int lives = 3;

    pugi::xml_document doc;
    doc.load_file(config.c_str());

    pugi::xml_node bondnode = doc.child("root").find_child_by_attribute("Actor", "name", "Bond");

    if (bondnode.empty()) {
        //if there is an error in node initialization
        std::cout << "Can't find Bond actor node..." << std::endl;
        return;
    }
    prepareFrameInfo(bondnode);
    Load(texture);
    jumping = false;
    sf::Image *img = new sf::Image();
    if (!img->loadFromFile(texture)) {
        return;
    }
    setOriginalImg(*img);
    type = 1;
}
Bond::Bond(std::string config, sf::Texture& t) : Actor::Actor() {
    int lives = 3;
    
    pugi::xml_document doc;
    doc.load_file(config.c_str());
    
      pugi::xml_node bondnode = doc.child("root").find_child_by_attribute("Actor", "name", "Bond");

    if (bondnode.empty()) {
        //if there is an error in node initialization
        std::cout << "Can't find Bond actor node..." << std::endl;
        return;
    }
      
       prepareFrameInfo(bondnode);
       Load(t, sf::Vector2i(0, 0), sf::Vector2i(32, 64));
       type = 1;
}
void Bond::jump() {
    if (jumping) {
        return;
    }
    animReq("jump_prepare", false);
    vy = -9.99;
    ay = 1.00;
    jumping = true;
    animReq("jump_up", false);
}

sf::IntRect Bond::getBoundary() {
    return sf::IntRect(upperleft.x, upperleft.y, lowerright.x, lowerright.y);
}

void Bond::setBoundary(float left, float up, float right, float lower) {
    upperleft = sf::Vector2f(left, up);
    lowerright = sf::Vector2f(right, lower);
}

bool Bond::lowCollide() {
    return GetPosition().y + 64 >= lowerright.y;
}

bool Bond::rightCollide() {
    return GetPosition().x + 16 >= lowerright.x;
}

bool Bond::leftCollide() {
    //  std::cout << "Bond's Position: " << GetPosition().x << std::endl;
    return GetPosition().x - 16 <= upperleft.x;
}

bool Bond::topCollide() {
    return GetPosition().y <= upperleft.y;
}

void Bond::Update(float elapsedTime) {

    //Input
    input();
    //Main update call
    Actor::Update(elapsedTime);
    
    //Animation related call
    if (topCollide())
    {
       // SetPosition(GetPosition().x, upperleft.y);
        vy = 0;
    }
    if (!lowCollide()) {
        if (ay == 0) {
            ay = 2;
            jumping = true;
            animReq("jump_fall", false);
        } else if (vy>-6 && vy < 6) {
            animReq("jump_float", false);
        } else if (vy > 6) {
            animReq("jump_fall", false);
        }
        if (rightpressed && !rightCollide()) {
            Actor::rightMove();
        } else if (leftpressed && !leftCollide()) {
            Actor::leftMove();
        }
    } else if (vy > 0) {
        jumping = false;
        SetPosition(GetPosition().x, lowerright.y - 64);
        if (rightpressed && !rightCollide()) {
            rightRun();
        } else if (leftpressed && !leftCollide()) {
            leftRun();
        } else {
            standStill();
        }
    } else if (!jumping) {
        jumpDelay--;
        if (rightpressed && !rightCollide()) {
            rightRun();
        } else if (leftpressed && !leftCollide()) {
            leftRun();
        } else if (isCurAnim("run")) {
            standStill();
        }
    }
    if (rightCollide())
    {
        vx = 0;
    }
}

void Bond::input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        setLeftPress(true);
    } else {
        setLeftPress(false);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        setRightPress(true);
    } else {
        setRightPress(false);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (jumpDelay <= 0)
        {
            jump();
            jumpDelay = 10;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        straightShoot();
    }
}

void Bond::crouchStill() {
    if (!alive) {
        return;
    }
    animReq("crouch", false);
}

void Bond::upshoot() {
    if (!alive)return;
    if (shootlocked)return;

    animReq("up_shoot", shootlocked);
    shootlocked = true;
    clock.restart();
}

void Bond::downshoot() {
    if (!alive)return;
    if (shootlocked)return;

    animReq("down_shoot", shootlocked);
    shootlocked = true;
    clock.restart();
}

void Bond::crouchshoot() {
    if (!alive)return;
    if (shootlocked)return;

    animReq("crouch_shoot", shootlocked);
    shootlocked = true;
    clock.restart();
}

void Bond::leftRun() {
    if (lowCollide()) {
        Actor::leftRun();
    }
}

void Bond::rightRun() {
    if (lowCollide()) {
        Actor::rightRun();
    }
}

void Bond::standStill() {
    if (lowCollide()) {
        Actor::standStill();
    }
}

void Bond::straightShoot() {
    if (lowCollide()) {
        Actor::attack();
    }
}