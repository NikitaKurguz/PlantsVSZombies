#include "Game.h"
#include "Collector.h"
#include "Sun.h"
#include <iostream>

Game::Game()
    : window(sf::VideoMode(1024, 600), "Plants vs Zombies")
{
    manager = Manager::GetExemplar();
    InitializeGame();
}
Game::~Game()
{
    Manager::GetExemplar()->KillIExemplar();
}

void Game::InitializeGame()
{
    level = std::make_unique<LevelManager>(&field, manager);
    sunManager = std::make_unique<SunManager>(&field);
    plantingInterface = std::make_unique<PlantingInterface>(&field, sunManager.get(), level.get());
    gameOverScreen = std::make_unique<GameOverWin>();
    winScreen = std::make_unique<WinScreen>();

    if (!gameOverScreen->Initialize())
    {
        std::cerr << "Warning: GameOverScreen failed to initialize!" << std::endl;
    }

    if (!winScreen->Initialize())
    {
        std::cerr << "Warning: WinScreen failed to initialize!" << std::endl;
    }

    gameOverScreen->SetGameOverImage("textures/other/Human.png");
    winScreen->SetWinImage("textures/other/Crow.png");

    gameOver = false;
    gameWin = false;
    manager->ResetGameFlags();
}

void Game::SetGameOverImage(const std::string& imagePath)
{
    if (gameOverScreen)
    {
        gameOverScreen->SetGameOverImage(imagePath);
    }
}

void Game::SetGameOverOverlayOpacity(int opacity)
{
    if (gameOverScreen)
    {
        gameOverScreen->SetOverlayOpacity(opacity);
    }
}

void Game::SetGameOverTextColor(const sf::Color& color)
{
    if (gameOverScreen)
    {
        gameOverScreen->SetTextColor(color);
    }
}

void Game::SetWinImage(const std::string& imagePath)
{
    if (winScreen)
    {
        winScreen->SetWinImage(imagePath);
    }
}

void Game::SetWinOverlayOpacity(int opacity)
{
    if (winScreen)
    {
        winScreen->SetOverlayOpacity(opacity);
    }
}

void Game::SetWinTextColor(const sf::Color& color)
{
    if (winScreen)
    {
        winScreen->SetTextColor(color);
    }
}

void Game::SetWinInfoColor(const sf::Color& color)
{
    if (winScreen)
    {
        winScreen->SetInfoColor(color);
    }
}

void Game::HandleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            isRunning = false;
        }

        if (gameOver)
        {
            gameOverScreen->HandleInput(event, window);
            continue;
        }

        if (gameWin)
        {
            winScreen->HandleInput(event, window);
            continue;
        }

        if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
            plantingInterface->HandleMouseMove(mousePos);
        }

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

            bool sun_clicked = false;
            std::vector<Object*> objectsCopy = manager->GetObjects();
            for (auto* obj : objectsCopy)
            {
                if (obj && obj->isAlive && obj->GetType() == CollisionObject::Sun)
                {
                    if (obj->GetHitBox().contains(window.mapPixelToCoords(mousePos)))
                    {
                        Sun* sun = dynamic_cast<Sun*>(obj);
                        if (sun)
                        {
                            sunManager->AddSun(sun->GetValue());
                            manager->SendDeathMsg(sun);
                            sun_clicked = true;
                            break;
                        }
                    }
                }
            }

            if (!sun_clicked)
            {
                plantingInterface->HandleMouseClick(mousePos, window);
            }
        }
    }
}

void Game::Update(float dt)
{
    if (gameOver || gameWin) return;

    if (level->GetCurrentWave() >= level->GetTotalWaves())
    {
        bool zombiesAlive = false;
        const std::vector<Object*>& objects = manager->GetObjects();
        for (size_t i = 0; i < objects.size(); ++i)
        {
            Object* obj = objects[i];
            if (obj && obj->isAlive && obj->GetType() == CollisionObject::Zombie)
            {
                zombiesAlive = true;
                break;
            }
        }

        if (!zombiesAlive && !gameWin)
        {
            SetGameWin();
            return;
        }
    }

    if (manager->IsGameOver())
    {
        SetGameOver();
        return;
    }

    level->Update(dt);
    sunManager->Update(dt);
    plantingInterface->Update(dt, window);
    manager->UpdateObjects(dt);
}

void Game::Render()
{
    window.clear({ 255, 255, 255, 255 });

    field.Draw(window);
    manager->DrawObjects(window);
    sunManager->Draw(window);
    plantingInterface->Draw(window);

    if (gameOver)
    {
        gameOverScreen->Draw(window);
    }

    if (gameWin)
    {
        winScreen->Draw(window);
    }

    window.display();
}

void Game::Run()
{
    while (window.isOpen() && isRunning)
    {
        float dt = clock.restart().asSeconds() * 7;

        HandleEvents();
        Update(dt);
        Render();
    }
}

void Game::SetGameOver()
{
    gameOver = true;
    manager->StopGame();
}

void Game::SetGameWin()
{
    gameWin = true;
    manager->SetGameWin();
    if (winScreen)
    {
        winScreen->SetWinMessage("");
    }
}