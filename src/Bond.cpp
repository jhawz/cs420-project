#include <SFML/Window/Keyboard.hpp>

#include "Bond.h"
#include "ServiceLocator.h"

Bond::Bond(std::string config, std::string texture) : Actor::Actor() {

    setLives(3);

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
    type = VisibleGameObject::BOND;
    state = BOND;
    transformDuration = sf::seconds(1);
}

Bond::Bond(std::string config, sf::Texture& t) : Actor::Actor() {

    setLives(3);

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
    type = VisibleGameObject::BOND;
    state = BOND;
    transformDuration = sf::seconds(1);
}

void Bond::jump() {
    switch (state) {
        case BOND:
            if (jumping) {
                return;
            }
            animReq("jump_prepare", false);
            vy = -9.99;
            ay = 1.0;
            jumping = true;
            animReq("jump_up", false);
            break;
        case RAMBO:
            if (jumping) {
                return;
            }
            animReq("Rjump", false);
            vy = -13.99;
            ay = 1.0;
            jumping = true;
            break;
        default:
            break;
    }
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

void Bond::grabbedByJaws()
{
    animReq("disappear", false);
    grabbed = true;
    rightpressed = false;
    leftpressed = false;
    vy = 0;
    vx = 0;
    grabbedTime = transformClock.getElapsedTime().asMilliseconds();
}

void Bond::Update(float elapsedTime) {

    //Input
    input();
    //Main update call
    Actor::Update(elapsedTime);
    if (isCurAnim("transform")) {
        if (transformClock.getElapsedTime() >= transformDuration) {
            standStill();
        }
    }

    if (grabbed && transformClock.getElapsedTime().asMilliseconds() >= grabbedTime + 800)
    {
        die();
        grabbed = false;
    }
    
    //Animation related call
    if (topCollide()) {
        // SetPosition(GetPosition().x, upperleft.y);
        vy = 0;
    }
    if (!lowCollide() && alive) {
        if (ay == 0) {
            ay = 2;
            jumping = true;
        }
        if (state == BOND) {
            animReq("jump_fall", false);
            if (vy>-6 && vy < 6) {
                animReq("jump_float", false);
            } else if (vy > 6) {
                animReq("jump_fall", false);
            }
        } else if (state == RAMBO) {
            animReq("Rjump", false);
        }
        if (rightpressed && !rightCollide()) {
            Actor::rightMove();
        } else if (leftpressed && !leftCollide()) {
            Actor::leftMove();
        }

    } else if (!lowCollide() && !alive) {
        if (ay == 0)
            ay = 2;
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
        } else if (isCurAnim("run") || isCurAnim("Rrun")) {
            standStill();
        }
    }
    if (rightCollide()) {
        vx = 0;
    }
}

void Bond::input() {
    if (alive && !grabbed) {
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
            if (jumpDelay <= 0) {
                jump();
                jumpDelay = 10;
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (state == BOND) {
                if (shotClock.getElapsedTime().asSeconds() >= 1.0 &&
                        jumping != true) {
                    standStill();
                    straightShoot();
                    setFiring(true);
                    ServiceLocator::GetAudio()->PlaySound("sounds/pistol.ogg");
                    shotClock.restart();
                } else if (shotClock.getElapsedTime().asSeconds() >= 1.0 &&
                        jumping == true) {
                    jumpShoot();
                    setFiring(true);
                    ServiceLocator::GetAudio()->PlaySound("sounds/pistol.ogg");
                    shotClock.restart();
                }
            } else if (state == RAMBO) {
                if (shotClock.getElapsedTime().asSeconds() >= .2 &&
                        jumping != true) {
                    standStill();
                    straightShoot();
                    setFiring(true);
                    ServiceLocator::GetAudio()->PlaySound("sounds/gun.wav");
                    shotClock.restart();
                } else if (shotClock.getElapsedTime().asSeconds() >= .2 &&
                        jumping == true) {
                    jumpShoot();
                    setFiring(true);
                    ServiceLocator::GetAudio()->PlaySound("sounds/gun.wav");
                    shotClock.restart();
                }
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            transform();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
            godMode = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
            godMode = false;
        }
    }
}

void Bond::crouchStill() {
    if (state == RAMBO) {
        return;
    }
    if (!alive) {
        return;
    }
    animReq("crouch", false);
}

void Bond::jumpShoot() {
    if (!alive || shootlocked) return;
    switch (state) {
        case BOND:
            animReq("jump_shoot", shootlocked);
            shootlocked = true;
            clock.restart();
            break;
        case RAMBO:
            break;
    }
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
    if (state == RAMBO) {
        return;
    }

    animReq("crouch_shoot", shootlocked);
    shootlocked = true;
    clock.restart();
}

void Bond::leftRun() {
    if (lowCollide()) {
        setFacingLeft();
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
        setFacingRight();
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

void Bond::transform() {
    switch (state) {
        case BOND:
            state = RAMBO;
            ServiceLocator::GetAudio()->PlaySong("music/Rambo_Theme.ogg", true);
            break;
        case RAMBO:
            state = BOND;
            ServiceLocator::GetAudio()->PlaySong("music/bond_theme.ogg", true);
            break;
        default:
            break;
    }
    animReq("transform", false);
    transformClock.restart();
}

void Bond::die() {
    if (alive)
    {
    switch (state) {
        case BOND:
            Actor::die();
            lives--;
            break;
        case RAMBO:
            transform();
            break;
        default:
            break;
    }
    jumping = false;
    rightpressed = false;
    leftpressed = false;
}
}

int Bond::getState() {
    return state;
}

int Bond::getRamboState() {
    return RAMBO;
}

void Bond::setBondState()
{
    state = BOND;
}