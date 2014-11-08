#include "Animation.h"

Animation::Animation(){
    curFrame=0;
    period=sf::milliseconds(100);
    frameCount=0;
    clock.restart();
}

void Animation::loadFromXml(pugi::xml_node& node){
    pugi::xml_node cur;
    bool rep=node.attribute("repeatable").as_bool();
    setRepeatable(rep);
    int p=node.attribute("period").as_int();
    setAnimationPeriod(p);
    bool totalline=node.attribute("whole_line").as_bool();
    if (totalline) {
        int line=node.attribute("line").as_int();
        int framenumber=node.attribute("frame_number").as_int();
        for (int i=0; i<framenumber; i++) {
            addFrame(sf::IntRect(i*32,line*64,32,64));
        }
    }
    else{
        int line=node.attribute("line").as_int();
        std::istringstream ss(std::string(node.text().as_string()));
        std::string token;
        while (std::getline(ss, token,',')) {
            int i=std::stoi(token);
            addFrame(sf::IntRect(i*32,line*64,32,64));
        }
    }
}

void Animation::setAnimationPeriod(int minisec){
    period=sf::milliseconds(minisec);
}

void Animation::addFrame(sf::IntRect frame){
    sf::IntRect rect(frame);
    if (rect.width<0) {
        rect.left+=frame.width;
        rect.width*=-1;
    }
    if (rect.height<0) {
        rect.top+=frame.height;
        rect.height*=-1;
    }
    m_frames.push_back(rect);
    
    frameCount++;
}

sf::IntRect Animation::getCurFrame(){
    return m_frames[curFrame];
}

bool Animation::play(){
    int elapsedPeriods=clock.getElapsedTime().asMilliseconds()/period.asMilliseconds();
    if ((!repeatable)&&(curFrame>=frameCount-1)) {
        end();
    }
    if(!ended){
        switch (elapsedPeriods) {
            case 0:
                return false;
            default:
                curFrame+=elapsedPeriods;
                curFrame=curFrame%frameCount;
                clock.restart();
                return true;
                break;
        }
    }
    else return false;
}

void Animation::setRepeatable(bool rep){
    repeatable=rep;
}

void Animation::restart(){
    ended=false;
    curFrame=0;
}

void Animation::end(){
    curFrame=0;
    ended=true;
}

bool Animation::isEnded(){
    return ended;
}


