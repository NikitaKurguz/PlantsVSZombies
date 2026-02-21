#include "Sun.h"
#include "Manager.h"

Sun::Sun(sf::Vector2f position, GameField* field, float value, bool falling) :
    Object(position, "textures/plants/Sun.png",
        { 0, 0, 800, 800 }, { 40, 40 }, field),
    value(value), is_falling(falling), life_timer(0), lifetime(10.0f)
{
    CheckTex("textures/plants/Sun.png");
}

void Sun::Update(float dt)
{
    if (is_falling)
    {
        // Падаем вниз
        Position({ GetPosition().x, GetPosition().y + fall_speed * dt });

        // Проверяем, не достигли ли уровня земли
        if (field)
        {
            float ground_y = field->get_field_origin().y +
                (target_row + 1) * field->get_cell_size().y;

            if (GetPosition().y >= ground_y)
            {
                is_falling = false;
                Position({ GetPosition().x, ground_y });
            }
        }
    }

    // Таймер жизни
    life_timer += dt;
    if (life_timer >= lifetime)
    {
        Manager::GetExemplar()->SendDeathMsg(this);
    }

    // Анимация мерцания перед исчезновением
    if (lifetime - life_timer < 2.0f)
    {
        float alpha = 255 * (1.0f - (life_timer - (lifetime - 2.0f)) / 2.0f);
        sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
    }
}

void Sun::SendMessage(Message* m)
{
    if (m->type == MessageType::Collision)
    {
        if (m->collision.obj1 == this || m->collision.obj2 == this)
        {
            Object* other = (m->collision.obj1 == this) ? m->collision.obj2 : m->collision.obj1;
            if (other->GetType() == CollisionObject::Collector)
            {
                Collect();
            }
        }
    }
}

bool Sun::IsCollision(Object* other) const
{
    return other->GetType() == CollisionObject::Collector &&
        GetHitBox().intersects(other->GetHitBox());
}

void Sun::Collect()
{
    Manager::GetExemplar()->SendDeathMsg(this);
    // Здесь будет добавление солнышек игроку
}