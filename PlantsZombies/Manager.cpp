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

void Manager::CheckCollisions()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		for (size_t j = i + 1; j < objects.size(); j++)
		{
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
		case MessageType::Death: {
			if (m->death.death_object) 
				remove_objs.push_back(m->death.death_object);
			
		}break;
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
				obj->SendMessage(m);
		}
		delete m;
	}
	for (auto del_obj : remove_objs)
	{
		auto it = std::find(objects.begin(), objects.end(), del_obj);
		delete* it;
		objects.erase(it);
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
