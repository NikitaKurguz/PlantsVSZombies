#pragma once
#include "Plant.h"

class CherryBomb : public Plant
{
private:
    float explosion_delay = 2.0f;  // Задержка перед взрывом (в секундах)
    float timer = 0.0f;
    bool exploded = false;
    float explosion_radius = 150.0f;  // Радиус взрыва (в пикселях)

public:
    CherryBomb(int row, int col, sf::Vector2f pos, GameField* field);
    ~CherryBomb();

    void Update(float dt) override;
    void SendMessage(Message* m) override;

    // Вишневая бомба не стреляет
    void CreateProjectile(Object* target) override {}
    Object* FindTargetInRange() override { return nullptr; }

    void Explode();  // Взорваться
    void CheckForZombies();  // Проверить зомби поблизости
};

