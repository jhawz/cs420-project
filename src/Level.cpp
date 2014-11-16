#include "Level.h"


void Level::loadLevel(int levelVal)
{
    switch (levelVal){
        
        case 1:
            loadSpecifiedLevel("data/Level1.txt");
            break;
        case 2:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 3:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 4:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 5:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 6:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 7:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 8:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 9:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 10:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 11:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 12:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 13:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 14:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 15:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 16:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 17:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 18:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 19:
            loadSpecifiedLevel("data/Level2.txt");
            break;
        case 20:
            loadSpecifiedLevel("data/Level2.txt");
            break;
    }
}

void Level::loadSpecifiedLevel(std::string fileName)
{
    MapLoader* m = new MapLoader();
    m->loadMap(fileName);
    setBackGround(m->getBackground(1));
    levelTiles.loadFromFile("textures/TiledEight32New.png");
    tileCodeList = m->getTileCodes();
  //  std::cout << "Prepping for tile building loop" << std::endl;
    for (int x = 0; x < tileCodeList.size(); x++)
    {
        if (std::stoi(tileCodeList[x]) > 0)
        {
            Tile* newTile = new Tile();
            newTile->buildTile(std::stoi(tileCodeList[x]), levelTiles, 
                    sf::Vector2i(((std::stoi(tileCodeList[x]) - 1) % 15) * 32,
                    ((std::stoi(tileCodeList[x]) - 1) / 15) * 32),
                    sf::Vector2i(32, 32));
            newTile->SetPosition((x % 100) * 32, (x / 100) * 32);
            tileList.push_back(newTile);
            tileColList.push_back(x % 100 + ((x / 100) * 100));
        }
    }
    
   // std::cout << "tile building done. exiting after deletion..." << std::endl;
    
    delete m;
    
}

VisibleGameObject* Level::getBackground(){
    return backGround;
}

void Level::setBackGround(VisibleGameObject* obj)
{
    backGround = obj;
}

std::vector<int> Level::getTileColList()
{
    return tileColList;
}

std::vector<std::string> Level::getTileCodes()
{
    return tileCodeList;
}

std::vector<Tile*> Level::getTileList()
{
    return tileList;
}