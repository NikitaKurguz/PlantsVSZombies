#include <SFML/Graphics.hpp>
#include "Manager.h"
#include "Zombie.h"
#include "GameField.h"
#include "LevelManager.h"
#include <iostream>
using namespace std;
using namespace sf;
int main()
{
    system("chcp 1251 > nul");
	RenderWindow window(VideoMode(1024, 600), "Plants vs Zombies");

    GameField field;
    Manager* manager = Manager::GetExemplar();
    LevelManager level(&field, manager);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        level.Update(0.001);
        manager->UpdateObjects(0.001);
        window.clear({255, 255, 255, 255});
        field.Draw(window);
        manager->DrawObjects(window);
        window.display();
    }
	return 0;
}