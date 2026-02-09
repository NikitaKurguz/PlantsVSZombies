#include "ZombieBucket.h"
#include "Manager.h"
ZombieBucket::ZombieBucket(int row, sf::Vector2f position, GameField* field):
	Zombie(row, position, "textures\\zombies\\ZombieBucket.png", 100, 8, 20, {0, 0, 130, 227}, {80, 130}, 2, field),
	bucket_hp(200)
{
	CheckTex("textures\\zombies\\ZombieBucket.png");
}

void ZombieBucket::SendMessage(Message* m)
{
	Zombie::SendMessage(m);
}

void ZombieBucket::Update(float t)
{
	Zombie::Update(t);
}
