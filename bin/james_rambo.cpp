/* 
 * File:   james_rambo.cpp
 * Author: jch
 *
 * Created on October 22, 2014, 2:45 PM
 */

using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Rambo.h"
#include "Enemy.h"
#include "Animation.h"
#include "Projectile.h"
#include "pugixml.hpp"
#include <cstdlib>

int main(int argc, char** argv) {
    sf::Clock clock;
    sf::Time period = sf::milliseconds(20);
    sf::Clock shot_clock;
    // create main window
    sf::RenderWindow GameWindow(sf::VideoMode(800, 548, 32), "James Rambo: Will Finger's Revenge");
    
    pugi::xml_document doc;
    doc.load_file("actors.xml");
    
    pugi::xml_node rambonode=doc.child("root").find_child_by_attribute("Actor", "name", "Rambo");


    sf::Image image;
    if (!image.loadFromFile("textures/SpriteSheet.png")) {
        std::cout << "Error loading texture image" << std::endl;
        return 1;
    }
    image.createMaskFromColor(image.getPixel(1, 1));

    sf::Texture background;
    if (!background.loadFromFile("textures/background.png")) {
        std::cout << "Error initializing the texture" << std::endl;
        std::cout << "" << std::endl;
    }

    sf::Sprite background_texture;
    background_texture.setTexture(background);

    sf::Texture texture;
    if (!texture.loadFromImage(image)) {
        std::cout << "Error initializing the texture" << std::endl;
        std::cout << "" << std::endl;
    }
    texture.setSmooth(true);
    Rambo rambo;
    rambo.setTexture(texture);
    rambo.prepareFrameInfo(rambonode); //In this method, it prepares for the frames needed by the animations.
    rambo.setPosition(50, 340);
    rambo.setOriginalImg(image);

    Projectile bullet;
    bullet.setTexture(texture);
    bullet.setBullet();

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

    sf::Music bond_theme;
    bond_theme.openFromFile("music/bond_theme.ogg");
    bond_theme.setLoop(true);
    bond_theme.setVolume(50.0);
    //bond_theme.play();

    // start main loop
    while (GameWindow.isOpen()) {
        clock.restart();
        // process events
        sf::Event event;
        while (GameWindow.pollEvent(event)) {
            // Exit
            if (event.type == sf::Event::Closed)
                GameWindow.close();
            // Escape pressed : exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                GameWindow.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            rambo.rightRun();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                rambo.jump();
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            rambo.leftRun();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                rambo.jump();
            }
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            rambo.jump();
        } else {
            rambo.standStill();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
                shot_clock.getElapsedTime().asSeconds() > 1) {
            rambo.shoot();
            bullet.setPosition(rambo.getPosition().x, rambo.getPosition().y + 15);
            bullet.fire();
            shot_clock.restart();
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

        //rambo.update should appear here instead;
        rambo.update();

        enemy_1.update();
        enemy_2.update();
        enemy_3.update();

        GameWindow.clear();

        GameWindow.draw(background_texture);
        GameWindow.draw(rambo);
        if (bullet.isActive()) {
            bullet.update();
            GameWindow.draw(bullet);
        }
        GameWindow.draw(enemy_1);
        GameWindow.draw(enemy_2);
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
