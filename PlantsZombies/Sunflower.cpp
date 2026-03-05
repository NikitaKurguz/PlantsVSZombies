#include "Sunflower.h"
#include "Manager.h"
#include "Sun.h"

Sunflower::Sunflower(int row, int col, sf::Vector2f pos, GameField* field) :
    Plant(row, col, pos, "textures\\plants\\SF.png",
        50, 0, 100, 0, 0, false, 
        { 0, 0, 1080, 1480 }, { 80, 80 }, field)
{
    CheckTex("textures\\plants\\SF.png");
}

Sunflower::~Sunflower()
{
}

void Sunflower::Update(float dt)
{
    Plant::Update(dt);  

    production_timer += dt;
    if (production_timer >= production_cooldown)
    {
        ProduceSun();
        production_timer = 0;
    }
}

void Sunflower::SendMessage(Message* m)
{
    Plant::SendMessage(m);
}

void Sunflower::ProduceSun()
{
    sf::Vector2f sun_pos = GetPosition();
    sun_pos.y -= 30;  

    Sun* sun = new Sun(sun_pos, Get_field(), 25, false);  
    Manager::GetExemplar()->SendCreateMsg(sun);
}