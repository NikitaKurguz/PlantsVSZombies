#include "Wallnut.h"
#include "Manager.h"

Wallnut::Wallnut(int row, int col, sf::Vector2f pos, GameField* field) :
    Plant(row, col, pos, "textures/plants/Wallnut.png",
        50, 0, 400, 0, 0, false,  // cost=50, hp=400 
        { 0, 0, 490, 567 }, { 70, 80 }, field)
{
    CheckTex("textures/plants/Wallnut.png");
}

Wallnut::~Wallnut()
{
}

void Wallnut::Update(float dt)
{
    Plant::Update(dt);  
}

void Wallnut::SendMessage(Message* m)
{
    Plant::SendMessage(m);  
}

