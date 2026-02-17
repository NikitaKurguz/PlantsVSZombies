#pragma once
#include "Object.h"

// Это будет виртуальный объект для курсора, собирающего солнышки
class Collector : public Object
{
private:
    sf::Vector2i mouse_position;

public:
    Collector(GameField* field);

    void Update(float dt) override;
    void SendMessage(Message* m) override;
    bool IsCollision(Object* other) const override;
    CollisionObject GetType() const override { return CollisionObject::Collector; }

    void SetMousePosition(const sf::Vector2i& pos) { mouse_position = pos; }
    void UpdatePosition(const sf::RenderWindow& window);
};