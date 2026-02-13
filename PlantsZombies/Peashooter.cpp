#include "Peashooter.h"
#include "Manager.h"
#include "Projectile.h"
#include "Pea.h"
#include <iostream> 

Peashooter::Peashooter(int row, int col, sf::Vector2f pos, GameField* field) :
    Plant(row, col, pos, "textures\\plants\\Peashoter.png", 100,                          
        field->get_field_size().x, 100, 40, 22, true,                    
        { 0, 0, 442, 426 }, { 70, 71 }, field)
{
}

Peashooter::~Peashooter()
{
}

void Peashooter::SendMessage(Message* m)
{
    Plant::SendMessage(m);
}

void Peashooter::Update(float t)
{
    Plant::Update(t); 
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

    const std::vector<Object*>& objects = mgr->GetObjects();

    Object* closest = nullptr;
    float minDistance = range;

    for (Object* obj : objects)
    {
        if (!obj) continue;
        if (!obj->isAlive) continue;

        if (obj->GetType() != CollisionObject::Zombie)
            continue;

        if (obj->Get_row() != Get_row())
            continue;

        float dx = obj->GetPosition().x - GetPosition().x;

        if (dx <= 0)
            continue;

        if (dx > minDistance)
            continue;

        minDistance = dx;
        closest = obj;
    }

    return closest;
}

