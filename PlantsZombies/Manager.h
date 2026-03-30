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
	bool game_over = false;
	bool game_stopped = false;
	bool game_win = false;

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
	void SetGameOver() { game_over = true; game_stopped = true; }
	void SetGameWin() { game_win = true; game_stopped = true; }
	bool IsGameOver() const { return game_over; }
	bool IsGameWin() const { return game_win; }
	bool IsGameStopped() const { return game_stopped; }
	void StopGame() { game_stopped = true; }
	void ResetGameFlags() { game_over = false; game_win = false; game_stopped = false; }
};