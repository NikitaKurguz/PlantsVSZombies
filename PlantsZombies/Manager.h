#pragma once
#include "Object.h"
#include "Message.h"
#include <vector>
class Manager
{
private:
	static Manager* manager_exemplar;

	std::vector<Object*> objects;
	std::vector<Message*> messages;

	std::vector<Object*> remove_objs;

	Manager();
	~Manager();
	Manager(const Manager&) = delete;
	Manager& operator=(const Manager&) = delete;
public:
	static Manager* GetExemplar();
	void KillIExemplar();
	void SendCreateMsg(Object* obj);
	void SendDeathMsg(Object* obj);
	void CheckCollisions();
	void UpdateObjects(float t);
	void DrawObjects(sf::RenderWindow& window);
	void SendMessage(Message* m);
};

