#include "Manager.h"
Manager* Manager::manager_exemplar = nullptr;
Manager::Manager()
{
}

Manager::~Manager()
{
	for (auto& obj : objects) delete obj;
	objects.clear();

	for (auto& m : messages) delete m;
	messages.clear();
}

Manager* Manager::GetExemplar()
{
	if (manager_exemplar == nullptr) manager_exemplar = new Manager();
	return manager_exemplar;
}

void Manager::KillIExemplar()
{
	if (manager_exemplar) delete manager_exemplar;
	manager_exemplar = nullptr;
}

void Manager::SendCreateMsg(Object* obj)
{
	Message* msg = new Message;
	msg->type = MessageType::Create;
	msg->create.new_object = obj;
	SendMessage(msg);
}

void Manager::SendDeathMsg(Object* obj)
{
	Message* msg = new Message;
	msg->type = MessageType::Death;
	msg->death.death_object = obj;
	msg->death.killer = obj;
	SendMessage(msg);
}
void Manager::SendAttackMsg(Object* attacker, Object* target, float dmg) {
	Message* msg = new Message;
	msg->type = MessageType::DealDamage;
	msg->deal_damage.attacker = attacker;
	msg->deal_damage.target = target;
	msg->deal_damage.damage_amount = dmg;
	SendMessage(msg);
}

void Manager::CheckCollisions()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (!objects[i] || !objects[i]->isAlive) continue;

		for (size_t j = i + 1; j < objects.size(); j++)
		{
			if (!objects[j] || !objects[j]->isAlive) continue;

			if (objects[i]->IsCollision(objects[j]))
			{
				Message* collision_msg = new Message;
				collision_msg->type = MessageType::Collision;
				collision_msg->collision.obj1 = objects[i];
				collision_msg->collision.obj2 = objects[j];
				SendMessage(collision_msg);
			}
		}
	}
}

Object* Manager::FindObjectByID(int id)
{
	for (auto* obj : objects)
	{
		if (obj && obj->GetID() == id && obj->isAlive)
			return obj;
	}
	return nullptr;
}


void Manager::UpdateObjects(float t)
{
	for (auto& obj : objects) 
		obj->Update(t);
	CheckCollisions();
	while(!(messages.empty()))
	{
		Message* m = messages.front();
		messages.erase(messages.begin());
		switch (m->type)
		{
		case MessageType::Death:
		{
			Object* obj = m->death.death_object;
			if (!obj) break;
			if (std::find(remove_objs.begin(), remove_objs.end(), obj) == remove_objs.end())
			{
				remove_objs.push_back(obj);
			}
		}
		break;
		case MessageType::Create:
		{
			if (m->create.new_object)
				objects.push_back(m->create.new_object);
		}break;
		}
		if (m->type == MessageType::Move || m->type == MessageType::DealDamage 
			|| m->type == MessageType::Collision)
		{
			for (auto& obj : objects)
			{
				if (!obj) continue;
				if (!obj->isAlive) continue;
				obj->SendMessage(m);
			}
		}
		delete m;
	}
	for (auto del_obj : remove_objs)
	{
		auto it = std::find(objects.begin(), objects.end(), del_obj);
		if (it != objects.end())
		{
			delete* it;
			objects.erase(it);
		}
		
	}
	remove_objs.clear();

}

void Manager::DrawObjects(sf::RenderWindow& window)
{
	for (auto& obj : objects) 
		obj->Draw(window);
}

void Manager::SendMessage(Message* m)
{
	messages.push_back(m);
}
