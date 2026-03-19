#pragma once
#include "Projectile.h"

class CabbageProjectile : public Projectile
{
private:
    int shooterID = -1;

protected:
    void OnHit(Object* other) override;

public:
    CabbageProjectile(sf::Vector2f position,
        GameField* field,
        float damage,
        float speed,
        int shooterID);
};