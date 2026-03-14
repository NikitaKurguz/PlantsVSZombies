#include "PotatoMine.h"
#include "Manager.h"

PotatoMine::PotatoMine(int row, int col, sf::Vector2f pos, GameField* field) :
    Plant(row, col, pos, "textures/plants/PotatoMine.png",
        25, 0, 100, 50, 0, false,  
        { 0, 0, 539, 482 }, { 60, 60 }, field)  
{
    CheckTex("textures/plants/PotatoMine.png");
}

PotatoMine::~PotatoMine()
{
}

void PotatoMine::Update(float dt)
{
    Plant::Update(dt);

    if (!is_armed)
    {
        timer += dt;
        if (timer >= activation_time)
        {
            is_armed = true;
        }
    }
}

void PotatoMine::SendMessage(Message* m)
{
    Plant::SendMessage(m);

    // Если взведены и столкнулись с зомби - взрываемся
    if (m->type == MessageType::Collision && is_armed)
    {
        if (m->collision.obj1 == this || m->collision.obj2 == this)
        {
            Object* other = (m->collision.obj1 == this) ? m->collision.obj2 : m->collision.obj1;
            if (other->GetType() == CollisionObject::Zombie)
            {
                Explode();
            }
        }
    }
}

void PotatoMine::Explode()
{
    // Находим всех зомби в радиусе и наносим урон
    Manager* mgr = Manager::GetExemplar();
    const auto& objects = mgr->GetObjects();

    for (Object* obj : objects)
    {
        if (!obj || !obj->isAlive) continue;
        if (obj->GetType() != CollisionObject::Zombie) continue;
        if (obj->Get_row() != row) continue;  // Только в том же ряду

        // Проверяем расстояние
        float dx = abs(obj->GetPosition().x - position.x);
        if (dx <= blast_radius)
        {
            mgr->SendAttackMsg(this, obj, damage);
        }
    }
    mgr->SendDeathMsg(this);
}