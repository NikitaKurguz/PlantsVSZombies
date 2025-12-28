#include "Manager.h"
Manager* Manager::instance = nullptr;
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

Manager* Manager::GetInstance()
{
	if (instance == nullptr) instance = new Manager();
	return instance;
}

void Manager::KillInstance()
{
	if (instance) delete instance;
}
