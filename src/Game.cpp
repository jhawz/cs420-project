#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "Enemy.h"
#include "VisibleGameObject.h"

void Game::Start(void)
{
	if(gameState != Uninitialized)
		return;
	
	mainWindow.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),"Pang!");
	
	//mainWindow.SetFramerateLimit(60);

//	PlayerPaddle *player1 = new PlayerPaddle();
//	player1->SetPosition((SCREEN_WIDTH/2),700);
//
//	GameBall *ball = new GameBall();
//	ball->SetPosition((SCREEN_WIDTH/2),(SCREEN_HEIGHT/2)-15);
	
//	gameObjectManager.Add("Paddle1",player1);
//	gameObjectManager.Add("Ball",ball);
        
        Enemy *enemy_1 = new Enemy();
        enemy_1->Load("textures/SpriteSheet.png");
        enemy_1->setPistol();
        enemy_1->SetPosition(100,100);
        enemy_1->rightRun();
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
				mainWindow.clear(sf::Color(0,0,0));

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