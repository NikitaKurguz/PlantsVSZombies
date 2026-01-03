#pragma once
#include "Object.h"
enum class MessageType { 
	Create, Death, Move, DealDamage, Collision
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
			sf::Vector2f old_pos;
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

