#include "LawnMower.h"
#include "GameField.h"

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

void LawnMower::SendMessage(Message* m) {}

void LawnMower::Update(float dt)
{
    if (!isActivated) return;
    Position({ GetPosition().x + velocity * dt, GetPosition().y });
}