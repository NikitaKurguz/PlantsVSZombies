#include <SFML/Graphics.hpp>
#include "Manager.h"
#include "Zombie.h"
#include "GameField.h"
#include "LevelManager.h"
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
    Clock clock;
    
    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds() * 8;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        level.Update(dt);
        manager->UpdateObjects(dt);
        window.clear({255, 255, 255, 255});
        field.Draw(window);
        manager->DrawObjects(window);
        window.display();
    }

	return 0;
}