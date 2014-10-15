#include "Animation.h"

Animation::Animation(){
    repeatable=true;
    curFrame=0;
    period=sf::milliseconds(100);
    frameCount=0;
    clock.restart();
}

void Animation::setAnimationPeriod(int minisec){
    period=sf::milliseconds(minisec);
}

void Animation::addFrame(sf::IntRect frame){
    m_frames.push_back(frame);
    setTextureRect(m_frames[curFrame]);
    frameCount++;
}

sf::IntRect Animation::getCurFrame(){
    return m_frames[curFrame];
}

bool Animation::play(){
    int elapsedPeriods=clock.getElapsedTime().asMilliseconds()/period.asMilliseconds();
    if ((!repeatable)&&(curFrame>=frameCount)) {
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
    ended=true;
}

bool Animation::isEnded(){
    return ended;
}
