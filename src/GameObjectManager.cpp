#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"

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
    float timeDelta = clock.restart().asSeconds();

    while (itr != gameObjects.end()) {
        itr->second->Update(timeDelta);
        std::cout<<itr->first<<std::endl;
        itr++;
    }


}
