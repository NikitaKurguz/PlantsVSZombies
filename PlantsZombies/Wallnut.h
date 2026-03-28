#pragma once
#include "Plant.h"

class Wallnut : public Plant
{
public:
    Wallnut(int row, int col, sf::Vector2f pos, GameField* field);

    void CreateProjectile(Object* target) override {}
    Object* FindTargetInRange() override { return nullptr; }
};