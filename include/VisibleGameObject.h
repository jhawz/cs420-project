#pragma once
#include "stdafx.h"
class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();
	
	virtual void Load(std::string filename);
        virtual void Load(sf::Texture& t, 
        sf::Vector2i textPos, sf::Vector2i textSize);
	virtual void Draw(sf::RenderWindow & window);
	virtual void Update(float elapsedTime);

	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition() const;
	virtual bool IsLoaded() const;
        virtual bool IsAlive();
        int type = 0;
        std::string getObjectType();
    	bool closeContact(VisibleGameObject &conter);
protected:
	sf::Sprite& GetSprite();
	std::string objectType;

private:
	sf::Sprite  sprite;
	sf::Texture image;
	std::string filename;
	bool isLoaded;
        bool alive;
	
};
