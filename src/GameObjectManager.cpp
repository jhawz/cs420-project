#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"
#include <iostream>
#include "Actor.h"
#include "Bond.h"
#include "Enemy.h"
#include "Level.h"

GameObjectManager::GameObjectManager() {
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
        itr->second->Draw(renderWindow);
        itr++;
    }
}

void GameObjectManager::UpdateAll() {
    std::map<std::string, VisibleGameObject*>::const_iterator itr = gameObjects.begin();
    float timeDelta = clock.restart().asSeconds() * 25;

    while (itr != gameObjects.end()) {
        if (itr->second->type > 0) {
            itr->second->Update(timeDelta);
            checkForCollision(itr->second);
          //  keepOnMap(itr->second);
        }
        itr++;
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

void GameObjectManager::checkForCollision(VisibleGameObject* obj) {
    //if both mod values are 0, then the object is perfectly centered in the
    //grid position. Can't be colliding (unless it's completely inside a 
    //tile, which this loop should prevent...)  
    int newTop = 0;
    int newLeft = 32;
    int newRight = 3200;
    int newBottom = 700;

    int xVal = ((int) obj->GetPosition().x) / 32;
    int yVal = ((int) obj->GetPosition().y) / 32;
    int posToFrame = xVal + ((yVal) * 100);
    //check directly left/right as well as 1 row below left/right since
    //bond is 64 pixels (2 tiles) high.)
    if (collidedWith(posToFrame - 1) || collidedWith(posToFrame + 100 - 1)) {
        newLeft = ((xVal + 1) * 32);
    }        //chances are we won't have a on left on right collision at the same time
        //so roll else if. Second collidedWith check for same reason as above.
    else if (collidedWith(posToFrame + 1) || collidedWith(posToFrame + 100 + 1)) {
        newRight = ((xVal) * 32);
    }
    //Check below
    if (collidedWith(posToFrame + (2 * 100))) {
        newBottom = (yVal + 2) * 32;
    } else {
        newBottom = (yVal + 4) * 32;
    }
    //Check above
    if (collidedWith(posToFrame - (2 * 100))) {
        newTop = (yVal - 2) * 32;
    }
    if (obj->type == 1) {
        static_cast<Bond*> (obj)->setBoundary(newLeft,
                newTop, newRight, newBottom);
    } else if (obj->type == 2) {
        static_cast<Enemy*> (obj)->setBoundary(newLeft,
                newTop, newRight, newBottom);
    }
    return;
}
//Checks for a collision between a specific character and the items in the
//Collision list.
//Called by checkForCollision.

bool GameObjectManager::collidedWith(int gridPos) {
    //Run binary search
    int low = 0;
    int high = collisionsList.size();
    int mid = 0;
    while (low < high) {
        //std::cout << "HIGH = " << high << " MID = " << mid << " LOW = " << low << std::endl;
        mid = ((low + high) / 2);
        if (collisionsList[mid] == gridPos) {
            //collided. 
            return true;
        } else if (collisionsList[mid] < gridPos) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    //check the entries directly before and after the last known mid val
    //to ensure that the collision code wasn't avoided by the division
    //(prevents the 'hopping' problem)
    if (collisionsList[mid - 1] == gridPos ||
            collisionsList[mid + 1] == gridPos) {
        return true;
    } //No collisions detected.
    return false;
}

void GameObjectManager::keepOnMap(VisibleGameObject* obj) {
    if (obj->GetPosition().x < 32)
        obj->SetPosition(32, obj->GetPosition().y);
    else if (obj->GetPosition().x > 3200 - 32)
        obj->SetPosition(3200 - 32, obj->GetPosition().y);

    if (obj->GetPosition().y < 0)
        obj->SetPosition(obj->GetPosition().x, 0);
    else if (obj->GetPosition().y > 600) {
        obj->SetPosition(obj->GetPosition().x, 600);
        static_cast<Actor*> (obj)->die();
    }
}

int GameObjectManager::getLevelCode() {
    return currentLevel;
}

void GameObjectManager::setCurLevel(Level* l) {
    curLevel = l;
}