
#include <iostream>
#include <Sprites.cpp>


int main(int argc, char**argv) {
    // Prints welcome message...
    /*
    std::cout << "Welcome ..." << std::endl;

    // Prints arguments...
    if (argc > 1) {
        std::cout << std::endl << "Arguments:" << std::endl;
        for (int i = 1; i < argc; i++) {
            std::cout << i << ": " << argv[i] << std::endl;
        }
    }
    
    return 0;
     */
    
    //EXAMPLE CODE FOR WHEN THIS THING IS BUILT
    /*
     * sf::RenderWindow r = new sf::RenderWindow(sf::VideoMode(800, 600));
     * Sprites character = new Sprites(r);
     * character->loadAnimData("animData.txt");
     * If you want to test the animation, create a text file that has a starting frame
     * value on one line and an ending frame value on the next and then link it to the
     * character-> loadAnimData command.
     * 
     * an example would be:
     * 0
     * 5
     * 
     * character->load("mainCharImg.png", 32, 32);
     * character should now be loaded and ready for drawing.
     * draw it with character->draw();
     * animate it with character->animate();
     * animate cycles through sections of the sprite
     * draw actually puts it on the screen
     * I kept them separate for working/testing purposes...they can be combined later.
     * 
    */
}
