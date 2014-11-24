/* 
 * File:   Hud.h
 * Author: jch
 *
 * Created on November 23, 2014, 12:42 AM
 */

#include "stdafx.h"

#ifndef HUD_H
#define	HUD_H

class Hud : public sf::View {
public:
    Hud();
    sf::Texture texture;
    sf::Sprite head_1;
    sf::Sprite head_2;
    sf::Sprite head_3;

private:


};

#endif	/* HUD_H */

