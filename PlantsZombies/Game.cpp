#include "Game.h"
#include "Collector.h"
#include "Sun.h"
#include <iostream>

Game::Game(): window(sf::VideoMode(1024, 600), "Plants vs Zombies")
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

    if (!gameOverScreen->Initialize())
    {
        std::cerr << "Warning: GameOverScreen failed to initialize!" << std::endl;
    }
    gameOverScreen->SetGameOverImage("textures/other/human.png");

    Collector* collector = new Collector(&field);
    manager->SendCreateMsg(collector);

    gameOver = false;
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
            for (auto* obj : manager->GetObjects())
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
    if (gameOver) return;

    level->Update(dt);
    sunManager->Update(dt);
    plantingInterface->Update(dt, window);
    manager->UpdateObjects(dt);

    if (manager->IsGameOver())
    {
        SetGameOver();
    }
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

    window.display();
}

void Game::Run()
{
    while (window.isOpen() && isRunning)
    {
        float dt = clock.restart().asSeconds() * 8;

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