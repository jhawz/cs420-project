#include "VisibleGameObject.h"
#include "Tile.h"

void Tile::buildTile(int tileVal, sf::Texture& img, sf::Vector2i textPos, sf::Vector2i textRect)
{

    tileCode = tileVal;
    Load(img, textPos, textRect);
}
