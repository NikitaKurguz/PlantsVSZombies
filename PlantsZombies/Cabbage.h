#pragma once
#include "Plant.h"

class Cabbage : public Plant
{
public:
    Cabbage(int row, int col, sf::Vector2f pos, GameField* field);
    ~Cabbage();

    void SendMessage(Message* m) override;
    void Update(float t) override;
    void CreateProjectile(Object* target) override;
    Object* FindTargetInRange() override;
};