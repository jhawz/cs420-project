#include "stdafx.h"
#include "VisibleGameObject.h"


VisibleGameObject::VisibleGameObject()
	: isLoaded(false)
{
	//isLoaded = false; Slightly faster to use the above constructor initialization.
}


VisibleGameObject::~VisibleGameObject()
{
}

void VisibleGameObject::Load(std::string filename)
{
	if(image.loadFromFile(filename) == false)
	{
		filename = "";
		isLoaded = false;
	}
	else
	{
		filename = filename;
		sprite.setTexture(image);
		isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow & renderWindow)
{
	if(isLoaded)
	{
		renderWindow.draw(sprite);
	}
}

void VisibleGameObject::Update(float elapsedTime)
{
}

void VisibleGameObject::SetPosition(float x, float y)
{
	if(isLoaded)
	{
		std::cout<<"Setting position "<<x<<","<<y<<std::endl;
		sprite.setPosition(x,y);
	}
}

sf::Vector2f VisibleGameObject::GetPosition() const
{
  if(isLoaded)
  {
    return sprite.getPosition();
  }
  return sf::Vector2f();
}


sf::Sprite& VisibleGameObject::GetSprite()
{
  return sprite;
}

bool VisibleGameObject::IsLoaded() const
{
  return isLoaded;
}
