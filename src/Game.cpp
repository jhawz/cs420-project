#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "Enemy.h"
#include "Bond.h"
#include "VisibleGameObject.h"
#include "MapLoader.h"
#include "Tile.h"
#include "StoryScreen.h"
#include "ServiceLocator.h"
#include "SFMLSoundProvider.h"

void Game::Start(void) {
    if (gameState != Uninitialized)
        return;

    mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32)
            , "James Rambo: Revenge of Jaws!");

    view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

    gameState = Game::ShowingSplash;

    SFMLSoundProvider soundProvider;
    ServiceLocator::RegisterServiceLocator(&soundProvider);

    ServiceLocator::GetAudio()->PlaySong("music/Rambo_Theme.ogg", true);

    while (!IsExiting()) {
        GameLoop();
    }

    mainWindow.close();
}

bool Game::IsExiting() {
    if (gameState == Game::Exiting)
        return true;
    else
        return false;
}

sf::RenderWindow& Game::GetWindow() {
    return mainWindow;
}

const sf::Event& Game::GetInput() {
    sf::Event currentEvent;
    mainWindow.pollEvent(currentEvent);
    return currentEvent;
}

void Game::GameLoop() {
    sf::Event currentEvent;
    mainWindow.pollEvent(currentEvent);

    switch (gameState) {
        case Game::ShowingMenu:
        {
            ShowMenu();
            break;
        }
        case Game::ShowingSplash:
        {
            ShowSplashScreen();
            break;
        }
        case Game::ShowingStory:
        {
            ShowStoryScreen();
            break;
        }
        case Game::Loading:
        {
            LoadLevel();
            break;
        }
        case Game::Unloading:
        {
            unLoadLevel();
            break;
        }

        case Game::Playing:
        {
            //std::cout << gameObjectManager.GetObjectCount() << std::endl;

            cameraPosition.x = gameObjectManager.Get("Bond")->GetPosition().x + 32 - (SCREEN_WIDTH / 2);
            //cameraPosition.y = gameObjectManager.Get("Bond")->GetPosition().y - (SCREEN_HEIGHT);
            cameraPosition.y = 0;
            if (cameraPosition.x < 0)
                cameraPosition.x = 0;
            if (cameraPosition.y < 0)
                cameraPosition.y = 0;
            if (cameraPosition.x > LEVEL_WIDTH - SCREEN_WIDTH)
                cameraPosition.x = LEVEL_WIDTH - SCREEN_WIDTH;
            if (cameraPosition.y > LEVEL_HEIGHT)
                cameraPosition.y = LEVEL_HEIGHT;

            view.reset(sf::FloatRect(cameraPosition.x, cameraPosition.y, SCREEN_WIDTH, SCREEN_HEIGHT));

            mainWindow.clear(sf::Color::Black);
            mainWindow.setView(view);

            gameObjectManager.UpdateAll();
            gameObjectManager.DrawAll(mainWindow);

                       switch (gameObjectManager.Get("Bond")->getLives()) {
                
                case 1:
                    hud.head_1.setPosition(cameraPosition.x, cameraPosition.y);
                    mainWindow.draw(hud.head_1);
                    break;
                case 2:
                    hud.head_1.setPosition(cameraPosition.x, cameraPosition.y);
                    hud.head_2.setPosition(cameraPosition.x + 
                    hud.head_1.getTextureRect().width, cameraPosition.y);
                    mainWindow.draw(hud.head_1);
                    mainWindow.draw(hud.head_2);
                    break;
                case 3:
                    hud.head_1.setPosition(cameraPosition.x, cameraPosition.y);
                    hud.head_2.setPosition(cameraPosition.x +
                    hud.head_1.getTextureRect().width, cameraPosition.y);
                    hud.head_3.setPosition(cameraPosition.x +
                    hud.head_1.getTextureRect().width * 2, cameraPosition.y);
                    mainWindow.draw(hud.head_1);
                    mainWindow.draw(hud.head_2);
                    mainWindow.draw(hud.head_3);
                    break;
            }

            mainWindow.display();
            if (currentEvent.type == sf::Event::Closed) gameState = Game::Exiting;

            if (currentEvent.type == sf::Event::KeyPressed) {
                if (currentEvent.key.code == sf::Keyboard::Escape) {
                    gameObjectManager.RemoveAll();
                    ShowMenu();
                }
            }
            if (gameObjectManager.isReadyForNextLevel())
            {
                gameObjectManager.increLevel();
                gameObjectManager.unsetReadyForNextLevel();
                gameState = Game::Unloading;
                std::cout << "Starting unload" << std::endl;
            }

            break;
        }
    }
}

