#pragma once
#include "Plant.h"

class CherryBomb : public Plant
{
private:
    float delay = 2.0f;  // Задержка перед взрывом 
    float timer = 0.0f;
    bool exploded = false;
    float explosion_radius = 150.0f;  // Радиус взрыва

public:
    CherryBomb(int row, int col, sf::Vector2f pos, GameField* field);

    void Update(float dt) override;
    void Explode();  

    void CreateProjectile(Object* target) override {}
    Object* FindTargetInRange() override { return nullptr; }
};

