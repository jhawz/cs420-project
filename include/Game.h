#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "GameObjectManager.h"
#include "Hud.h"
#include "Jaw.h"

class Game {
public:
    static void Start();
    static sf::RenderWindow& GetWindow();
    const static sf::Event& GetInput();
    const static int SCREEN_WIDTH = 800;
    const static int SCREEN_HEIGHT = 600;
    const static int LEVEL_WIDTH = 3200;
    const static int LEVEL_HEIGHT = 608;

private:
    static bool IsExiting();
    static void GameLoop();

    static void ShowSplashScreen();
    static void ShowMenu();
    static void ShowStoryScreen();
    static void LoadLevel();
    static void unLoadLevel();

    enum GameState {
        Uninitialized, ShowingSplash, Paused,
        ShowingMenu, Playing, Exiting, ShowingStory, Loading, Unloading
    };

    static GameState gameState;
    static sf::RenderWindow mainWindow;
    static sf::View view;
    static Hud hud;
    static sf::Vector2f cameraPosition;

    static GameObjectManager gameObjectManager;
};