#include "Zombie.h"
#include "Manager.h"

Zombie::Zombie(int row, sf::Vector2f position, const std::string& file_name, 
	float hp, float velocity, float damage, const sf::IntRect& rect, sf::Vector2f physical_size, GameField* field):
	Object(position, file_name, rect, physical_size, field), hp(hp), velocity(velocity), damage(damage), row(row)
{
	CheckTex(file_name);
}

Zombie::~Zombie()
{

}



bool Zombie::IsCollision(Object* other) const
{
	if (this->GetType() == CollisionObject::Zombie &&
		other->GetType() == CollisionObject::LawnMower) 
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

void Zombie::IsDeath()
{
	if (hp <= 0) {
		hp = 0;
		Message* death_msg = new Message;
		death_msg->type = MessageType::Death;
		death_msg->death.death_object = this;
		death_msg->death.killer = this;

		Manager* manager = Manager::GetExemplar();
		manager->SendMessage(death_msg);
	}
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
				Message* death_msg = new Message;
				death_msg->type = MessageType::Death;
				death_msg->death.death_object = this;
				death_msg->death.killer = other;
				Manager* manager = Manager::GetExemplar();
				manager->SendMessage(death_msg);
			}
		}
	}
	if (m->type == MessageType::DealDamage)
	{

	}
}

void Zombie::Update(float t)
{
	position.x -= t * velocity;
	if (position.x < 100)
	{
		Message* death_msg = new Message;
		death_msg->type = MessageType::Death;
		death_msg->death.death_object = this;
		death_msg->death.killer = this;

		Manager::GetExemplar()->SendMessage(death_msg);
		return;
	}
	Message* m = new Message;
	m->type = MessageType::Move;
	m->move.new_pos = position;
	m->move.mover = this;

	Manager::GetExemplar()->SendMessage(m);
}


