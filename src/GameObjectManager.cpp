#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"
#include <iostream>
#include "Actor.h"
#include "Bond.h"
#include "Enemy.h"

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
        itr->second->Update(timeDelta);
        checkForCollision(itr->second);
        itr++;
    }
}
    void GameObjectManager::setCollisionList(std::vector<int> v)
    {
        collisionsList = v;
    }
    
    void GameObjectManager::checkForCollision(VisibleGameObject* obj){
        //mod will cause the GameObjectManager to skip tiles.
        
        if (((int) obj->GetPosition().x) % 32 != 0)
        {
            
        }
        
        if (((int) obj->GetPosition().y) % 32 != 0)
        {
            int xVal = ((int) obj->GetPosition().x) / 32;
            int yVal = ((int) obj->GetPosition().y) / 32;
            int posToFrame = xVal + ((yVal + 2) * 100);
            
            //Run binary search
            int low = 0;
            int high = collisionsList.size();
            int mid = 0;
            while (low < high)
            {
                mid = ((low + high) / 2);
                if (collisionsList[mid] == posToFrame)
                {
                    //collided. 
                    if (static_cast<Actor*>(obj)->type == 1)
                    {
                        static_cast<Bond*>(obj)->setBoundary(0, 0, 3200, (yVal + 2) * 32);
                    }
                    else
                    {
                        static_cast<Enemy*>(obj)->setBoundary(0, 0, 3200, (yVal + 2) * 32);
                    }
                    
                    obj->SetPosition(obj->GetPosition().x, yVal * 32);
                    return;
                }
                else if (collisionsList[mid] < posToFrame)
                {
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
               // std::cout << "LOW = " << low << " MID = " << mid << " HIGH = " <<  high << std::endl;
            }
            if (collisionsList[mid - 1] == posToFrame || collisionsList[mid + 1] == posToFrame)
            {
                    if (static_cast<Actor*>(obj)->type == 1)
                    {
                        static_cast<Bond*>(obj)->setBoundary(0, 0, 3200, (yVal + 2) * 32);
                    }
                    else
                    {
                        static_cast<Enemy*>(obj)->setBoundary(0, 0, 3200, (yVal + 2) * 32);
                    }
                    
                obj->SetPosition(obj->GetPosition().x, yVal * 32);
                return;
            }
        }
    }