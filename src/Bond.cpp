#include <SFML/Window/Keyboard.hpp>

#include "Bond.h"

Bond::Bond(std::string config, std::string texture) : Actor::Actor() {
    pugi::xml_document doc;
    doc.load_file(config.c_str());

    pugi::xml_node bondnode = doc.child("root").find_child_by_attribute("Actor", "name", "Bond");

    if (bondnode.empty()) {
        //if there is an error in node initialization
        std::cout << "Can't find Bond actor node..." << std::endl;
        return;
    }
    std::cout << "start preparing frames" << std::endl;
    prepareFrameInfo(bondnode);
    std::cout << "Finish preparing frames" << std::endl;
    Load(texture);
    jumping = false;
    sf::Image *img = new sf::Image();
    if (!img->loadFromFile(texture)) {
        return;
    }
    setOriginalImg(*img);
    type = 1;
}

void Bond::jump() {
    if (jumping) {
        return;
    }
    animReq("jump_prepare", false);
    vy = -9.99;
    ay = 0.5;
    jumping = true;
    animReq("jump_up", false);
}

sf::IntRect Bond::getBoundary(){
    return sf::IntRect(upperleft.x, upperleft.y, lowerright.x, lowerright.y);
}

void Bond::setBoundary(float left, float up, float right, float lower) {
    upperleft = sf::Vector2f(left, up);
    lowerright = sf::Vector2f(right, lower);
}

bool Bond::lowCollide() {
    return GetPosition().y + 64 >= lowerright.y;
}

void Bond::Update(float elapsedTime) {

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
        jump();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        straightShoot();
    }

    Actor::Update(elapsedTime);
    
    if (!lowCollide()) {
        if (ay == 0) {
            ay = 2;
            jumping = true;
            animReq("jump_fall", false);
            std::cout << "Falling" << std::endl;
        } else if (vy>-6 && vy < 6) {
            animReq("jump_float", false);
        } else if (vy > 6) {
            animReq("jump_fall", false);
        }
    } else if (vy > 0) {
        jumping = false;
        SetPosition(GetPosition().x, lowerright.y - 64);
        if (rightpressed) {
            rightRun();
        } else if (leftpressed) {
            leftRun();
        } else {
            standStill();
        }
    } else if (!jumping) {
        if (rightpressed) {
            rightRun();
        } else if (leftpressed) {
            leftRun();
        } else if (isCurAnim("run")) {
            standStill();
        }
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

   
