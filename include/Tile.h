/* 
 * File:   Tile.h
 * Author: moth
 *
 * Created on November 9, 2014, 2:32 PM
 */

#ifndef TILE_H
#define	TILE_H

#include <SFML/Graphics.hpp>
#include "VisibleGameObject.h"

class Tile :public VisibleGameObject
{
    public:
    Tile()
    {
        
    };
    void buildTile(int tileCode, sf::Texture& img, 
           sf::Vector2i textPos, sf::Vector2i textRect);
    
    ~Tile()
    {
        
    };
    
    private:
        int tileCode;
        
};


#endif	/* TILE_H */

