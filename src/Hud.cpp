/* 
 * File:   Hud.cpp
 * Author: jch
 * 
 * Created on November 23, 2014, 12:42 AM
 */

#include "Hud.h"

Hud::Hud() {
    std::vector<sf::Sprite> heads;
    texture.loadFromFile("textures/bond_head.png");
    head_1.setTexture(texture);
    head_2.setTexture(texture);
    head_3.setTexture(texture);
    head_1.setPosition(10, 10);
    head_2.setPosition(60, 10);
    head_3.setPosition(110, 10);
}