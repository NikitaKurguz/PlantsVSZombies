#include "CabbageProjectile.h"
#include "Manager.h"
#include "Plant.h"
#include <cmath>

CabbageProjectile::CabbageProjectile(sf::Vector2f position, GameField* field,
    float damage, float speed, int shooterID) :
    Projectile(position, "textures/plants/Cabbage.png",  // Текстура капусты
        { 0, 0, 626, 626 }, { 50, 50 }, field, damage, speed, 800),
    shooterID(shooterID), start_y(position.y),
    elapsed_time(0), total_time(800.0f / speed)
{
    CheckTex("textures/plants/Cabbage.png");
}

void CabbageProjectile::Update(float dt)
{
    elapsed_time += dt;

    // Движение по горизонтали
    float x = GetPosition().x + speed * dt;

    // Параболическая траектория
    float t = elapsed_time / total_time;
    if (t > 1.0f) t = 1.0f;

    // arc = 4 * t * (1 - t) - это парабола с вершиной в середине (t=0.5, arc=1)
    float arc = 4 * t * (1 - t);
    float y = start_y - arc * 60;  // Поднимаемся на 60 пикселей

    Position({ x, y });

    traveled_distance += speed * dt;
    if (traveled_distance >= max_distance || elapsed_time >= total_time)
    {
        Manager::GetExemplar()->SendDeathMsg(this);
        return;
    }

    CheckFieldBounds();
}

void CabbageProjectile::OnHit(Object* other)
{
    if (other->GetType() != CollisionObject::Zombie)
        return;

    Manager::GetExemplar()->SendAttackMsg(this, other, damage);
    Manager::GetExemplar()->SendDeathMsg(this);

    if (shooterID >= 0)
    {
        Object* shooter = Manager::GetExemplar()->FindObjectByID(shooterID);
        if (shooter && shooter->GetType() == CollisionObject::Plant)
            static_cast<Plant*>(shooter)->OnProjectileDestroyed();
    }
}