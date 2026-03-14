#pragma once
#include "Plant.h"

class Wallnut : public Plant
{
public:
    Wallnut(int row, int col, sf::Vector2f pos, GameField* field);
    ~Wallnut();

    void Update(float dt) override;
    void SendMessage(Message* m) override;
    void CreateProjectile(Object* target) override {}
    Object* FindTargetInRange() override { return nullptr; }
};