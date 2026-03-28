#include "CherryBomb.h"
#include "Manager.h"

CherryBomb::CherryBomb(int row, int col, sf::Vector2f pos, GameField* field) :
    Plant(row, col, pos, "textures/plants/CherryBomb.png",
        150, 0, 100, 150, 0, false,  
        { 0, 0, 920, 584 }, { 80, 80 }, field)
{
    CheckTex("textures/plants/CherryBomb.png");
}

void CherryBomb::Update(float dt)
{
    Plant::Update(dt);

    timer += dt;
    if (timer >= delay){Explode();}
}

void CherryBomb::Explode()
{
    if (exploded) return;
    exploded = true;

    Manager* mgr = Manager::GetExemplar();
    if (!mgr) return;

    const auto& objects = mgr->GetObjects();
    int zombies_hit = 0;

    for (Object* obj : objects)
    {
        if (!obj || !obj->isAlive) continue;
        if (obj->GetType() != CollisionObject::Zombie) continue;

        float dx = std::abs(obj->GetPosition().x - GetPosition().x);
        float dy = std::abs(obj->GetPosition().y - GetPosition().y);
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= explosion_radius)
        {
            mgr->SendAttackMsg(this, obj, damage);
            zombies_hit++;
        }
    }
    if (field) field->ClearCell(row, col);
    mgr->SendDeathMsg(this);
}