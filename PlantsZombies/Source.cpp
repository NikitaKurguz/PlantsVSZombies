#include <SFML/Graphics.hpp>
#include "Manager.h"
#include "GameField.h"
#include "LevelManager.h"
#include "SunManager.h"
#include "PlantingInterface.h"
#include "Collector.h"    
#include "Sun.h" 
#include <iostream>
#include <ctime>

int main()
{
    srand(time(nullptr));
    system("chcp 1251 > nul");

    sf::RenderWindow window(sf::VideoMode(1024, 600), "Plants vs Zombies");

    GameField field;
    Manager* manager = Manager::GetExemplar();
    LevelManager level(&field, manager);
    SunManager sunManager(&field);
    PlantingInterface plantingInterface(&field, &sunManager, &level);

    Collector* collector = new Collector(&field);
    manager->SendCreateMsg(collector);

    sf::Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds() * 8;
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Обработка движения мыши для интерфейса
            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i mousePos(event.mouseMove.x, event.mouseMove.y);
                plantingInterface.HandleMouseMove(mousePos);
            }

            // Обработка кликов мыши
            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);

                // Сначала проверяем клик по солнышкам
                bool sun_clicked = false;
                for (auto* obj : manager->GetObjects())
                {
                    if (obj && obj->isAlive && obj->GetType() == CollisionObject::Sun)
                    {
                        if (obj->GetHitBox().contains(
                            window.mapPixelToCoords(mousePos)))
                        {
                            Sun* sun = dynamic_cast<Sun*>(obj);
                            if (sun)
                            {
                                sunManager.AddSun(sun->GetValue());
                                manager->SendDeathMsg(sun);
                                sun_clicked = true;
                                break;
                            }
                        }
                    }
                }

                // Если не кликнули по солнышку, передаем обработку интерфейсу посадки
                if (!sun_clicked)
                {
                    plantingInterface.HandleMouseClick(mousePos, window);
                }
            }
        }

        // Обновление
        level.Update(dt);
        sunManager.Update(dt);
        plantingInterface.Update(dt, window);
        manager->UpdateObjects(dt);

        // Отрисовка
        window.clear({ 255, 255, 255, 255 });
        field.Draw(window);
        manager->DrawObjects(window);
        sunManager.Draw(window);
        plantingInterface.Draw(window);
        window.display();
    }

    Manager::GetExemplar()->KillIExemplar();
    return 0;
}