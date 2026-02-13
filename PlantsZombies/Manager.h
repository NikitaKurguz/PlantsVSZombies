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
	const std::vector<Object*>& GetObjects() const { return objects; }
	void SendCreateMsg(Object* obj);
	void SendDeathMsg(Object* obj);
	void SendAttackMsg(Object* attacker, Object* target, float dmg);
	void CheckCollisions();
	Object* FindObjectByID(int id);
	void UpdateObjects(float t);
	void DrawObjects(sf::RenderWindow& window);
	void SendMessage(Message* m);
};

