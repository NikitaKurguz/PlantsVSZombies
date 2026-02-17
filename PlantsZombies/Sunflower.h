#pragma once
#include "Plant.h"

class Sunflower : public Plant
{
private:
    float production_cooldown = 8.0f;  // Интервал производства солнышек
    float production_timer = 0.0f;

public:
    Sunflower(int row, int col, sf::Vector2f pos, GameField* field);
    ~Sunflower();

    void Update(float dt) override;
    void SendMessage(Message* m) override;
    void CreateProjectile(Object* target) override {}  // Подсолнух не стреляет
    Object* FindTargetInRange() override { return nullptr; }  // Не ищет цели

    void ProduceSun();
};