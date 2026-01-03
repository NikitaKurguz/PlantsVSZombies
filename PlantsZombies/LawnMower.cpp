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
        if (m->collisison.obj1 == this || m->collisison.obj2 == this)
            Activate();
    }
}

void LawnMower::Update(float dt)
{
    if (!isActivated) return;
    Position({ GetPosition().x + velocity * dt, GetPosition().y });
}