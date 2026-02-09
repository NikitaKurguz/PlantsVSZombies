#pragma once
#include "Object.h"

class Projectile : public Object
{
protected:
    float damage;
    float speed;
    float max_distance;
    float traveled_distance;
    sf::Vector2f direction;

private:
    void CheckFieldBounds();

protected:
    virtual void OnHit(Object* other) = 0;

public:
    Projectile(sf::Vector2f position,
        const std::string& texture_file,
        const sf::IntRect& texture_rect,
        sf::Vector2f size,
        GameField* field,
        float damage,
        float speed,
        float max_distance = 1000);

    virtual ~Projectile() = default;

    void Update(float dt) override;
    CollisionObject GetType() const override;
    bool IsCollision(Object* other) const override;
    void SendMessage(Message* m) override;
};
