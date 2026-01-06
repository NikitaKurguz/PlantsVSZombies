#include "ZombieBucket.h"
#include "Manager.h"
ZombieBucket::ZombieBucket(int row, sf::Vector2f position, GameField* field):
	Zombie(row, position, "textures\\zombies\\ZombieBucket.png", 100, 4, 20, {0, 0, 130, 227}, {80, 130}, field),
	bucket_hp(200)
{
	CheckTex("textures\\zombies\\ZombieBucket.png");
}

void ZombieBucket::SendMessage(Message* m)
{
	if (m->type == MessageType::Collision)
	{
		if (m->collision.obj1 == this || m->collision.obj2 == this)
		{
			Object* other = (m->collision.obj1 == this) ? m->collision.obj2 : m->collision.obj1;
			if (other->GetType() == CollisionObject::LawnMower)
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

void ZombieBucket::Update(float t)
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
