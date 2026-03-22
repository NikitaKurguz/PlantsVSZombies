#pragma once
#include "Projectile.h"

class CabbageProjectile : public Projectile
{
private:
    int shooterID = -1;
    float start_y;           // Начальная высота
    float elapsed_time;      // Время полета
    float total_time;

protected:
    void OnHit(Object* other) override;

public:
    CabbageProjectile(sf::Vector2f position,
        GameField* field,
        float damage,
        float speed,
        int shooterID);
    void Update(float dt) override;
};