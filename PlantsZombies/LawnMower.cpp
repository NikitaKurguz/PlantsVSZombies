#include "LawnMower.h"
#include "Manager.h"
LawnMower::LawnMower(sf::Vector2f pos, int row)
    : Object(pos,
        "textures\\Lawn_mower\\mower.png",
        { 0, 0, 256, 208 },
        { 70, 55 }),
    velocity(300),
    row(row)
{
}


void LawnMower::Activate()
{
    isActivated = true;
}

void LawnMower::SendMessage(Message* m) 
{
    if (m->type == MessageType::Collision) {
        if (m->collision.obj1 == this || m->collision.obj2 == this)
        {
            Object* other = (m->collision.obj1 == this) ? m->collision.obj2 : m->collision.obj1;
            if (other->GetType() == CollisionObject::Zombie) Activate();
        }
    }
}

void LawnMower::Update(float dt)
{
    if (!isActivated) return; 
    Position({ GetPosition().x + velocity * dt, GetPosition().y });
    dist_covered += velocity * dt;
    if (dist_covered >= max_dist)
    {
        Message* death_msg = new Message;
        death_msg->type = MessageType::Death;
        death_msg->death.death_object = this;
        death_msg->death.killer = this;

        Manager::GetExemplar()->SendMessage(death_msg);
    }
    
}