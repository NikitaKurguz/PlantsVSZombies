#include <SFML/Graphics.hpp>
#include "Manager.h"
#include "Zombie.h"
#include "GameField.h"
#include <iostream>
using namespace std;
using namespace sf;
int main()
{
    system("chcp 1251 > nul");
	RenderWindow window(VideoMode(1400, 600), "Plants vs Zombies");
    GameField field;

    Manager* manager = Manager::GetExemplar();
    Message* msg = new Message;
    msg->type = MessageType::Create;
    msg->create.new_object = new Zombie();
    manager->SendMessage(msg);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        manager->UpdateObjects(0.001);
        window.clear({255, 255, 255, 255});
        field.Draw(window);
        manager->DrawObjects(window);
        window.display();
    }
	return 0;
}