#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include "Rambo.h"
#include "Enemy.h"
#include "Animation.h"

int main(int argc, char** argv) {
    sf::Clock clock;
    sf::Time period = sf::milliseconds(20);
    // create main window
    sf::RenderWindow GameWindow(sf::VideoMode(800, 600, 32), "Hello World - SFML");
    sf::Image image;
    if (!image.loadFromFile("sprites/SpriteSheet.png")) {
        std::cout << "Error loading texture image" << std::endl;
        return 1;
    }
    image.createMaskFromColor(image.getPixel(1, 1));

    sf::Texture texture;
    if (!texture.loadFromImage(image)) {
        std::cout << "Error initializing the texture" << std::endl;
        std::cout << "" << std::endl;
    }
    texture.setSmooth(true);
    Rambo rambo;
    rambo.setTexture(texture);
    rambo.prepareFrameInfo(); //In this method, it prepares for the frames needed by the animations.
    rambo.setPosition(0, 400);

    Enemy enemy_1;
    enemy_1.setTexture(texture);
    enemy_1.setPistol();
    enemy_1.setPosition(800, 400);

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
                std::cout << "retreat" << std::endl;
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

        //rambo.update should appear here instead;
        rambo.update();
        enemy_1.update();

        // clear screen and fill with blue
        GameWindow.clear(sf::Color::White);


        GameWindow.draw(rambo);
        GameWindow.draw(enemy_1);
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