#include "Level.h"

void Level::loadLevel(int levelVal) {
    loadSpecifiedLevel("data/Level" + std::to_string(levelVal) + ".txt");
}

void Level::loadSpecifiedLevel(std::string fileName) {
    MapLoader* m = new MapLoader();
    m->loadMap(fileName);
    setBackGround(m->getBackground(1));
    levelTiles.loadFromFile("textures/TiledEight32New.png");
    enemySheet.loadFromFile("textures/enemy.png");
    bondSheet.loadFromFile("textures/JB.png");
    tileCodeList = m->getTileCodes(); 
    std::vector<int> firstIDs = m->getFirstIDs();
    std::cout << "ID Codes as follows: " << firstIDs[0] << " " << firstIDs[1] << " " << firstIDs[2] << std::endl;
    for (int x = 0; x < tileCodeList.size(); x++) {       
        if (isRealObjectOnMap(std::stoi(tileCodeList[x]))) {
            int tileCode = std::stoi(tileCodeList[x]);
            
            if (isTile(tileCode, firstIDs))
            {
            Tile* newTile = buildATile(
                    levelTiles, 
                    tileCode - firstIDs[0], //fix tilecode bias from TMX
                    x);

            tileList.push_back(newTile);
            tileColList.push_back(x % tilesPerRow + ((x / tilesPerRow) *
            tilesPerRow));
            }
            else if (isEnemy(tileCode, firstIDs))
            {
                  Enemy* e = buildAnEnemy(enemySheet, 
                          tileCode - firstIDs[1], 
                          x);
                  enemyList.push_back(e);
                  
            }
            else if (isBond(tileCode, firstIDs))
            {
                Bond* b = buildABond(bondSheet,
                        tileCode - firstIDs[2],
                        x);
                bond = b;
            }
            else if (isPowerup(tileCode, firstIDs))
            {
                Powerup* p = buildAPowerup(bondSheet, 
                        tileCode - firstIDs[2],
                        x);
                powerupList.push_back(p);
            }
        }
    }
    delete m;
}

bool Level::isRealObjectOnMap(int objectCode)
{
    return (objectCode > 0);
}

bool Level::isEnemy(int objectCode, std::vector<int>& mapIDs)
{
    return (objectCode >= mapIDs[1] && objectCode < mapIDs[2]);
}

bool Level::isTile(int objectCode, std::vector<int>& mapIDs)
{
    return (objectCode < mapIDs[1]);
}

bool Level::isBond(int objectCode, std::vector<int>& mapIDs)
{
    return (objectCode >= mapIDs[2] && objectCode < mapIDs[3]);
}

bool Level::isPowerup(int objectCode, std::vector<int>& mapIDs)
{
    return (objectCode >= mapIDs[3]);
}

Tile* Level::buildATile(sf::Texture& sheet, int positionInFrames, 
        int mapPositionInFrames){
    Tile* newTile = new Tile();
    sf::Vector2i tileDimensions(tileWidth, tileHeight);
    int tilesPerRowInSheet(((int) sheet.getSize().x) / tileWidth);
    
    sf::Vector2i tilePositionInSheet(
            (positionInFrames % tilesPerRowInSheet) * tileWidth, 
            (positionInFrames / tilesPerRowInSheet) * tileHeight);
    
    newTile->buildTile(positionInFrames, sheet, tilePositionInSheet,
            tileDimensions);
    
    newTile->SetPosition((mapPositionInFrames % tilesPerRow) * tileWidth, 
            (mapPositionInFrames / tilesPerRow) * tileHeight);
    
    checkIfExitTile(newTile, mapPositionInFrames);
    
    return newTile;
    
}

void Level::checkIfExitTile(Tile* t, int mapPositionInFrames)
{
    if (mapPositionInFrames == 175 ||
            mapPositionInFrames == 176 ||
            mapPositionInFrames == 190 ||
            mapPositionInFrames == 191)
    {
        t->setAsExit();
    }
}

Enemy* Level::buildAnEnemy(sf::Texture& sheet, int positionInFrames,
        int mapPositionInFrames)
{
    std::string enemyType;
    float fireRate;
    
    switch (positionInFrames)
    {
        case 0:
            enemyType = "Pistol";
            fireRate = 2.0;
            break;
        case 10:
            enemyType = "Smg";
            fireRate = 0.5;
            break;
        case 20:
            enemyType = "Machinegun";
            fireRate = 0.5;
            break;
        default:
            enemyType = "Jaw";
            fireRate = 4.0;
            break;
    }
    
    Enemy* e = new Enemy("actors.xml", sheet, enemyType, fireRate);
    
    e->SetPosition((mapPositionInFrames % tilesPerRow) * tileWidth,
            ((mapPositionInFrames / tilesPerRow) * tileHeight) - tileHeight);
    e->setBoundary(0, 0, 700, 3200);
    e->setOrigPos(sf::Vector2f(e->GetPosition().x, e->GetPosition().y));
    return e;
}

Bond* Level::buildABond(sf::Texture& sheet, int positionInFrames, 
        int mapPositionInFrames)
{
    Bond* b = new Bond("actors.xml", sheet);
    b->SetPosition((mapPositionInFrames % tilesPerRow) * tileWidth,
            ((mapPositionInFrames / tilesPerRow) * tileHeight) - tileHeight);
    b->setBoundary(0, 0, 700, 3200);
    
    return b;
}

Powerup* Level::buildAPowerup(sf::Texture& sheet, int positionInFrames,
        int mapPositionInFrames)
{
    Powerup* p = new Powerup("actors.xml", sheet, positionInFrames);
    p->SetPosition((mapPositionInFrames % tilesPerRow) * tileWidth,
            ((mapPositionInFrames / tilesPerRow) * tileHeight) - tileHeight);
    
    return p;
}

VisibleGameObject* Level::getBackground() {
    return backGround;
}

void Level::setBackGround(VisibleGameObject* obj) {
    backGround = obj;
}

std::vector<int> Level::getTileColList() {
    return tileColList;
}

std::vector<std::string> Level::getTileCodes() {
    return tileCodeList;
}

std::vector<Tile*>& Level::getTileList() {
    return tileList;
}

std::vector<Enemy*>& Level::getEnemyList() {
    return enemyList;
}

std::vector<Powerup*>& Level::getPowerupList() {
    return powerupList;
}

Bond* Level::getBond()
{
    return bond;
}