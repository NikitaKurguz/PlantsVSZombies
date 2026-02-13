#include "Plant.h"
#include "Manager.h"

void Plant::Update_attck_timer(float t)
{
}

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

Plant::~Plant()
{
}

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

void Plant::IsDeath()
{
    if (hp <= 0 && isAlive) {
        isAlive = false;
        Manager* manager = Manager::GetExemplar();
        manager->SendDeathMsg(this);
    }
}

void Plant::TakeDmg(float dmg)
{
    if (hp <= 0) return;
    hp -= dmg;
    sprite.setColor(sf::Color(255, 150, 150, 255));
    IsDeath();
}

void Plant::SendMessage(Message* m)
{
    if (m->type == MessageType::DealDamage)
    {
        if (m->deal_damage.target == this)
            TakeDmg(m->deal_damage.damage_amount);
    }
    if (m->type == MessageType::Collision)
    {
        if (m->collision.obj1 == this || m->collision.obj2 == this)
        {
            Object* other = (m->collision.obj1 == this) ? m->collision.obj2 : m->collision.obj1;
            if (other->GetType() == CollisionObject::Zombie)
            {

            }
        }
    }
    if (m->type == MessageType::Death)
    {
        if (m->death.death_object->GetID() == targetID)
            StopAttack();
    }


}
void Plant::Update(float t)
{
    if (sprite.getColor() != sf::Color::White)
    {
        color_timer += t;
        if (color_timer >= 0.1)
        {
            sprite.setColor(sf::Color::White);
            color_timer = 0;
        }
    }

    if (is_attack_type)
        Attack(t);
}


void Plant::Attack(float t)
{
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

void Plant::StartAttack(Object* target)
{
    if (!target || !target->isAlive) return;

    targetID = target->GetID();
    isAttacking = true;
    attack_timer = 0;
}

void Plant::StopAttack()
{
    isAttacking = false;
    targetID = -1;
    attack_timer = 0;
}

