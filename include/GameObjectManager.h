#pragma once
#include "VisibleGameObject.h"
#include "Level.h"
#include "Bond.h"


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
        void checkForTileCollision(VisibleGameObject* obj);
        int getLevelCode();
        void setCurLevel(Level* l);
        Bond* b;
        int const tileWidth = 32;
        int const tileHeight = 32;
        void checkIfActorFired(VisibleGameObject* obj);
        void updateBondLocForEnemies(VisibleGameObject* obj);
        bool isReadyForNextLevel();
        void increLevel();
private:
	std::map<std::string, VisibleGameObject*> gameObjects;
        std::vector<int> collisionsList;
	sf::Clock clock;
        int currentLevel = 3;
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