#ifndef __Animation__
#define __Animation__

#include <cstdio>
#include <iostream>
#include <sfml/System/Time.hpp>
#include <sfml/Graphics.hpp>
#include <vector>

class Animation:public sf::Sprite{
public:
    Animation();
    void setAnimationPeriod(int minisec);
    void setRepeatable(bool rep);
    void addFrame(sf::IntRect frame);
    void restart();
    void end();
    bool isEnded();
    bool play();
    sf::IntRect getCurFrame();
    
private:
    std::vector<sf::IntRect> m_frames;
    bool repeatable;
    bool ended;
    int curFrame;
    int frameCount;
    sf::Time period;
    sf::Clock clock;
};


#endif /* defined(__Animation__) */