void Game::unLoadLevel()
{
    gameObjectManager.RemoveAll();
    gameState = Game::Loading;
    std::cout << "Starting load; unload finished" << std::endl;
}

void Game::ShowSplashScreen() {
    SplashScreen splashScreen;
    splashScreen.Show(mainWindow);
    gameState = Game::ShowingMenu;
}

void Game::ShowMenu() {
    MainMenu mainMenu;
    MainMenu::MenuResult result = mainMenu.Show(mainWindow);
    switch (result) {
        case MainMenu::Exit:
            gameState = Exiting;
            break;
        case MainMenu::Play:
            gameState = ShowingStory;
            break;
    }
    std::cout << "Resetting level..." << std::endl;
    gameObjectManager.resetLevelToOne();
    std::cout << "Level Reset" << std::endl;
}

void Game::ShowStoryScreen() {
    StoryScreen storyScreen;
    int cLevel=gameObjectManager.getLevelCode();
    switch(cLevel){
        case 1:
            storyScreen.Show(mainWindow,0);
            break;
        case 6:
            storyScreen.Show(mainWindow,1);
            break;
        case 11:
            storyScreen.Show(mainWindow,2);
            break;
        case 16:
            storyScreen.Show(mainWindow,3);
            break;
        case 21:
            storyScreen.Show(mainWindow,5);
            break;
    }
    LoadLevel();
}

void Game::LoadLevel() {
    Level* l = new Level();

    l->loadLevel(gameObjectManager.getLevelCode());

    gameObjectManager.setCollisionList(l->getTileColList());

    std::vector<Tile*> tiles = l->getTileList();

    for (int x = 0; x < tiles.size(); x++) {
        gameObjectManager.Add("Tile" + (std::to_string(x)), tiles[x]);
    }

    std::vector<Enemy*> enemies = l->getEnemyList();

    for (int x = 0; x < enemies.size(); x++) {
        std::cout << "Loaded Enemy" << std::endl;
        gameObjectManager.Add("Enemy" + (std::to_string(x)), enemies[x]);
    }

    std::vector<Powerup*> powerups = l->getPowerupList();

    for (int x = 0; x < powerups.size(); x++) {
        std::cout << "Loaded Powerup" << std::endl;
        gameObjectManager.Add("Powerup", powerups[x]);
    }
    
    std::vector<int> exitPos = l->getExitCodes();
    
    gameObjectManager.setExitList(exitPos);

    if (gameObjectManager.getLevelCode() == 20)
    {
        Jaw* j = l->getJaws();
        gameObjectManager.j = j;
        gameObjectManager.Add("Jaws", j);
        
        Co* c = l->getCo();
        gameObjectManager.c = c;
        gameObjectManager.Add("Co", c);
        
    }
    
    Bond* b = l->getBond();
    gameObjectManager.b = b;
    gameObjectManager.Add("Bond", b);

    gameObjectManager.Add("Background", l->getBackground());
    gameState = Playing;
    gameObjectManager.setCurLevel(l);
}

Game::GameState Game::gameState = Uninitialized;
sf::RenderWindow Game::mainWindow;
sf::View Game::view;
Hud Game::hud;
sf::Vector2f Game::cameraPosition;
GameObjectManager Game::gameObjectManager;
