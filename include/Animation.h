#ifndef __Animation__
#define __Animation__

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sfml/System/Time.hpp>
#include <sfml/Graphics.hpp>
#include <vector>
#include "pugixml.hpp"

class Animation{
public:
    Animation();
    void loadFromXml(pugi::xml_node& node);
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
