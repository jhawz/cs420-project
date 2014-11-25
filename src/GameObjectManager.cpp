#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include "Actor.h"
#include "Bond.h"
#include "Enemy.h"
#include "Level.h"
#include "Bullet.h"
#include "Jaw.h"

GameObjectManager::GameObjectManager() {
    currentLevel = 1;
}

GameObjectManager::~GameObjectManager() {
    std::for_each(gameObjects.begin(), gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject) {
    gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::Remove(std::string name) {
    std::map<std::string, VisibleGameObject*>::iterator results = gameObjects.find(name);
    if (results != gameObjects.end()) {
        delete results->second;
        gameObjects.erase(results);
    }
}

void GameObjectManager::RemoveAll() {
    gameObjects.clear();
    delete curLevel;
}

VisibleGameObject* GameObjectManager::Get(std::string name) const {
    std::map<std::string, VisibleGameObject*>::const_iterator results = gameObjects.find(name);
    if (results == gameObjects.end())
        return NULL;
    return results->second;
}

int GameObjectManager::GetObjectCount() const {
    return gameObjects.size();
}

void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow) {
    std::map<std::string, VisibleGameObject*>::const_iterator itr = gameObjects.begin();
    while (itr != gameObjects.end()) {
        if (itr->second->type == VisibleGameObject::MARTINI
                && !itr->second->IsAlive()) {

        } else {

        }
        itr->second->Draw(renderWindow);
        itr++;
    }
}

void GameObjectManager::UpdateAll() {
    std::map<std::string, VisibleGameObject*>::const_iterator itr = gameObjects.begin();
    std::map<std::string, VisibleGameObject*>::const_iterator itr2 = gameObjects.begin();
    float timeDelta = clock.restart().asSeconds() * 25;

    while (itr != gameObjects.end()) {
        if (itr->second->type != VisibleGameObject::TILE) {
            itr->second->Update(timeDelta);
            checkForTileCollision(itr->second);
            checkIfActorFired(itr->second);
        }

        if (itr->second->type == VisibleGameObject::BOND) {
            bondCollisions(itr->second);
        } else if (itr->second->type == VisibleGameObject::ENEMY ||
                itr->second->type == VisibleGameObject::JAWS) {
            enemyCollisions(itr->second);
        }//check for martini collision for transformation
        else if (itr->second->type == VisibleGameObject::MARTINI && itr->second->IsAlive()) {
            itr2 = gameObjects.begin();
            while (itr2 != gameObjects.end()) {
                if (itr2->second->type == VisibleGameObject::BOND) {
                    if (itr2->second->closeContact(itr->second)
                            &&
                            static_cast<Bond*> (itr2->second)->getState()
                            != static_cast<Bond*> (itr2->second)->getRamboState()) {
                        static_cast<Powerup*> (itr->second)->disappear();
                        itr->second->setNotAlive();
                        static_cast<Bond*> (itr2->second)->transform();
                    }
                }
                itr2++;
            }
        }
        //Bullet collision
        if (itr->second->type == VisibleGameObject::BULLET) {
            itr2 = gameObjects.begin();
            while (itr2 != gameObjects.end()) {
                bulletCollisions(itr->second, itr2->second);
                itr2++;
            }
            if (itr->second->getRemove())
                Remove(itr->second->getName());
        }
        itr++;
    }
}

void GameObjectManager::bondCollisions(VisibleGameObject* obj1) {
    if (obj1->IsAlive()) {
        checkForExitCollision(obj1);
    } else if (!obj1->IsAlive() && static_cast<Bond*> (obj1)->getAnim()->isEnded()) {
        static_cast<Actor*> (obj1)->setAlive();
        static_cast<Bond*> (obj1)->setBoundary(0, 0, 700, 3200);
        obj1->SetPosition(32, 300);
        static_cast<Bond*> (obj1)->standStill();
    }

}

void GameObjectManager::enemyCollisions(VisibleGameObject* obj) {
    if (obj->type == VisibleGameObject::JAWS)
    {
        updateBondLocForEnemies(obj, true);
    }
    else
    {
        updateBondLocForEnemies(obj, false);
    }
}

void GameObjectManager::martiniCollisions(VisibleGameObject* obj1,
        VisibleGameObject* obj2) {

}

void GameObjectManager::bulletCollisions(VisibleGameObject* obj1,
        VisibleGameObject* obj2) {

    if (obj1->closeContact(obj2)
            && obj2->IsAlive()) {
        if (obj2->type == VisibleGameObject::BOND
                && static_cast<Bullet*> (obj1)->getOwner() !=
                VisibleGameObject::BOND) {
            static_cast<Bullet*> (obj1)->setRemove();
            if (!static_cast<Bond*> (obj2)->godMode) {
                static_cast<Bond*> (obj2)->die();
            }

        } else if (obj2->type == VisibleGameObject::ENEMY
                && static_cast<Bullet*> (obj1)->getOwner() !=
                VisibleGameObject::ENEMY) {
            static_cast<Bullet*> (obj1)->setRemove();
            static_cast<Enemy*> (obj2)->die();

        } else if (obj2->type == VisibleGameObject::JAWS
                && static_cast<Bullet*> (obj1)->getOwner() !=
                VisibleGameObject::JAWS) {
            static_cast<Bullet*> (obj1)->setRemove();
            static_cast<Jaw*>(obj2)->die();
        }

    }
}

//Sets up the internally stored list of integer values which are the
//x,y positions of tiles that objects can collide with converted into
//a single dimensional number. This conversion = xVal + (yVal * rowLength)

void GameObjectManager::setCollisionList(std::vector<int> v) {
    collisionsList = v;
}

//Causes character to react to tiles on map based upon what is contained
//within the collisionsList

void GameObjectManager::checkForTileCollision(VisibleGameObject* obj) {
    //if both mod values are 0, then the object is perfectly centered in the
    //grid position. Can't be colliding (unless it's completely inside a 
    //tile, which this loop should prevent...)  
    int newTop = 0;
    int newLeft = 0;
    int newRight = 3200;
    int newBottom = 700;

    int xVal = ((int) obj->GetPosition().x) / 32;
    int yVal = ((int) obj->GetPosition().y) / 32;
    int posToFrame = xVal + ((yVal) * 100);
    int returnCollisionValue = -1;
    //check directly left/right as well as 1 row below left/right since
    //bond is 64 pixels (2 tiles) high.)

    //check left collisions
    returnCollisionValue = collidedWith(posToFrame - 1);

    if (returnCollisionValue > -1) {
        newLeft = ((collisionsList[returnCollisionValue] % 100) * 32) + 33;
        // std::cout << "LEFT BOUND CHANGED TO: " << newLeft << std::endl;
    } else {
        returnCollisionValue = collidedWith(posToFrame + 100 - 1);
        if (returnCollisionValue > -1) {
            newLeft = ((collisionsList[returnCollisionValue] % 100) * 32) + 33;
            //    std::cout << "LEFT BOUND CHANGED TO: " << newLeft << std::endl;
        }
    }
    //check right collisions
    returnCollisionValue = collidedWith(posToFrame + 1);

    if (returnCollisionValue > -1) {
        newRight = ((collisionsList[returnCollisionValue] % 100) * 32) - 33;
        //   std::cout << "RIGHT (1st) BOUND CHANGED TO: " << newRight << std::endl;
    } else {
        returnCollisionValue = collidedWith(posToFrame + 100 + 1);
        if (returnCollisionValue > -1) {
            newRight = ((collisionsList[returnCollisionValue] % 100) * 32) - 33;
            //            std::cout << "RIGHT (2nd) BOUND CHANGED TO: " << newRight << std::endl;
        }
    }

    //Check below
    if (collidedWith(posToFrame + (2 * 100)) > -1) {
        newBottom = (yVal + 2) * 32;
    } else if (((int) obj->GetPosition().x) % 32 != 0 &&
            collidedWith(posToFrame + (2 * 100) + 1) > -1 &&
            collidedWith(posToFrame + (2 * 100) - 1) > -1) {
        newBottom = (yVal + 2) * 32;
    }
    //Check above
    if (collidedWith(posToFrame - (1 * 100)) > -1) {
        newTop = (yVal) * 32;
    } else if (collidedWith((posToFrame - (1 * 100)) + 1) > -1) {
        newTop = (yVal - 1) * 32;
    } else {
        newTop = 0;
    }
    if (obj->type == 1) {
        static_cast<Bond*> (obj)->setBoundary(newLeft,
                newTop, newRight, newBottom);
        if (obj->GetPosition().y >= 600) {

            static_cast<Bond*> (obj)->die();
        }
    } else if (obj->type == 2) {
        static_cast<Enemy*> (obj)->setBoundary(newLeft,
                newTop, newRight, newBottom);
        if (obj->GetPosition().y >= 600) {
            static_cast<Enemy*> (obj)->die();
        }
    } else if (obj->type == 4) {
        sf::Vector2i curBoundary = static_cast<Bullet*> (obj)->getBoundary();
        if (curBoundary.x > newLeft) {
            newLeft = curBoundary.x;
        }
        if (curBoundary.y < newRight) {
            newRight = curBoundary.y;
        }
        static_cast<Bullet*> (obj)->setBoundary(newLeft, newRight);
    }
    return;
}
//Checks for a collision between a specific character and the items in the
//Collision list.
//Called by checkForCollision.

void GameObjectManager::checkForExitCollision(VisibleGameObject* obj) {
    for (int i = 0; i < exitList.size(); i++) {
        sf::Vector2f obj2((exitList[i] % tilesPerRow) * tileWidth
                , (exitList[i] / tilesPerRow) * tileHeight);
        if (obj->closeContact(obj2)) {
            nextLevel = true;
        }
    }
}

void GameObjectManager::unsetReadyForNextLevel() {
    nextLevel = false;
}

//Returns the position of the tile the object collided with in a frame count
//Returns -1 if there was no collision

int GameObjectManager::collidedWith(int gridPos) {
    //Run binary search
    int low = 0;
    int high = collisionsList.size();
    int mid = 0;
    while (low < high) {
        //std::cout << "HIGH = " << high << " MID = " << mid << " LOW = " << low << std::endl;
        mid = ((low + high) / 2);
        if (collisionsList[mid] == gridPos) {
            //collided. 
            return mid;
        } else if (collisionsList[mid] < gridPos) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    //check the entries directly before and after the last known mid val
    //to ensure that the collision code wasn't avoided by the division
    //(prevents the 'hopping' problem)
    if (collisionsList[mid + 1] == gridPos) {
        return mid + 1;
    } else if (collisionsList[mid - 1] == gridPos) {
        return mid - 1;
    }
    //No collisions detected.
    return -1;
}

int GameObjectManager::getLevelCode() {
    return currentLevel;
}

void GameObjectManager::setCurLevel(Level* l) {
    curLevel = l;
}

void GameObjectManager::checkIfActorFired(VisibleGameObject* obj) {
    if (obj->getFiring() == true) {
        Bullet *bullet;
        if (obj->isFacingRight()) {
            bullet = new Bullet("actors.xml", "textures/JB.png", 0);
            bullet->SetPosition(obj->GetPosition().x - 36, obj->GetPosition().y);
            if (obj->GetPosition().x > 400)
                bullet->setBoundary(obj->GetPosition().x - 450,
                    obj->GetPosition().x + 450);
            else
                bullet->setBoundary(obj->GetPosition().x - 800,
                    obj->GetPosition().x + 800);
        } else {
            bullet = new Bullet("actors.xml", "textures/JB.png", 1);
            bullet->SetPosition(obj->GetPosition().x + 36, obj->GetPosition().y);
            if (obj->GetPosition().x > 400)
                bullet->setBoundary(obj->GetPosition().x - 450,
                    obj->GetPosition().x + 450);
            else
                bullet->setBoundary(obj->GetPosition().x - 800,
                    obj->GetPosition().x + 800);
        }
        std::string tmpName = "Bullet" + (std::to_string(clock.getElapsedTime().asSeconds()));
        bullet->setName(tmpName);
        this->Add(tmpName, bullet);
        bullet->setOwner(obj->type);
        obj->setFiring(false);
    }
}

void GameObjectManager::updateBondLocForEnemies(VisibleGameObject* obj, 
        bool isJaws) {
    if (isJaws)
    {
            static_cast<Jaw*> (obj)->setBondLocation(Get("Bond")->GetPosition());
    }
    else
    {
           static_cast<Enemy*> (obj)->setBondLocation(Get("Bond")->GetPosition()); 
    }

}

bool GameObjectManager::isReadyForNextLevel() {
    return nextLevel;
}

void GameObjectManager::increLevel() {
    currentLevel++;
}

void GameObjectManager::setExitList(std::vector<int> v) {
    exitList = v;
}
