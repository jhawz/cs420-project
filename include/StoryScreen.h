/* 
 * File:   StoryScreen.h
 * Author: jch
 *
 * Created on November 14, 2014, 1:48 PM
 */

#ifndef STORYSCREEN_H
#define	STORYSCREEN_H

#pragma once
#include "stdafx.h"

class StoryScreen
{
public:
	int Show(sf::RenderWindow& window, int story_state);
        
private:
    int story_state;
    sf::Text story1;
    sf::Text story2;
    sf::Text story3;
    sf::Text story4;
    sf::Text death;
    sf::Text victory;
};

#endif	/* STORYSCREEN_H */