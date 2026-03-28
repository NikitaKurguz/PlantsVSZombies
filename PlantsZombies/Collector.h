#pragma once
#include "Object.h"

// Невидимый объект для сбора солнышек по клику
class Collector : public Object
{
public:
    Collector(GameField* field);

    void Update(float dt) override;
    void SendMessage(Message* m) override;
    bool IsCollision(Object* other) const override;
    CollisionObject GetType() const override { return CollisionObject::Collector; }
    void UpdatePosition(const sf::RenderWindow& window);
};