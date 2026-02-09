#include "Peashoter.h"
#include "Manager.h"
#include "Projectile.h"
#include "Pea.h"
#include <iostream> 

Peashoter::Peashoter(int row, int col, sf::Vector2f pos, GameField* field) :
    Plant(row, col, pos, "textures\\plants\\Peashoter.png", 100,                          
        field->get_field_size().x, 100, 40, 6, true,                    
        { 0, 0, 442, 426 }, { 70, 71 }, field)
{
}

Peashoter::~Peashoter()
{
}

void Peashoter::SendMessage(Message* m)
{
    Plant::SendMessage(m);
}

void Peashoter::Update(float t)
{
    Plant::Update(t); 
}

void Peashoter::CreateProjectile()
{
    sf::Vector2f shoot_position = GetPosition();
    shoot_position.x += 35;  
    shoot_position.y -= 50;  

    Pea* pea = new Pea(shoot_position, Get_field(), GetDamage(), 40, GetID());

    Manager::GetExemplar()->SendCreateMsg(pea);

}