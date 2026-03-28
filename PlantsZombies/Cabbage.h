#pragma once
#include "Plant.h"

class Cabbage : public Plant
{
public:
    Cabbage(int row, int col, sf::Vector2f pos, GameField* field);
    void CreateProjectile(Object* target) override;
    Object* FindTargetInRange() override;
};