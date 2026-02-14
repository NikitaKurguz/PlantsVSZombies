#include "ZombieBucket.h"
#include "Manager.h"
ZombieBucket::ZombieBucket(int row, sf::Vector2f position, GameField* field):
	Zombie(row, position, "textures\\zombies\\ZombieBucket.png", 100, 8, 20, {0, 0, 130, 227}, {80, 130}, 2, field),
	bucket_hp(100)
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

void ZombieBucket::TakeDmg(float dmg_amount)
{
    if (bucket_hp > 0)
    {
        bucket_hp -= dmg_amount;
        if (bucket_hp <= 0)
        {
            bucket_hp = 0;
            Manager* manager = Manager::GetExemplar();

            Zombie* normalZombie = new Zombie(
                row, position, "textures\\zombies\\DefaultZombie.png",
                hp, 8, 20, { 0, 0, 128, 205 }, { 80, 120 }, 2, Get_field());

            manager->SendCreateMsg(normalZombie);
            manager->SendDeathMsg(this);

            return;
        }
        if (bucket_hp <= max_bucket_hp / 2.0f)
        {

        }
    }
    else 
        hp -= dmg_amount;
    IsDeath();
}


void ZombieBucket::IsDeath()
{
	if (hp <= 0) {
		hp = 0;
		Manager* manager = Manager::GetExemplar();
		manager->SendDeathMsg(this);
	}
}

