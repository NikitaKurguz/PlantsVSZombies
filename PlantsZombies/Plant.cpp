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
    attack_timer(0), recharge_time(0)
{
    CheckTex(file_name);
}

Plant::~Plant()
{
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
    if (hp <= 0) {
        hp = 0;
        Manager* manager = Manager::GetExemplar();
        manager->SendDeathMsg(this);
    }
}

void Plant::TakeDmg(float dmg)
{
    if (hp <= 0) return;
    hp -= dmg;
    IsDeath();
}

void Plant::SendMessage(Message* m)
{
    if (m->type == MessageType::DealDamage)
    {
        if (m->deal_damage.target == this)
            TakeDmg(m->deal_damage.damage_amount);
    }

}
void Plant::Update(float t)
{
}

void Plant::Attack(float t)
{
    attack_timer += t;
    
}

Object* Plant::FindTargetInRange()
{
    return nullptr;
}
