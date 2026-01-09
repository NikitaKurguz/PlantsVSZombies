#pragma once
#include "Object.h"
class Plant;

class Projectile : public Object
{
protected:
    float damage;           
    float speed;           
    float max_distance;    
    float traveled_distance; 

    sf::Vector2f direction; 
    Plant* shooter_plant;

private:
    void CheckFieldBounds(); 
    void HandleCollisionMessage(Message* m); 

public:
    Projectile(sf::Vector2f position,
        const std::string& texture_file,
        const sf::IntRect& texture_rect,
        sf::Vector2f size,
        GameField* field,
        float damage,
        float speed,
        Plant* shooter_plant = nullptr,
        float max_distance = 1000.0f);

    Projectile(const Projectile& other);

    virtual ~Projectile();

    virtual void Update(float dt) override;
    virtual CollisionObject GetType() const override;
    virtual bool IsCollision(Object* other) const override;
    virtual void SendMessage(Message* m) override;

    float GetDamage() const { return damage; }
    float GetSpeed() const { return speed; }
    float GetTraveledDistance() const { return traveled_distance; }
    bool HasReachedMaxDistance() const { return traveled_distance >= max_distance; }
    Plant* GetShooterPlant() const { return shooter_plant; }
};