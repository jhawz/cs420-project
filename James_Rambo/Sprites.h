/* 
 * File:   Sprites.h
 * Author: will
 *
 * Created on October 9, 2014, 3:32 PM
 */

#ifndef SPRITES_H
#define	SPRITES_H
        

#endif	/* SPRITES_H */

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string.h>

using namespace std;

class Sprites
{
    
    private:
    int spritesInRow;
    int height;
    int width;
    sf::Vector2f vel;
    int curFrame;
    int maxFrame;
    int minFrame;
    sf::Texture tex;
    sf::Sprite sprite;
    sf::RenderWindow w;
    AnimSeq animList(10);
    int animSeqUsed = 0;
    int state;
    int animDelay = DELAY_MAX; //Convert into Constants for class later.
    const int DELAY_MAX = 2;
    
    class AnimSeq
    {
        
    private:
        
        AnimSeq(int animState, int sf, int ef)
        {
            startFrame = sf;
            endFrame = ef;
        }
        
        int startFrame;
        int endFrame;
        
    public:
        int getStartFrame();
        int getEndFrame();
        
    };
    
    public:
        
        Sprites(sf::RenderWindow& w)
        {
            this->w = w;
        }
    
        void loadAnimData(string filename);
        void load(string spriteImgFile);
        void setPosition(int x, int y);
        void setSpritesInRow(int spriteCount);
        void move(int x, int y);
        void move();
        void animate();
        int getState();
        int getCurrentFrame();
        sf::Vector2f getVelocity();
        void draw();
        void setFrameData(int c, int m, int ma);
        void resetCurFrame();
        void createAnimSeq(int animationState, int startFrame, int endFrame);
        void changeAnimSequence(int animState);
        
        
};