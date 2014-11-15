#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window) {

    //Load menu image from file
    sf::Texture image;
    image.loadFromFile("textures/Mainmenu.png");
    sf::Sprite sprite(image);

    //Setup clickable regions

    //Play menu item coordinates
    MenuItem playButton;
    playButton.rect.top = 110;
    playButton.rect.width = 800;
    playButton.rect.left = 0;
    playButton.rect.height = 190;
    playButton.action = Play;

    //Exit menu item coordinates
    MenuItem exitButton;
    exitButton.rect.left = 0;
    exitButton.rect.height = 145;
    exitButton.rect.top = 300;
    exitButton.rect.width = 800;
    exitButton.action = Exit;

    menuItems.push_back(playButton);
    menuItems.push_back(exitButton);

    window.draw(sprite);
    window.display();

    return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y) {
    std::list<MenuItem>::iterator it;

    for (it = menuItems.begin(); it != menuItems.end(); it++) {
        sf::Rect<int> menuItemRect = (*it).rect;
        std::cout << "X: " << x << std::endl;
        std::cout << "Y: " << y << std::endl;
        std::cout << "Width > y: " << (menuItemRect.width > y) << std::endl;
        std::cout << "Top < y: " << (menuItemRect.top < y) << std::endl;
        std::cout << "Left < x: " << (menuItemRect.left < x) << std::endl;
        std::cout << "Height > x: " << (menuItemRect.height > x) << std::endl;
        
        if (menuItemRect.width > y
                && menuItemRect.top < y
                && menuItemRect.left < x
                && (menuItemRect.height
                + menuItemRect.top) > y) {
            return (*it).action;
        }
    }

    return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window) {
    sf::Event menuEvent;

    while (42 != 43) {

        while (window.pollEvent(menuEvent)) {
            if (menuEvent.type == sf::Event::MouseButtonPressed) {

                return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
            }
            if (menuEvent.type == sf::Event::Closed) {
                return Exit;
            }
        }
    }
}