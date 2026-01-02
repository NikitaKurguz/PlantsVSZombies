#pragma once
#include "Object.h"
class GameField;
class LawnMower : public Object
{
private:
	bool isActivated = false;
	float velocity;
	int row;
public:
	LawnMower(sf::Vector2f pos, int row);

	bool get_active_status() const { return isActivated; }
	float get_velocity() const { return velocity; }
	int get_row() const { return row; }

	void Activate();
	void SendMessage(Message* m) override;
	void Update(float dt) override;

};

