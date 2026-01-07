#include "Zombie.h"
#include "Manager.h"
#include "Plant.h"

Zombie::Zombie(int row, sf::Vector2f position, const std::string& file_name,
	float hp, float velocity, float damage, const sf::IntRect& rect, sf::Vector2f physical_size, float attack_speed, GameField* field) :
	Object(position, file_name, rect, physical_size, field), hp(hp), velocity(velocity), damage(damage), row(row), attack_speed(attack_speed)
{
	CheckTex(file_name);
}

Zombie::~Zombie()
{

}

bool Zombie::IsCollision(Object* other) const
{
	if (other->GetType() == CollisionObject::LawnMower || 
		other->GetType() == CollisionObject::Plant)
	{
		if (this->Get_row() != other->Get_row()) return false;
		return this->GetHitBox().intersects(other->GetHitBox());
	}
		
	return false;
}

void Zombie::TakeDmg(float dmg_amount)
{
	if (hp <= 0) return;
	hp -= dmg_amount;
	IsDeath();
}

void Zombie::StartAttack(Object* plant)
{
	if (!plant || plant->GetType() != CollisionObject::Plant)
		return;
	sprite.setColor(sf::Color(255, 200, 200, 255));
	isAttacking = true; target = plant;
	attack_timer = 0;
}

void Zombie::StopAttack()
{
	isAttacking = false; target = nullptr; attack_timer = 0;
	sprite.setColor(sf::Color::White);
}

void Zombie::SendAttackToObject()
{
	if (!target || target->GetType() != CollisionObject::Plant)
	{
		StopAttack();
		return;
	}
	Manager::GetExemplar()->SendAttackMsg(this, target, this->damage);
}

void Zombie::IsDeath()
{
	if (hp <= 0) {
		hp = 0;
		Manager* manager = Manager::GetExemplar();
		manager->SendDeathMsg(this);
	}
}

void Zombie::Move(float t)
{
	if (!isAttacking)
		position.x -= t * velocity;
}

void Zombie::SendMessage(Message* m)
{
	if (m->type == MessageType::Collision)
	{
		if (m->collision.obj1 == this || m->collision.obj2 == this)
		{
			Object* other = (m->collision.obj1 == this) ? m->collision.obj2 : m->collision.obj1;
			if ( other->GetType() == CollisionObject::LawnMower)
			{
				Manager* manager = Manager::GetExemplar();
				manager->SendDeathMsg(this);
			}
			if (other->GetType() == CollisionObject::Plant)
			{
				StartAttack(other);
				
			}
		}
	}
	if (m->type == MessageType::Death) {
		if (m->death.death_object == target)
			StopAttack();
	}
	if (m->type == MessageType::DealDamage)
	{
		if (m->deal_damage.target == this)
			TakeDmg(m->deal_damage.damage_amount);
	}
}

void Zombie::Update(float t)
{
	if (isAttacking && target != nullptr)
	{
		attack_timer += t;
		if (attack_timer >=  attack_speed) {
			SendAttackToObject();
			attack_timer = 0;
		}
	}
	else
	{
		Move(t);
		if (position.x < 100) {
			Manager::GetExemplar()->SendDeathMsg(this);
			return;
		}

		Message* m = new Message;
		m->type = MessageType::Move;
		m->move.new_pos = position;
		m->move.mover = this;
		Manager::GetExemplar()->SendMessage(m);
	}
	
}


