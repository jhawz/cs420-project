#include <SFML/Window/Keyboard.hpp>

#include "Bond.h"

Bond::Bond(std::string config, std::string texture) : Actor::Actor() {
    objectType="Bond";
    pugi::xml_document doc;
    doc.load_file(config.c_str());
    
    pugi::xml_node bondnode = doc.child("root").find_child_by_attribute("Actor", "name", "Bond");
    
    if (bondnode.empty()) {
        //if there is an error in node initialization
        std::cout << "Can't find Bond actor node..." << std::endl;
        return;
    }
    //  std::cout << "start preparing frames" << std::endl;
    prepareFrameInfo(bondnode);
    // std::cout << "Finish preparing frames" << std::endl;
    Load(texture);
    jumping = false;
    sf::Image *img = new sf::Image();
    if (!img->loadFromFile(texture)) {
        return;
    }
    setOriginalImg(*img);
    type = 1;
    state=BOND;
    transformDuration=sf::seconds(1);
}

void Bond::jump() {
    switch (state) {
        case BOND:
            if (jumping) {
                return;
            }
            animReq("jump_prepare", false);
            vy = -9.99;
            ay = 0.5;
            jumping = true;
            animReq("jump_up", false);
            break;
        case RAMBO:
            animReq("Rjump", false);
            break;
        default:
            break;
    }
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

bool Bond::rightCollide() {
    return GetPosition().x + 32 >= lowerright.x;
}

bool Bond::leftCollide() {
    return GetPosition().x - 32 <= upperleft.x;
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
    
    if (isCurAnim("transform")) {
        if (transformClock.getElapsedTime()>=transformDuration) {
            standStill();
        }
    }
    
    if (!lowCollide()&&state==BOND) {
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
        if (rightpressed && !rightCollide()) {
            rightRun();
        } else if (leftpressed && !leftCollide()) {
            leftRun();
        } else if (isCurAnim("run")||isCurAnim("Rrun")) {
            standStill();
        }
        //   std::cout << "LEFT BOUNDARY: " << upperleft.x << "RIGHT BOUNDARY: " << lowerright.x << std::endl;
    }
}

void Bond::crouchStill() {
    if (state==RAMBO) {
        return;
    }
    if (!alive) {
        return;
    }
    animReq("crouch", false);
}

void Bond::upshoot() {
    if (!alive)return;
    if (shootlocked)return;
    
    switch (state) {
        case BOND:
            animReq("up_shoot", shootlocked);
            shootlocked = true;
            clock.restart();
            break;
        case RAMBO:
            animReq("Rup_shoot", false);
            break;
        default:
            break;
    }
}

void Bond::downshoot() {
    if (!alive)return;
    if (shootlocked)return;
    
    switch (state) {
        case BOND:
            animReq("down_shoot", shootlocked);
            shootlocked = true;
            clock.restart();
            break;
        case RAMBO:
            animReq("Rdown_shoot", false);
            break;
        default:
            break;
    }
}

void Bond::crouchshoot() {
    if (!alive)return;
    if (shootlocked)return;
    if (state==RAMBO) {
        return;
    }
    
    animReq("crouch_shoot", shootlocked);
    shootlocked = true;
    clock.restart();
}

void Bond::leftRun() {
    if (lowCollide()) {
        switch (state) {
            case BOND:
                Actor::leftRun();
                break;
            case RAMBO:
                Actor::leftRun("Rrun");
                break;
            default:
                break;
        }
    }
}

void Bond::rightRun() {
    if (lowCollide()) {
        switch (state) {
            case BOND:
                Actor::rightRun();
                break;
            case RAMBO:
                Actor::rightRun("Rrun");
                break;
            default:
                break;
        }
    }
}

void Bond::standStill() {
    if (lowCollide()) {
        switch (state) {
            case BOND:
                Actor::standStill();
                break;
            case RAMBO:
                Actor::standStill("Rstand");
                break;
            default:
                break;
        }
    }
}

void Bond::straightShoot() {
    if (lowCollide()) {
        switch (state) {
            case BOND:
                Actor::attack();
                break;
            case RAMBO:
                Actor::attack("Rstraight_shoot");
                break;
            default:
                break;
        }
    }
}

void Bond::transform(){
    switch (state) {
        case BOND:
            state=RAMBO;
            break;
        case RAMBO:
            state=BOND;
            break;
        default:
            break;
    }
    animReq("transform", false);
    transformClock.restart();
}