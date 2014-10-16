#include <SFML/Graphics.hpp>
#include <iostream>
#include "Rambo.h"

int main(int argc, char** argv) {
    // create main window
    sf::RenderWindow GameWindow(sf::VideoMode(800, 600, 32), "Hello World - SFML");

   /* sf::Texture texture;

    if (!texture.loadFromFile("sprites/wood.png")) {
        std::cout << "Error loading wood texture" << std::endl;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
    */

    Rambo rambo;
    
    // start main loop
    while (GameWindow.isOpen()) {
        // process events
        sf::Event Event;
        while (GameWindow.pollEvent(Event)) {
            // Exit
            if (Event.type == sf::Event::Closed)
                GameWindow.close();
        }

        // clear screen and fill with blue
        GameWindow.clear();

        GameWindow.draw(rambo);
        // display
        GameWindow.display();
    }

    // Done.
    return 0;
}
