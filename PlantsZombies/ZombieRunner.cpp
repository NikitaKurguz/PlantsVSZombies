#include "ZombieRunner.h"
#include "Manager.h"
ZombieRunner::ZombieRunner(int row, sf::Vector2f position, GameField* field) :
    Zombie(row, position, "textures\\zombies\\Zombie_Runner.png", 100, 7, 20, { 0, 0, 365, 511 }, { 80, 130 }, 2, field),
    armor_hp(300), is_tex_ch1(false), is_tex_ch2(false)
{
    CheckTex("textures\\zombies\\ZombieBucket.png");
    if (!damaged_tex_1.loadFromFile("textures\\zombies\\Zombie_Runner1.png"))
    {
        std::cout << "ошибка" << std::endl;
    }
    if (!damaged_tex_2.loadFromFile("textures\\zombies\\Zombie_Runner2.png"))
    {
        std::cout << "ошибка" << std::endl;
    }
}

void ZombieRunner::SendMessage(Message* m)
{
    Zombie::SendMessage(m);
}

void ZombieRunner::Update(float t)
{
    Zombie::Update(t);
}

void ZombieRunner::TakeDmg(float dmg_amount)
{
    if (armor_hp > 0)
    {
        armor_hp -= dmg_amount;

        if (armor_hp <= max_armor_hp * 2 / 3.0 && !is_tex_ch1)
        {
            sprite.setTexture(damaged_tex_1);
            sprite.setTextureRect({ 0, 0, 354, 512 });
            AutoScaling();

            is_tex_ch1 = true;
        }
        if (armor_hp <= max_armor_hp / 3.0 && !is_tex_ch2)
        {
            sprite.setTexture(damaged_tex_2);
            sprite.setTextureRect({ 0, 0, 329, 512 });
            AutoScaling();

            is_tex_ch2 = true;
        }

        if (armor_hp <= 0)
        {
            armor_hp = 0;
            Manager* manager = Manager::GetExemplar();

            Zombie* normalZombie = new Zombie(
                row, position, "textures\\zombies\\DefaultZombie.png",
                hp, 4, 20, { 0, 0, 274, 512 }, { 63, 120 }, 2, Get_field());

            manager->SendCreateMsg(normalZombie);
            manager->SendDeathMsg(this);
            return;
        }
    }
    else
        hp -= dmg_amount;

    IsDeath();
}


void ZombieRunner::IsDeath()
{
    if (hp <= 0) {
        hp = 0;
        Manager* manager = Manager::GetExemplar();
        manager->SendDeathMsg(this);
    }
}

