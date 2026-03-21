#include "ZombieDancer.h"
#include "Manager.h"

float ZombieDancer::Get_x_pos(sf::Vector2f pos) const
{
    int n;
    float f_pos_x;
    n = rand() % 3;
    switch (n) 
    {
    case 0:
        f_pos_x = pos.x - 50; 
        break;
    case 1: 
        f_pos_x = pos.x;
        break;
    case 2:
        f_pos_x = pos.x + 50;
        break;
    }
    return f_pos_x;
}

ZombieDancer::ZombieDancer(int row, sf::Vector2f position, GameField* field) :
    Zombie(row, position, "textures\\zombies\\ZombieDancer.png", 150, 2, 25, { 0, 0, 322, 512 }, { 80, 130 }, 1.5f, field),
    has_summoned(false)
{
    CheckTex("textures\\zombies\\ZombieDancer.png");
    start_x = position.x;
}

void ZombieDancer::SendMessage(Message* m)
{
    Zombie::SendMessage(m);
}

void ZombieDancer::Update(float t)
{
    if (!has_summoned && !isAttacking)
    {
        float distance_traveled = start_x - position.x;

        if (distance_traveled >= summon_distance)
        {
            SummonZombies();
        }
    }

    Zombie::Update(t);
}

void ZombieDancer::SummonZombies()
{
    if (has_summoned) return;

    has_summoned = true;
    Manager* manager = Manager::GetExemplar();


    int row1, row2, row3, row4;
    std::vector<int> available_rows;
    for (int i = 0; i < 5; i++) {
        if (i != row) {
            available_rows.push_back(i);
        }
    }
    row1 = available_rows[2];
    row2 = available_rows[0];
    row3 = available_rows[1];
    row4 = available_rows[3];

    sf::Vector2f spawn_pos1 = GetZombieSpawnPosition(row1);
    sf::Vector2f spawn_pos2 = GetZombieSpawnPosition(row2);
    sf::Vector2f spawn_pos3 = GetZombieSpawnPosition(row3);
    sf::Vector2f spawn_pos4 = GetZombieSpawnPosition(row4);

    Zombie* z1 = new Zombie(row1, { Get_x_pos(position), spawn_pos1.y}, "textures\\zombies\\Zombie_Bunny.png",
        100, 3, 20, { 0, 0, 239, 512 }, { 55, 120 }, 1, Get_field());

    Zombie* z2 = new Zombie(row2, { Get_x_pos(position), spawn_pos2.y }, "textures\\zombies\\Zombie_Bunny.png",
        100, 3, 20, { 0, 0, 239, 512 }, { 55, 120 }, 1, Get_field());

    Zombie* z3 = new Zombie(row3, { Get_x_pos(position), spawn_pos3.y }, "textures\\zombies\\Zombie_Bunny.png",
        100, 3, 20, { 0, 0, 239, 512 }, { 55, 120 }, 1, Get_field());

    Zombie* z4 = new Zombie(row4, { Get_x_pos(position), spawn_pos4.y }, "textures\\zombies\\Zombie_Bunny.png",
        100, 3, 20, { 0, 0, 239, 512 }, { 55, 120 }, 1, Get_field());

    manager->SendCreateMsg(z1);
    manager->SendCreateMsg(z2);
    manager->SendCreateMsg(z3);
    manager->SendCreateMsg(z4);

    sprite.setColor(sf::Color(255, 200, 200));
}

void ZombieDancer::TakeDmg(float dmg_amount)
{
    Zombie::TakeDmg(dmg_amount);
}

void ZombieDancer::IsDeath()
{
    Zombie::IsDeath();
}