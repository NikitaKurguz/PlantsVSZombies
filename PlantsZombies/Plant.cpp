#include "Plant.h"
#include "Manager.h"

Plant::Plant(int row, int col, sf::Vector2f position, const std::string& file_name,
    int cost, int range, float hp, float damage, float attack_cooldown, bool is_attack_type,
    const sf::IntRect& rect, sf::Vector2f physical_size, 
    GameField* field):
    Object(position, file_name, rect, physical_size, field),
    row(row), col(col), cost(cost), range(range), hp(hp), damage(damage),
    attack_cooldown(attack_cooldown), is_attack_type(is_attack_type),
    attack_timer(0)
{
    CheckTex(file_name);
}

Plant::~Plant(){}

void Plant::OnProjectileDestroyed()
{
    projectile_active = false;
}

bool Plant::IsCollision(Object* other) const
{
    if (other->GetType() == CollisionObject::Zombie)
    {
        if (this->Get_row() != other->Get_row()) return false;
        return this->GetHitBox().intersects(other->GetHitBox());
    }
    return false;
}

void Plant::TakeDmg(float dmg)
{
    if (hp <= 0) return;
    hp -= dmg;
    if (hp <= 0 && isAlive) { 
        isAlive = false;
        if (field) field->ClearCell(row, col);
        Manager::GetExemplar()->SendDeathMsg(this);
    }
}

void Plant::SendMessage(Message* m)
{
    if (m->type == MessageType::DealDamage)
    {
        if (m->deal_damage.target == this)
            TakeDmg(m->deal_damage.damage_amount);
    }
    if (m->type == MessageType::Death)
    {
        if (m->death.death_object->GetID() == targetID)
            StopAttack();
    }
}
void Plant::Update(float t)
{
    if (is_attack_type)
    attack_timer += t;

    Object* target = FindTargetInRange();
    if (!target)
        return;

    if (attack_timer >= attack_cooldown)
    {
        if (!projectile_active)
        {
            CreateProjectile(target);
            projectile_active = true;
            attack_timer = 0;
        }
    }
}

Object* Plant::GetTarget()
{
    if (targetID < 0) return nullptr;
    return Manager::GetExemplar()->FindObjectByID(targetID);
}

void Plant::StopAttack()
{
    isAttacking = false;
    targetID = -1;
    attack_timer = 0;
}

