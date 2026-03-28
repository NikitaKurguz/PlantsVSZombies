#pragma once
#include "Plant.h"

class Sunflower : public Plant
{
private:
    float production_cooldown = 10;  
    float production_timer = 0;

public:
    Sunflower(int row, int col, sf::Vector2f pos, GameField* field);

    void Update(float dt) override;
    void CreateProjectile(Object* target) override {}  // Подсолнух не стреляет
    Object* FindTargetInRange() override { return nullptr; }  // Не ищет цели

    void ProduceSun();
};