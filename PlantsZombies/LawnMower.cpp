#include "LawnMower.h"
#include "Manager.h"
float LawnMower::CalcMaxDist()
{
    GameField* field = Get_field();
    if (!field) return 600;
    return field->get_field_size().x * 1.1f;
}
LawnMower::LawnMower(sf::Vector2f pos, int row, GameField* field):
    Object(pos,"textures\\Lawn_mower\\mower.png", { 0, 0, 256, 208 },
        { 70, 55 }, field), velocity(200), row(row)
{
    max_dist = CalcMaxDist();
}


bool LawnMower::IsCollision(Object* other) const
{
    if (this->GetType() == CollisionObject::LawnMower &&
        other->GetType() == CollisionObject::Zombie)
    {
        if (this->Get_row() != other->Get_row()) return false;
        return this->GetHitBox().intersects(other->GetHitBox());
    }
    return false;
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