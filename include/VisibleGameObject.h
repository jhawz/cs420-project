#pragma once
#include "stdafx.h"

class VisibleGameObject {
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
    bool closeContact(VisibleGameObject* conter);
    bool closeContact(sf::Vector2f obj2);
    void setFiring(bool fire);
    bool getFiring();
    bool isFacingRight();
    void setFacingRight();
    void setFacingLeft();
    void setRemove();
    bool getRemove();
    void setName(std::string objName);
    std::string getName();
    bool isExit();
    void setAsExit();
    
    static const int TILE = 0;
    static const int BOND = 1;
    static const int ENEMY = 2;
    static const int JAWS = 3;
    static const int BULLET = 4;
    static const int MARTINI = 5;

protected:
    sf::Sprite& GetSprite();
    std::string objectType;

private:
    sf::Sprite sprite;
    sf::Texture image;
    std::string filename;
    bool isLoaded;
    bool removed = false;
    bool alive;
    bool firing = false;
    bool rightDir;
    std::string name;
    bool exitObj = false;
};
