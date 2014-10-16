#include "Sprites.h"
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

using namespace std;

//desperately needs a split function.
void Sprites::loadAnimData(string filename)
{
    ifstream r;
    string lineVal;
    string lineData();
    r.open(filename);
    
    int startFrame = r.getline();
    int endFrame = r.getline();
    
    createAnimSeq(startFrame, endFrame);
    
    r.close();
}

void Sprites::load(string spriteImgFile, int hei, int wid)
{
    tex = new sf::Texture(spriteImgFile);
    
    height = hei;
    width = wid;
    
    sprite = new sf::Sprite(tex, new sf::IntRect(0, 0, wid, hei));
    
    sprite.setPosition(32, 32);
    
}

void Sprites::setPosition(int x, int y)
{
    sprite.setPosition(x, y);
}

void Sprites::setSpritesInRow(int spriteCount)
{
    spritesInRow = spriteCount;
}

void Sprites::move(int x, int y)
{
    sf::Vector2f curPos = sprite.getPosition();
    
    sprite.setPosition(curPos.x + x, curPos.y + y);
    
    
}

void Sprites::move(){
    
    sf::Vector2f curPos = sprite.getPosition();
    
    sprite.setPosition(curPos.x + vel.x, curPos.y + vel.y);
    
}

sf::Vector2f Sprites::getVelocity()
{
    return vel;
}

void Sprites::animate()
{
    if (animDelay <= 0)
    {
        animDelay = DELAY_MAX;
        if (curFrame >= maxFrame)
            curFrame = minFrame;
        else
            curFrame++;
        
    }
    else
        animDelay--;
    
    sprite.setTextureRect( new sf::IntRect(width * (curFrame % spritesInRow),
            height * (curFrame / spritesInRow), width, height));
    
}

int Sprites::getState()
{
    return state;
}

int Sprites::getCurrentFrame(){
    return curFrame;
}

void Sprites::draw()
{
    w.draw(sprite);
}

void Sprites::setFrameData(int c, int m, int ma)
{
    curFrame = c;
    minFrame = m;
    maxFrame = ma;
}

void Sprites::resetCurFrame()
{
    curFrame = minFrame;
}

void Sprites::createAnimSeq(int animState, int startFrame, int stopFrame)
{
    if (animSeqUsed < 9)
    {
        Sprites::AnimSeq a = new Sprites::AnimSeq(animState,
                startFrame, stopFrame);
        animList(animSeqUsed) = a;
        animSeqUsed++;
    }
    else
    {
        cout << "Anim Sequence Array full! FIGURE OUT THE DICTIONARY USAGE!" 
                << endl;
        
    }
    
}

void Sprites::changeAnimSequence(int animationState)
{
    Sprites::AnimSeq a = animList(animationState);
    
    minFrame = a.getStartFrame();
    maxFrame = a.getEndFrame();
    state = animationState;
}

