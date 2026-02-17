#include <SFML/Graphics.hpp>
#include "Manager.h"
#include "Zombie.h"
#include "GameField.h"
#include "LevelManager.h"
#include "SunManager.h"
#include "Sunflower.h"
#include "Collector.h"
#include "Sun.h"  
#include <iostream>
#include <ctime>
using namespace std;
using namespace sf;

int main()
{
    srand(time(nullptr));
    system("chcp 1251 > nul");

    RenderWindow window(VideoMode(1024, 600), "Plants vs Zombies");

    GameField field;
    Manager* manager = Manager::GetExemplar();
    LevelManager level(&field, manager);
    SunManager sunManager(&field);

    // Создаем коллектор для сбора солнышек
    Collector* collector = new Collector(&field);
    manager->SendCreateMsg(collector);

    // Добавим тестовый подсолнух
    int sunflower_row = 2;
    int sunflower_col = 3;
    sf::Vector2f sunflowerPos = level.GetPlantPosition(sunflower_row, sunflower_col);
    Sunflower* sunflower = new Sunflower(sunflower_row, sunflower_col, sunflowerPos, &field);
    manager->SendCreateMsg(sunflower);

    Clock clock;

    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds() * 8;
        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            // Обработка кликов для сбора солнышек
            if (event.type == Event::MouseButtonPressed &&
                event.mouseButton.button == Mouse::Left)
            {
                // Обновляем позицию коллектора и проверяем коллизии
                collector->UpdatePosition(window);

                // Проверяем все объекты на коллизию с коллектором
                for (auto* obj : manager->GetObjects())
                {
                    if (obj && obj->isAlive && obj->GetType() == CollisionObject::Sun)
                    {
                        if (obj->GetHitBox().contains(
                            window.mapPixelToCoords(
                                Vector2i(event.mouseButton.x, event.mouseButton.y))))
                        {
                            // Собираем солнышко
                            Sun* sun = dynamic_cast<Sun*>(obj);
                            if (sun)
                            {
                                sunManager.AddSun(sun->GetValue());
                                manager->SendDeathMsg(sun);
                            }
                        }
                    }
                }
            }
        }

        level.Update(dt);
        sunManager.Update(dt);
        manager->UpdateObjects(dt);

        window.clear({ 255, 255, 255, 255 });
        field.Draw(window);
        manager->DrawObjects(window);
        sunManager.Draw(window);
        window.display();
    }

    Manager::GetExemplar()->KillIExemplar();
    return 0;
}