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
}

void Manager::UpdateObjects(float t)
{
	for (auto& obj : objects) 
		obj->Update(t);

	for (auto& m : messages) 
	{
		switch (m->type)
		{
		case MessageType::Death: {
			if (m->death.death_object) {
				auto del_obj = std::find(objects.begin(), objects.end(), m->death.death_object);
				delete* del_obj;
				objects.erase(del_obj);
			}
		}break;
		case MessageType::Create:
		{
			if (m->create.new_object)
				objects.push_back(m->create.new_object);
		}break;
		}
		if (m->type == MessageType::Move || m->type == MessageType::DealDamage)
		{
			for (auto& obj : objects)
				obj->SendMessage(m);
		}	
	}

}

void Manager::DrawObjects(sf::RenderWindow window)
{
	for (auto& obj : objects) 
		obj->Draw(window);
}

void Manager::SendMessage(Message* m)
{
	messages.push_back(m);
}
