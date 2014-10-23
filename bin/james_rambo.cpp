/* 
 * File:   james_rambo.cpp
 * Author: jch
 *
 * Created on October 22, 2014, 2:45 PM
 */

using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include "Rambo.h"
#include "Enemy.h"
#include "Animation.h"
#include <cstdlib>

int main(int argc, char** argv) {
    sf::Clock clock;
    sf::Time period = sf::milliseconds(20);
    // create main window
    sf::RenderWindow GameWindow(sf::VideoMode(800, 548, 32), "James Rambo: Will Finger's Revenge");

    
    sf::Image image;
    if (!image.loadFromFile("sprites/SpriteSheet.png")) {
        std::cout << "Error loading texture image" << std::endl;
        return 1;
    }
    image.createMaskFromColor(image.getPixel(1, 1));
    
    sf::Texture background;
    if (!background.loadFromFile("sprites/background.png")) {
        std::cout << "Error initializing the texture" << std::endl;
        std::cout << "" << std::endl;
    }
    
    sf::Sprite bgsprite;
    bgsprite.setTexture(background);

    sf::Texture texture;
    if (!texture.loadFromImage(image)) {
        std::cout << "Error initializing the texture" << std::endl;
        std::cout << "" << std::endl;
    }
    texture.setSmooth(true);
    Rambo rambo;
    rambo.setTexture(texture);
    rambo.prepareFrameInfo(); //In this method, it prepares for the frames needed by the animations.
    rambo.setPosition(0, 340);
    rambo.setOriginalImg(image);

    Enemy enemy_1;
    enemy_1.setTexture(texture);
    enemy_1.setPistol();
    enemy_1.setPosition(800, 340);

    Enemy enemy_2;
    enemy_2.setTexture(texture);
    enemy_2.setSmg();
    enemy_2.setPosition(740, 340);

    Enemy enemy_3;
    enemy_3.setTexture(texture);
    enemy_3.setMachineGun();
    enemy_3.setPosition(700, 340);

    // start main loop
    while (GameWindow.isOpen()) {
        clock.restart();
        // process events
        sf::Event Event;
        while (GameWindow.pollEvent(Event)) {
            // Exit
            if (Event.type == sf::Event::Closed)
                GameWindow.close();
            //No matter whether there is an event or not, rambo.update() should be called so it should not appear here.
            /*
                        rambo.update();
             */
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            rambo.rightRun();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            rambo.leftRun();
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            rambo.jump();
        } else {
            rambo.standStill();
        }

        if (enemy_1.isAlive()) {
            if (enemy_1.getPosition().x >= rambo.getPosition().x + 100
                    && enemy_1.isAttacking() == true) {
                enemy_1.leftRun();
            }
            if (enemy_1.getPosition().x < rambo.getPosition().x + 100
                    && enemy_1.isAttacking() == true) {
                enemy_1.setAttack(false);
            }
            if (enemy_1.getPosition().x <= rambo.getPosition().x + 600
                    && enemy_1.isAttacking() == false) {
                enemy_1.rightRun();
            }
            if (enemy_1.getPosition().x > rambo.getPosition().x + 600
                    && enemy_1.isAttacking() == false) {
                enemy_1.setAttack(true);
            }
        }

        if (enemy_2.isAlive()) {
            if (enemy_2.getPosition().x >= rambo.getPosition().x + 150
                    && enemy_2.isAttacking() == true) {
                enemy_2.leftRun();
            }
            if (enemy_2.getPosition().x < rambo.getPosition().x + 150
                    && enemy_2.isAttacking() == true) {
                enemy_2.setAttack(false);
            }
            if (enemy_2.getPosition().x <= rambo.getPosition().x + 600
                    && enemy_2.isAttacking() == false) {
                enemy_2.rightRun();
            }
            if (enemy_2.getPosition().x > rambo.getPosition().x + 600
                    && enemy_2.isAttacking() == false) {
                enemy_2.setAttack(true);
            }
        }

        if (enemy_3.isAlive()) {
            if (enemy_3.getPosition().x >= rambo.getPosition().x + 50
                    && enemy_3.isAttacking() == true) {
                enemy_3.leftRun();
            }
            if (enemy_3.getPosition().x < rambo.getPosition().x + 50
                    && enemy_3.isAttacking() == true) {
                enemy_3.setAttack(false);
            }
            if (enemy_3.getPosition().x <= rambo.getPosition().x + 600
                    && enemy_3.isAttacking() == false) {
                enemy_3.rightRun();
            }
            if (enemy_3.getPosition().x > rambo.getPosition().x + 600
                    && enemy_3.isAttacking() == false) {
                enemy_3.setAttack(true);
            }
        }

        GameWindow.clear();
        GameWindow.draw(bgsprite);

        //rambo.update should appear here instead;
        rambo.update();
        GameWindow.draw(rambo);
        enemy_1.update();
        GameWindow.draw(enemy_1);
        enemy_2.update();
        GameWindow.draw(enemy_2);
        enemy_3.update();
        GameWindow.draw(enemy_3);

        // display
        GameWindow.display();
        sf::Time elapsed = clock.getElapsedTime();
        if (period > elapsed) {
            sf::sleep(period - elapsed);
        }
    }

    // Done.
    return 0;
}