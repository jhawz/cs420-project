#ifndef JAW_H
#define JAW_H

#include <cstdio>
#include <iostream>

#include "Actor.h"

class Jaw:public Actor{
public:
    Jaw(std::string config, std::string texture);
    void attack(Actor& actor);
};
