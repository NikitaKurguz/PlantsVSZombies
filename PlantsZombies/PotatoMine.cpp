#include "PotatoMine.h"
#include "Manager.h"

PotatoMine::PotatoMine(int row, int col, sf::Vector2f pos, GameField* field) :
    Plant(row, col, pos, "textures/plants/PotatoMine.png",
        25, 0, 100, 150, 0, false,  
        { 0, 0, 539, 482 }, { 60, 60 }, field)  
{
    CheckTex("textures/plants/PotatoMine.png");
}


void PotatoMine::Update(float dt)
{
    Plant::Update(dt);

    timer += dt;
    if (timer >= activation_time)
    {
        is_armed = true;
    }
}

void PotatoMine::SendMessage(Message* m)
{
    Plant::SendMessage(m);
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
    Manager* mgr = Manager::GetExemplar();

    for (Object* obj : mgr->GetObjects())
    {
        if (!obj || !obj->isAlive) continue;
        if (obj->GetType() != CollisionObject::Zombie) continue;
        if (obj->Get_row() != row) continue;  

        float dx = obj->GetPosition().x - position.x;
        if (dx < 0) dx = -dx;
        if (dx <= blast_radius)
        {
            mgr->SendAttackMsg(this, obj, damage);
        }
    }

    field->ClearCell(row, col);
    mgr->SendDeathMsg(this);
}