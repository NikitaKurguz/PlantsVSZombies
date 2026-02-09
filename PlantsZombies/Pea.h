#pragma once
#include "Projectile.h"
class Plant;

class Pea : public Projectile
{
private:
    int shooterID = -1;

protected:
    void OnHit(Object* other) override;

public:
    Pea(sf::Vector2f position,
        GameField* field,
        float damage,
        float speed,
        int shooterID);
};


