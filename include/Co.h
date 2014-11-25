/* 
 * File:   Co.h
 * Author: moth
 *
 * Created on November 25, 2014, 4:45 AM
 */

#ifndef CO_H
#define	CO_H

#include "stdafx.h"
#include "Animation.h"
#include "pugixml.hpp"
#include "Actor.h"

class Co : public Actor {
public:
    Co(std::string config, sf::Texture& t);
    void Update(float elapsedTime);
    private:
};
#endif	/* CO_H */