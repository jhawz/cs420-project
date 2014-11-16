#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "Enemy.h"
#include "Bond.h"
#include "VisibleGameObject.h"
#include "MapLoader.h"
#include "Tile.h"
#include "Level.h"

void Game::Start(void) {
    if (gameState != Uninitialized)
        return;

    mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32)
    , "James Rambo: Revenge of WillFinger!");

    //mainWindow.SetFramerateLimit(60);    

    view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
    view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

    gameState = Game::ShowingSplash;

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
        case Game::Loading:
        {
            Level* l = new Level();
    
            l->loadLevel(gameObjectManager.getLevelCode());

            gameObjectManager.setCollisionList(l->getTileColList());

            Enemy *enemy_1 = new Enemy("actors.xml", "textures/enemy.png", "Pistol");
            enemy_1->SetPosition(300, 200);
            enemy_1->setBoundary(0, 0, 800, 464);

            Bond *bond = new Bond("actors.xml", "textures/JB.png");
            bond->SetPosition(200, 200);
            bond->setBoundary(0, 0, 800, 464);

            gameObjectManager.Add("Bond", bond);
            gameObjectManager.Add("Enemy", enemy_1);
            std::vector<Tile*> tiles = l->getTileList();

            for (int x = 0; x < tiles.size(); x++)
            {
                gameObjectManager.Add("Tile" + (std::to_string(x)), tiles[x]);
               // std::cout << "Next Tile..." << std::endl;
            }

            gameObjectManager.Add("Background", l->getBackground());
            gameState = Playing;
            gameObjectManager.setCurLevel(l);
            break;
        }

        case Game::Playing:
        {
            if (gameObjectManager.Get("Bond")->GetPosition().y > 600) {
                gameObjectManager.Get("Bond")->SetPosition(200,200);
            }

            cameraPosition.x = gameObjectManager.Get("Bond")->GetPosition().x + 32 - (SCREEN_WIDTH / 2);
            cameraPosition.y = gameObjectManager.Get("Bond")->GetPosition().y - (SCREEN_HEIGHT);

            if (cameraPosition.x < 0)
                cameraPosition.x = 0;
            if (cameraPosition.y < 0)
                cameraPosition.y = 0;
            if (cameraPosition.x > LEVEL_WIDTH - SCREEN_WIDTH)
                cameraPosition.x = LEVEL_WIDTH - SCREEN_WIDTH;
            if (cameraPosition.y > LEVEL_HEIGHT)
                cameraPosition.y = LEVEL_HEIGHT;

            std::cout << "X: " << cameraPosition.x << std::endl;
            std::cout << "Y: " << cameraPosition.y << std::endl;

            view.reset(sf::FloatRect(cameraPosition.x, cameraPosition.y, SCREEN_WIDTH, SCREEN_HEIGHT));

            mainWindow.clear(sf::Color::Black);
            mainWindow.setView(view);

            gameObjectManager.UpdateAll();
            gameObjectManager.DrawAll(mainWindow);

            mainWindow.display();
            if (currentEvent.type == sf::Event::Closed) gameState = Game::Exiting;

            if (currentEvent.type == sf::Event::KeyPressed) {
                if (currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
            }

            break;
        }
    }
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
            gameState = Loading;
            break;
    }
}

Game::GameState Game::gameState = Uninitialized;
sf::RenderWindow Game::mainWindow;
sf::View Game::view;
sf::Vector2f Game::cameraPosition;
GameObjectManager Game::gameObjectManager;
