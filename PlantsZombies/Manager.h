#pragma once
#include "Object.h"
#include "message.h"
#include <vector>
class Manager
{
private:
	static Manager* manager_exemplar;

	std::vector<Object*> objects;
	std::vector<Message*> messages;

	Manager();
	~Manager();
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
public:
	static Manager* GetExemplar();
	void KillIExemplar();

	void UpdateObjects(float t);
	void DrawObjects(sf::RenderWindow& window);
	void SendMessage(Message* m);
};

