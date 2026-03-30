#pragma once
#include "Object.h"

class Sun : public Object
{
private:
    float lifetime = 150;        
    float life_timer = 0;
    float value = 25.0f;           
    bool is_falling = true;         
    float fall_speed = 10.0f;      
    int target_row = -1;           

public:
    Sun(sf::Vector2f position, GameField* field, float value = 25.0f, bool falling = true);

    void Update(float dt) override;
    void SendMessage(Message* m) override;
    bool IsCollision(Object* other) const override;
    CollisionObject GetType() const override { return CollisionObject::Sun; }

    float GetValue() const { return value; }
    void Collect();

    void SetTargetRow(int row) { target_row = row; }
    int GetTargetRow() const { return target_row; }
};