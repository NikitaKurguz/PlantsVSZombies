#include "Peashooter.h"
#include "Manager.h"
#include "PeaProjectile.h"

Peashooter::Peashooter(int row, int col, sf::Vector2f pos, GameField* field) :
    Plant(row, col, pos, "textures\\plants\\Peashoter.png",
        100,field->get_field_size().x, 100, 20, 15, true,                    
        { 0, 0, 442, 426 }, { 70, 71 }, field)
{
    CheckTex("textures\\plants\\Peashoter.png");
}

void Peashooter::CreateProjectile(Object* target)
{
    if (!target) return;

    sf::Vector2f shoot_position = GetPosition(); 
    shoot_position.x += 35; 
    shoot_position.y -= 50;

    Manager::GetExemplar()->SendCreateMsg(
        new Pea(shoot_position, Get_field(), GetDamage(), 40, GetID()));
}

Object* Peashooter::FindTargetInRange()
{
    Manager* mgr = Manager::GetExemplar();
    if (!mgr) return nullptr;

    Object* closest = nullptr;
    float minDistance = range;

    for (Object* obj : mgr->GetObjects())
    {
        if (!obj || !obj->isAlive) continue;
        if (obj->GetType() != CollisionObject::Zombie) continue;
        if (obj->Get_row() != Get_row())continue;

        float dx = obj->GetPosition().x - GetPosition().x;
        if (dx <= 0 || dx > minDistance) continue;

        minDistance = dx;
        closest = obj;
    }
    return closest;
}

