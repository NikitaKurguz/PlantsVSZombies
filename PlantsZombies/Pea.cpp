#include "Pea.h"
#include "Manager.h"
#include "Plant.h"

Pea::Pea(sf::Vector2f position,
    GameField* field,
    float damage,
    float speed,
    int shooterID)
    : Projectile(position,
        "textures\\plants\\pea2.png",
        { 0, 0, 1152, 720 },
        { 80, 45 },
        field,
        damage,
        speed,
        800.f),
    shooterID(shooterID)
{
}

void Pea::OnHit(Object* other)
{
    if (other->GetType() != CollisionObject::Zombie)
        return;

    Manager::GetExemplar()->SendAttackMsg(this, other, damage);
    Manager::GetExemplar()->SendDeathMsg(this);

    if (shooterID >= 0)
    {
        Object* shooter = Manager::GetExemplar()->FindObjectByID(shooterID);
        if (shooter && shooter->GetType() == CollisionObject::Plant)
        {
            static_cast<Plant*>(shooter)->SetCanShoot(true);
        }
    }
}
