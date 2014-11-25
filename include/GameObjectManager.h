#pragma once
#include "VisibleGameObject.h"
#include "Level.h"
#include "Bond.h"
#include "Jaw.h"


class GameObjectManager
{
public:	
	GameObjectManager();
	~GameObjectManager();

	void Add(std::string name, VisibleGameObject* gameObject);
	void Remove(std::string name);
        void RemoveAll();
	int GetObjectCount() const;
	VisibleGameObject* Get(std::string name) const;
	void DrawAll(sf::RenderWindow& renderWindow);
	void UpdateAll();
        void setCollisionList(std::vector<int> v);
        void setExitList(std::vector<int> v);
        void checkForTileCollision(VisibleGameObject* obj);
        void checkForExitCollision(VisibleGameObject* obj);
        int getLevelCode();
        void setCurLevel(Level* l);
        Bond* b;
        Jaw* j;
        int const tileWidth = 32;
        int const tileHeight = 32;
        int const tilesPerRow = 100;
        void checkIfActorFired(VisibleGameObject* obj);
        void updateBondLocForEnemies(VisibleGameObject* obj, bool isJaws);
        bool isReadyForNextLevel();
        void unsetReadyForNextLevel();
        void increLevel();
        void enemyCollisions(VisibleGameObject* obj);
        void martiniCollisions(VisibleGameObject* obj1, VisibleGameObject* obj2);
        void bondCollisions(VisibleGameObject* obj);
        void bulletCollisions(VisibleGameObject* obj1, VisibleGameObject* obj2);
        void resetLevelToOne();
private:
	std::map<std::string, VisibleGameObject*> gameObjects;
        std::vector<int> collisionsList;
        std::vector<int> exitList;
	sf::Clock clock;
        int currentLevel;
        Level * curLevel;
	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string,VisibleGameObject*> & p) const
		{
			delete p.second;
		}
	};
        int collidedWith(int gridPos);
        bool nextLevel = false;
};