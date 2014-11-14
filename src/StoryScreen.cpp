
#include "StoryScreen.h"

int StoryScreen::Show(sf::RenderWindow & renderWindow, int story_state) {
    // Load the text font
    sf::Font font; // Set font variable, gotta declare it before you call it duh
    if (!font.loadFromFile("fonts/BebasNeue.otf")) { // You can change the font file, it was what I had on hand.

        return 100; // Everything fails if you don't have the font file.
    }

    //window.display(background);

    sf::Text text;
    text.setFont(font);

    // Stories 
    sf::Text story1("You are James Rambo, back from your tour of duty. \n \
    After defeating the gang known as the Ladies of Saigon.\n \
    You come back to America for a little R&R only to \
    realize your girlfriend Co Galore has been kidnapped. \n \
    All evidence points to an abandoned factory, you go to check it out. \n \n \
    Press Any Key To Continue...", font, 30);
    //story1.setPosition(width/2-story1.getGlobalBounds().width/2,600); // Formating 

    sf::Text story2("During your fight with the henchman of the factory you learn that, it is your nemesis Jaws who kidnapped Co. \n \
    Jaws holds a grudge with you after you won Co over at the Casino Royale.\n \
    He wants what he thinks is rightfully his.  You find a door that takes you deeper into Jaws' lair.\n \n \
    Press Any Key To Continue...", font, 30);

    sf::Text story3("After defeating more of Jaws' henchman, you advance through this floor only being taunted by Jaws throughout.\n \n \
    Press Any Key To Continue...", font, 30);

    sf::Text story4("Test4", font, 30);

    enum stories {
        story_1, story_2, story_3, story_4
    }; // Our story states not to be confused with our actual stories themselves.

    while (renderWindow.isOpen()) {
        switch (story_state) {
            case story_1:
                renderWindow.draw(story1);
                break;
            case story_2:
                renderWindow.draw(story2);
                break;
            case story_3:
                renderWindow.draw(story3);
                break;
            case story_4:
                renderWindow.draw(story4);
                break;
        }


        renderWindow.display(); // Display the stories, why it has to come after the states...I don't know

        sf::Event event;
        while (renderWindow.pollEvent(event)) {
            if ((event.type == sf::Event::Closed) || // If window is closed
                    ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))// Looks for a key pressed & key must be esc key
                renderWindow.close();

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (story_state == story_1)) { // Looks for key pressed & it being in state
                return story_state;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (story_state == story_2)) {
                story_state = story_3;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (story_state == story_3)) {
                story_state = story_4;
            }

        }


        renderWindow.clear(); // Clears the window, if we don't have it then it F's up the display 

    }
}