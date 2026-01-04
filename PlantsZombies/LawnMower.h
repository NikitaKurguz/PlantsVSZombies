#pragma once
#include "Object.h"
class GameField;
class LawnMower : public Object
{
private:
	bool isActivated = false;
	float velocity;
	int row;

	float max_dist = 600;
	float dist_covered = 0;
public:
	LawnMower(sf::Vector2f pos, int row);

	bool get_active_status() const { return isActivated; }
	float get_velocity() const { return velocity; }
	int get_row() const { return row; }
	CollisionObject GetType() const override { return CollisionObject::LawnMower; }

	void Activate();
	void SendMessage(Message* m) override;
	void Update(float dt) override;

};

