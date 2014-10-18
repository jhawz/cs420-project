#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include "Rambo.h"
#include "Animation.h"

int main(int argc, char** argv) {
    sf::Clock clock;
    sf::Time period = sf::milliseconds(20);
    // create main window
    sf::RenderWindow GameWindow(sf::VideoMode(1024, 768, 32), "Hello World - SFML");
    sf::Image image;
    if (!image.loadFromFile("sprites/bond_sheet.png")) {
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
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            rambo.leftRun();
        }
        else {
            rambo.standStill();
        }
        //rambo.update should appear here instead;
        rambo.update();

        // clear screen and fill with blue
        GameWindow.clear(sf::Color::White);

        //The following method should be removed because this is not the right place for it to appear.
        /*
        rambo.prepareFrameInfo();
         */
        GameWindow.draw(rambo);
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