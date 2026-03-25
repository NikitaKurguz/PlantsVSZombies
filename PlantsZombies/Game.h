#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameField.h"
#include "Manager.h"
#include "LevelManager.h"
#include "SunManager.h"
#include "PlantingInterface.h"
#include "GameOverWin.h"

class Game
{
private:
    sf::RenderWindow window;
    sf::Clock clock;

    GameField field;
    Manager* manager;
    std::unique_ptr<LevelManager> level;
    std::unique_ptr<SunManager> sunManager;
    std::unique_ptr<PlantingInterface> plantingInterface;
    std::unique_ptr<GameOverWin> gameOverScreen;

    bool isRunning = true;
    bool gameOver = false;

    void HandleEvents();
    void Update(float dt);
    void Render();
    void InitializeGame();

public:
    Game();
    ~Game();
    void Run();

    void SetGameOver();

    void SetGameOverImage(const std::string& imagePath);
    void SetGameOverOverlayOpacity(int opacity);
    void SetGameOverTextColor(const sf::Color& color);
};