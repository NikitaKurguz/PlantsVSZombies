#include "Zombie.h"
#include "GameField.h"
#include "Manager.h"

Zombie::Zombie(int row, sf::Vector2f position, const std::string& file_name, 
	float hp, float velocity, float damage, const sf::IntRect& rect, sf::Vector2f physical_size):
	Object(position, file_name, rect, physical_size), hp(hp), velocity(velocity), damage(damage), row(row)
{
	CheckTex(file_name);
}

Zombie::~Zombie()
{
}



void Zombie::SendMessage(Message* m)
{
	if (m->type == MessageType::Collision)
	{
		if (m->collisison.obj1 == this || m->collisison.obj2 == this)
		{
			 Object* other = (m->collisison.obj1 == this) ? m->collisison.obj2 : m->collisison.obj1;
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
}

void Zombie::Update(float t)
{
	position.x -= t * velocity;

	Message* m = new Message;
	m->type = MessageType::Move;
	m->move.new_pos = position;
	m->move.mover = this;
}


