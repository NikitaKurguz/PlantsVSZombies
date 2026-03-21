#include "ZombieRunner.h"
#include "Manager.h"

ZombieRunner::ZombieRunner(int row, sf::Vector2f position, GameField* field) :
    Zombie(row, position, "textures\\zombies\\Zombie_Runner.png", 100, 5, 20, { 0, 0, 365, 511 }, { 80, 130 }, 2, field),
    armor_hp(300), is_tex_ch1(false), is_tex_ch2(false)
{
    CheckTex("textures\\zombies\\ZombieBucket.png");
    if (!damaged_tex_1.loadFromFile("textures\\zombies\\Zombie_Runner1.png"))
    {
        std::cout << "ошибка загрузки текстуры 1 для зомби бегуна" << std::endl;
    }
    if (!damaged_tex_2.loadFromFile("textures\\zombies\\Zombie_Runner2.png"))
    {
        std::cout << "ошибка загрузки текстуры 2 для зомби бегуна" << std::endl;
    }
}

bool ZombieRunner::IsCollision(Object* other) const
{
    if (is_jumping) return false;

    if (other->GetType() == CollisionObject::Plant)
    {
        if (!has_jumped && other->Get_row() == row)
        {
            return false;
        }
        if (other->GetID() == targetID)
        {
            return false;
        }
    }

    return Zombie::IsCollision(other);
}

void ZombieRunner::SendMessage(Message* m)
{
    if (m->type == MessageType::Collision)
    {
        if (is_jumping) return;

        if (m->collision.obj1 == this || m->collision.obj2 == this)
        {
            Object* other = (m->collision.obj1 == this)
                ? m->collision.obj2 : m->collision.obj1;

            if (other->GetType() == CollisionObject::Plant)
            {
                if (!has_jumped && other->Get_row() == row)
                {
                    StartJump(other->GetID());
                    return;
                }
                else if (other->GetID() != targetID && !is_jumping)
                {
                    StartAttack(other);
                }
            }

            if (other->GetType() == CollisionObject::LawnMower)
            {
                Manager::GetExemplar()->SendDeathMsg(this);
            }
        }
    }

    if (m->type == MessageType::Death)
    {
        if (m->death.death_object->GetID() == targetID)
        {
            StopAttack();
        }
    }

    if (m->type == MessageType::DealDamage)
    {
        if (m->deal_damage.target == this)
        {
            TakeDmg(m->deal_damage.damage_amount);
        }
    }
}

void ZombieRunner::StartJump(int plant_id)
{
    if (is_jumping || has_jumped) return;

    if (isAttacking)
    {
        StopAttack();
    }

    is_jumping = true;
    has_jumped = true;
    targetID = plant_id;
    jump_timer = 0;
    jump_start_x = position.x;
    jump_start_y = position.y;

    sprite.setColor(sf::Color(200, 200, 255));
}

void ZombieRunner::StopJump()
{
    is_jumping = false;
    jump_timer = 0;
    sprite.setColor(sf::Color::White);
}

void ZombieRunner::Update(float t)
{
    if (is_jumping)
    {
        jump_timer += t;

        float progress = jump_timer / jump_duration;

        if (progress >= 1.0f)
        {
            StopJump();
        }
        else
        {
            float x = jump_start_x - jump_distance * progress;
            float y = jump_start_y - jump_height * 4 * progress * (1 - progress);

            position.x = x;
            position.y = y;
        }

        Message* m = new Message;
        m->type = MessageType::Move;
        m->move.mover = this;
        m->move.new_pos = position;
        Manager::GetExemplar()->SendMessage(m);
    }
    else
    {
        Zombie::Update(t);
    }
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
            Zombie* normalZombie = new Zombie(row, position, Get_field());

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