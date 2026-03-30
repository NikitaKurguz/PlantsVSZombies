#pragma once
#include "Plant.h"

class PotatoMine : public Plant
{
private:
    float activation_time = 5.0f;  
    float timer = 0.0f;
    bool is_armed = false;          // Взведена ли мина
    float blast_radius = 70.0f;     

public:
    PotatoMine(int row, int col, sf::Vector2f pos, GameField* field);

    void Update(float dt) override;
    void SendMessage(Message* m) override;

    void CreateProjectile(Object* target) override {}
    Object* FindTargetInRange() override { return nullptr; }

    void Explode();  
};