
#include "StoryScreen.h"

int StoryScreen::Show(sf::RenderWindow & renderWindow, int story_state) {
    // Load the text font
    sf::Font font; // Set font variable, gotta declare it before you call it duh
    if (!font.loadFromFile("fonts/BebasNeue.otf")) { // You can change the font file, it was what I had on hand.

        return 100; // Everything fails if you don't have the font file.
    }

    // Stories 
    sf::Text story1("You are James Rambo, back from your tour of duty. \
    \nAfter defeating the gang known as the Ladies of Saigon. \
    \nYou come back to America for a little R&R only to \
    \nrealize your girlfriend Co Galore has been kidnapped. \
    \nAll evidence points to an abandoned factory, you go to check it out.\
    \nYou enter the factory and you hear over the crack of the intercom:\
    \nWho dares enter the factory lair of Jaws?\
    \nYou respond:the name's Rambo...James Rambo as you smash in the door.\
    \n\nPress enter to continue...", font, 30);

    sf::Text story2("After defeating the first set of henchmen you learn\
    \nthat the factory has four floors with Co being held on the last one.\
    \nJaws,as you mutter to yourself how do I know you? As if spurred by\
    \nyour comment the intercom cackles: Mister Rambo; I have Co and \
    \nI intend to take her as my bride, just try to stop me James Rambo!\
    \nThe intercom chimes out as you proceed deeper into Jaw's lair.\
    \n\nPress enter to continue...", font, 30);
    story2.setPosition(2400, 0);

    sf::Text story3("After defeating more of Jaws's henchman you advance\
    \nthrough this floor only being taunted by Jaws throughout.\
    \nhe knows you are coming for him, you hear the urgency in his voice\
    \nAll henchmen attack! you hear over the intercom.\
    \nAs you go through the door and descend deeper into the factory.\
    \n\nPress enter to continue...", font, 30);
    story3.setPosition(2400, 0);

    sf::Text story4("You proceed through the last door, as you walk down the corridor\
    \nyou collect your thoughts and prepare yourself mentally for the battle ahead. \
    \nAll of Jaw's men are after you now,Jaws's end is imminent.\
    \n", font, 30);
    story4.setPosition(2400, 0);

    sf::Text death("\n\n                      GAME OVER", font, 80);

    sf::Text victory("You rush over to Co, James...James...Rambo she screams in delight\
    \nYou saved me from Jaws, you don't say a word because badasses don't.\
    \nYou just give a head nod in acknowledgment....The end", font, 30);
    victory.setPosition(2400, 0);

    enum stories {
        story_1, story_2, story_3, story_4, _death, _victory
    }; // Our story states not to be confused with our actual stories themselves.

    renderWindow.clear();

    while (renderWindow.isOpen()) {
        switch (story_state) {

            case 0:
                renderWindow.draw(story1);
                break;
            case 1:
                renderWindow.draw(story2);
                break;
            case 2:
                renderWindow.draw(story3);
                break;
            case 3:
                renderWindow.draw(story4);
                break;
            case 4:
                renderWindow.draw(death);
                break;
            case 5:
                renderWindow.draw(victory);
                break;
        }

        renderWindow.display(); // Display the stories, why it has to come after the states...I don't know

        sf::Event event;
        while (renderWindow.pollEvent(event)) {
            if ((event.type == sf::Event::Closed) || // If window is closed
                    ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))// Looks for a key pressed & key must be esc key
                renderWindow.close();

            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) { // Looks for key pressed & it being in state
                return story_state;
            }
            renderWindow.clear(); // Clears the window, if we don't have it then it F's up the display 
        }
    }
}