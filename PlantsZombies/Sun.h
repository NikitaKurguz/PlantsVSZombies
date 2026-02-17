#pragma once
#include "Object.h"

class Sun : public Object
{
private:
    float lifetime = 150.0f;        // Время жизни солнышка
    float life_timer = 0.0f;
    float value = 25.0f;            // Сколько солнышек дает
    bool is_falling = true;         // Падает ли с неба или от подсолнуха
    float fall_speed = 10.0f;       // Скорость падения
    int target_row = -1;             // Для какого ряда (если падает с неба)

public:
    Sun(sf::Vector2f position, GameField* field, float value = 25.0f, bool falling = true);

    void Update(float dt) override;
    void SendMessage(Message* m) override;
    bool IsCollision(Object* other) const override;
    CollisionObject GetType() const override { return CollisionObject::Sun; }

    float GetValue() const { return value; }
    void Collect();

    // Для падающих с неба солнышек
    void SetTargetRow(int row) { target_row = row; }
    int GetTargetRow() const { return target_row; }
};