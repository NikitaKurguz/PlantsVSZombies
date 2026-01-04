#pragma once
#include "Object.h"
enum class MessageType { 
	Create, Death, Move, DealDamage, Collision
};
enum class CollisionObject {
	Plant, Zombie, LawnMower, Other
};
struct Message
{
	MessageType type;
	Object* Who_sender;
	union 
	{
		struct 
		{
			Object* new_object;
		}create;

		struct
		{
			Object* death_object;
			Object* killer;
		}death;

		struct
		{
			Object* mover;
			sf::Vector2f new_pos;
		}move;

		struct
		{
			float damage_amount;
			Object* target;
			Object* attacker;
		}deal_damage;
		struct
		{
			Object* obj1;
			Object* obj2;
		} collisison;
	};
	Message();
};

