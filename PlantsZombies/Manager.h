#pragma once
#include "Object.h"
#include "message.h"
#include <vector>
class Manager
{
private:
	static Manager* instance;

	std::vector<Object*> objects;
	std::vector<Message*> messages;

	Manager();
	~Manager();
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
public:
	static Manager* GetInstance();
	void KillInstance();
};

