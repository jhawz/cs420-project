#include "Level.h"
void Level::loadLevel(int levelVal) {
    loadSpecifiedLevel("data/Level" + std::to_string(levelVal) + ".txt", (levelVal / 5) + 1);
}
void Level::loadSpecifiedLevel(std::string fileName, int backgroundVal) {
    MapLoader* m = new MapLoader();
    m->loadMap(fileName);
    setBackGround(m->getBackground(backgroundVal));
    std::cout << "Beginning to load level" << std::endl;
    levelTiles.loadFromFile("textures/TiledEight32New.png");
    enemySheet.loadFromFile("textures/enemy.png");
    bondSheet.loadFromFile("textures/JB.png");
    tileCodeList = m->getTileCodes(); 
    std::vector<int> firstIDs = m->getFirstIDs();
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
            
            if (isExitTile(std::stoi(tileCodeList[x])))
            {
                tileExitList.push_back(x % tilesPerRow + ((x / tilesPerRow) *
                        tilesPerRow));
            }
            }
            else if (tileCode == 286) //have to forgive the constant, = Jaws
            {
                std::cout << "Starting Jaws build" << std::endl;
                Jaw* j = buildAJaw(enemySheet, tileCode - firstIDs[1], x);
                jaw = j;
                std::cout << "built jaws" << std::endl;
            }
            else if (isEnemy(tileCode, firstIDs))
            {
                  Enemy* e = buildAnEnemy(enemySheet, 
                          tileCode - firstIDs[1], //fix tilecode bias from TMX
                          x);
                  enemyList.push_back(e);
            }
            else if (isBond(tileCode, firstIDs))
            {
                Bond* b = buildABond(bondSheet,
                        tileCode - firstIDs[2], //fix tilecode bias from TMX
                        x);
                bond = b;
            }
            else if (isPowerup(tileCode, firstIDs))
            {
                Powerup* p = buildAPowerup(bondSheet, 
                        tileCode - firstIDs[2], //fix tilecode bias from TMX
                        x);
                powerupList.push_back(p);
                p->setName("Powerup");
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

bool Level::isBond(int objectCode, std::vector<int>& mapIDs) {
    return (objectCode >= mapIDs[2] && objectCode < mapIDs[3]);
}
bool Level::isPowerup(int objectCode, std::vector<int>& mapIDs) {
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
    
    return newTile;
    
}
Enemy* Level::buildAnEnemy(sf::Texture& sheet, int positionInFrames,
        int mapPositionInFrames) {
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
            enemyType = "MachineGun";
            fireRate = 0.35;
            break;
        case 30:
            enemyType = "Pistol";
            fireRate = 2.0;
            break;
        case 40:
            enemyType  = "Smg";
            fireRate = 0.5;
            break;
        case 50:
            enemyType = "MachineGun";
            fireRate = 0.35;
            break;
        case 60:
            enemyType = "Jaw";
            fireRate = 4.0;
            break;
        default:
            enemyType = "MachineGun";
            fireRate = 0.35;
    }
    
    Enemy* e = new Enemy("actors.xml", sheet, enemyType, fireRate);
    
    e->SetPosition((mapPositionInFrames % tilesPerRow) * tileWidth,
            ((mapPositionInFrames / tilesPerRow) * tileHeight) - tileHeight);
    e->setBoundary(0, 0, 700, 3200);
    e->setOrigPos(sf::Vector2f(e->GetPosition().x, e->GetPosition().y));
    return e;
}

Bond* Level::buildABond(sf::Texture& sheet, int positionInFrames, 
        int mapPositionInFrames) {
    Bond* b = new Bond("actors.xml", sheet);
    b->SetPosition((mapPositionInFrames % tilesPerRow) * tileWidth,
            ((mapPositionInFrames / tilesPerRow) * tileHeight) - tileHeight);
    b->setBoundary(0, 0, 700, 3200);
    bondStartLoc = sf::Vector2f(b->GetPosition().x, b->GetPosition().y);
    
    return b;
}

Powerup* Level::buildAPowerup(sf::Texture& sheet, int positionInFrames,
        int mapPositionInFrames) {
    Powerup* p = new Powerup("actors.xml", sheet, positionInFrames);
    p->SetPosition((mapPositionInFrames % tilesPerRow) * tileWidth,
            ((mapPositionInFrames / tilesPerRow) * tileHeight) - tileHeight);
    
    return p;
}

Jaw* Level::buildAJaw(sf::Texture& sheet, int positionInFrames,
        int mapPositionInFrames)
{
    std::cout << "building jaws" << std::endl;
    Jaw* j = new Jaw("actors.xml", sheet);
    std::cout << "in buildAJaw: Jaw built" << std::endl;
    j->SetPosition((mapPositionInFrames % tilesPerRow) * tileWidth,
            ((mapPositionInFrames / tilesPerRow) * tileHeight) - tileHeight);
    j->setBoundary(0, 0, 700, 3200);
    j->setOrigPos(sf::Vector2f(j->GetPosition().x, j->GetPosition().y));
    return j;
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

Bond* Level::getBond() {
    return bond;
}

std::vector<int> Level::getExitCodes()
{
    return tileExitList;
}

bool Level::isExitTile(int mapPositionInFrames)
{
        if (mapPositionInFrames == 175 ||
            mapPositionInFrames == 176 ||
            mapPositionInFrames == 190 ||
            mapPositionInFrames == 191)
        {
            return true;
        }
        return false;
}

Jaw* Level::getJaws()
{
    return jaw;
}