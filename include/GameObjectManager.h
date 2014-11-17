#pragma once
#include "VisibleGameObject.h"
#include "Level.h"


class GameObjectManager
{
public:	
	GameObjectManager();
	~GameObjectManager();

	void Add(std::string name, VisibleGameObject* gameObject);
	void Remove(std::string name);
	int GetObjectCount() const;
	VisibleGameObject* Get(std::string name) const;
	void DrawAll(sf::RenderWindow& renderWindow);
	void UpdateAll();
        void setCollisionList(std::vector<int> v);
        void checkForCollision(VisibleGameObject* obj);
        void keepOnMap(VisibleGameObject* obj);
        int getLevelCode();
        void setCurLevel(Level* l);
private:
	std::map<std::string, VisibleGameObject*> gameObjects;
        std::vector<int> collisionsList;
	sf::Clock clock;
        int currentLevel = 1;
        Level * curLevel;
	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string,VisibleGameObject*> & p) const
		{
			delete p.second;
		}
	};
        bool collidedWith(int gridPos);
};