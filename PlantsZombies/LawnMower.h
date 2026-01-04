#pragma once
#include "Object.h"
class LawnMower : public Object
{
private:
	bool isActivated = false;
	float velocity;
	int row;

	float max_dist;
	float dist_covered = 0;
	float CalcMaxDist();
public:
	LawnMower(sf::Vector2f pos, int row, GameField* field);

	bool get_active_status() const { return isActivated; }
	float get_velocity() const { return velocity; }
	int Get_row() const override{ return row; }
	CollisionObject GetType() const override { return CollisionObject::LawnMower; }
	bool IsCollision(Object* other) const override;
	

	void Activate();
	void SendMessage(Message* m) override;
	void Update(float dt) override;

};

