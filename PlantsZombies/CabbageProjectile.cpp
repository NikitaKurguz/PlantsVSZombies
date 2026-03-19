#include "CabbageProjectile.h"
#include "Manager.h"
#include "Plant.h"

CabbageProjectile::CabbageProjectile(sf::Vector2f position, GameField* field,
    float damage, float speed, int shooterID) :
    Projectile(position, "textures/plants/Cabbage.png",  // Текстура капусты
        { 0, 0, 626, 626 }, { 50, 50 }, field, damage, speed, 800),
    shooterID(shooterID)
{
    CheckTex("textures/plants/Cabbage.png");
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