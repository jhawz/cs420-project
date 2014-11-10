#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "Enemy.h"
#include "Bond.h"
#include "VisibleGameObject.h"
#include "MapLoader.h"
#include "Tile.h"

void Game::Start(void)
{
	if(gameState != Uninitialized)
		return;
	
	mainWindow.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),"James Rambo: Revenge of WillFinger!");
	
	//mainWindow.SetFramerateLimit(60);
               sf::Texture text;
        MapLoader* m = new MapLoader();
        m->loadMap("data/Level1.txt");
        std::vector<std::string> testList = m->getTileCodes();
        text.loadFromFile("textures/TiledEight32New.png");
        for (int x = 0; x < testList.size(); x++)
        {
            Tile* newTile = new Tile();
            newTile->buildTile(std::stoi(testList[x]), text, 
                    sf::Vector2i(((std::stoi(testList[x]) - 1) % 15) * 32, 
                    ((std::stoi(testList[x]) - 1) / 15) * 32),
                sf::Vector2i(32, 32));
            newTile->SetPosition((x % 100) * 32, (x / 100) * 32);
            gameObjectManager.Add("Tile" + std::to_string(x), newTile);
        }
        delete m;
        Enemy *enemy_1 = new Enemy("actors.xml", "textures/enemy.png", "Pistol");
        enemy_1->SetPosition(400,400);
        
        Bond *bond = new Bond("actors.xml", "textures/JB.png");
        bond->SetPosition(200,200);
        bond->setBoundary(0, 0, 1024, 464);
        
        gameObjectManager.Add("Bond", bond);
        gameObjectManager.Add("Enemy", enemy_1);

	gameState= Game::ShowingSplash;

	while(!IsExiting())
	{
		GameLoop();
	}

	mainWindow.close();
}

bool Game::IsExiting()
{
	if(gameState == Game::Exiting) 
		return true;
	else 
		return false;
}


sf::RenderWindow& Game::GetWindow()
{
	return mainWindow;
}

const sf::Event& Game::GetInput() 
{
	sf::Event currentEvent;
	mainWindow.pollEvent(currentEvent);
	return currentEvent;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	mainWindow.pollEvent(currentEvent);
	
	switch(gameState)
	{
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
		case Game::Playing:
			{
				mainWindow.clear(sf::Color::White);

				gameObjectManager.UpdateAll();
				gameObjectManager.DrawAll(mainWindow);

				mainWindow.display();
				if(currentEvent.type == sf::Event::Closed) gameState = Game::Exiting;

				if(currentEvent.type == sf::Event::KeyPressed)
					{
						if(currentEvent.key.code == sf::Keyboard::Escape) ShowMenu();
					}

				break;
			}
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(mainWindow);
	gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(mainWindow);
	switch(result)
	{
		case MainMenu::Exit:
			gameState = Exiting;
			break;
		case MainMenu::Play:
			gameState = Playing;
			break;
	}
}

Game::GameState Game::gameState = Uninitialized;
sf::RenderWindow Game::mainWindow;
GameObjectManager Game::gameObjectManager;
