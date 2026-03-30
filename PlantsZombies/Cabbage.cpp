#include "Cabbage.h"
#include "Manager.h"
#include "CabbageProjectile.h"

Cabbage::Cabbage(int row, int col, sf::Vector2f pos, GameField* field) :
    Plant(row, col, pos, "textures/plants/CabbagePult.png",
        100, 4000, 100, 20, 20, true, 
        { 0, 0, 1392, 1305 }, { 70, 80 }, field)
{
    CheckTex("textures/plants/CabbagePult.png");
}

void Cabbage::CreateProjectile(Object* target)
{
    if (!target) return;

    sf::Vector2f shoot_position = GetPosition();
    shoot_position.x += 30;
    shoot_position.y -= 70;  

    Manager::GetExemplar()->SendCreateMsg(
        new CabbageProjectile(shoot_position, Get_field(), GetDamage(), 35, GetID()));
}

Object* Cabbage::FindTargetInRange()
{
    Manager* mgr = Manager::GetExemplar();
    if (!mgr) return nullptr;

    Object* closest = nullptr;
    float minDistance = range;

    for (Object* obj : mgr->GetObjects())
    {
        if (!obj || !obj->isAlive) continue;
        if (obj->GetType() != CollisionObject::Zombie) continue;
        if (obj->Get_row() != Get_row()) continue;

        float dx = obj->GetPosition().x - GetPosition().x;
        if (dx <= 0 || dx > minDistance) continue;

        minDistance = dx;
        closest = obj;
    }
    return closest;
}