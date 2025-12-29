#pragma once
#include "Object.h"
enum class MessageType { Create, Death, Move, DealDamage };
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
			Object* to_who;
			Object* by_whom;
		}deal_damage;
	};
};

