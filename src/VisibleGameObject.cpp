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
void VisibleGameObject::Load(sf::Texture& t, 
        sf::Vector2i textPos, sf::Vector2i textRect)
{
    image = t;
    sprite.setTexture(t);
    sprite.setTextureRect(sf::IntRect(textPos.x, textPos.y, 
            textRect.x, textRect.y));
    isLoaded = true;
        
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

bool VisibleGameObject::IsAlive()
{
    return alive;
}

void VisibleGameObject::setAlive()
{
    alive = true;
}

void VisibleGameObject::setNotAlive()
{
    alive = false;
}

std::string VisibleGameObject::getObjectType(){
    return objectType;
}

bool VisibleGameObject::closeContact(VisibleGameObject &conter){
    sf::Vector2f myPos,conterPos;
    myPos=GetPosition();
    conterPos=conter.GetPosition();
    if ((myPos.x-conterPos.x<=32)
        &&(myPos.x-conterPos.x>=-32)
        &&(myPos.y-conterPos.y<=64)
        &&(myPos.y-conterPos.y>=-64)) {
        return true;
    }
    else return false;
}

bool VisibleGameObject::closeContact(sf::Vector2f obj2)
{
    sf::Vector2f myPos;
    myPos = GetPosition();
    if ((myPos.x -obj2.x <= 32)
            &&(myPos.x - obj2.x >= -32)
            &&(myPos.y - obj2.y <= 64)
            &&(myPos.y - obj2.y >= -64))
    {
        return true;
    }
    return false;
}
bool VisibleGameObject::closeContact(VisibleGameObject* conter){
    sf::Vector2f myPos,conterPos;
    myPos=GetPosition();
    conterPos=conter->GetPosition();
    if ((myPos.x-conterPos.x<=32)
        &&(myPos.x-conterPos.x>=-32)
       &&(myPos.
            y-conterPos.y<=30)
        &&(myPos.y-conterPos.y>=-30)) {
        return true;
    }
    else return false;
}

void VisibleGameObject::setFiring(bool fire){
    firing = fire;
}

bool VisibleGameObject::getFiring(){
    return firing;
}

bool VisibleGameObject::isFacingRight(){
    return rightDir;
}

void VisibleGameObject::setFacingRight(){
    rightDir = true;
}

void VisibleGameObject::setFacingLeft(){
    rightDir = false;
}

void VisibleGameObject::setRemove(){
    removed = true;
}

bool VisibleGameObject::getRemove(){
    return removed;
}

void VisibleGameObject::setName(std::string objName){
    name = objName;
}

std::string VisibleGameObject::getName(){
    return name;
}

bool VisibleGameObject::isExit()
{
    return exitObj;
}

void VisibleGameObject::setAsExit()
{
    exitObj = true;
}

int VisibleGameObject::getLives(){
    return lives;
}

void VisibleGameObject::setLives(int life_count){
    lives = life_count;
}

