#include "Projectile.h"
#include "Manager.h"
#include "Zombie.h"
#include <cmath>
#include "Plant.h"

sf::Vector2f Normalize(const sf::Vector2f& v)
{
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    if (length > 0.001f)
        return sf::Vector2f(v.x / length, v.y / length);
    return sf::Vector2f(1.0f, 0.0f); 
}

Projectile::Projectile(sf::Vector2f position,
    const std::string& texture_file,
    const sf::IntRect& texture_rect,
    sf::Vector2f size,
    GameField* field,
    float damage,
    float speed,
    Plant* shooter_plant,
    float max_distance)
    : Object(position, texture_file, texture_rect, size, field),
    damage(damage),
    speed(speed),
    max_distance(max_distance),
    traveled_distance(0.0f),
    direction(1.0f, 0.0f) ,
    shooter_plant(shooter_plant)

{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    AutoScalingEnabled = true;
}

Projectile::Projectile(const Projectile& other)
    : Object(other), 
    damage(other.damage),
    speed(other.speed),
    max_distance(other.max_distance),
    traveled_distance(other.traveled_distance),
    direction(other.direction),
    shooter_plant(other.shooter_plant)
{}

Projectile::~Projectile()
{}

void Projectile::Update(float dt)
{
    sf::Vector2f old_position = GetPosition();

    Position(GetPosition() + direction * speed * dt);

    sf::Vector2f movement = GetPosition() - old_position;
    traveled_distance += std::sqrt(movement.x * movement.x + movement.y * movement.y);

    if (HasReachedMaxDistance())
    {
        Message* msg = new Message();
        msg->type = MessageType::Death;
        msg->death.death_object = this;
        Manager::GetExemplar()->SendMessage(msg);
        return;
    }

    CheckFieldBounds();
}

void Projectile::CheckFieldBounds()
{
    GameField* field = Get_field();
    if (!field) return;

    sf::Vector2f field_origin = field->get_field_origin();
    sf::Vector2f field_size = field->get_field_size();

    float left_bound = field_origin.x - 50.0f;
    float right_bound = field_origin.x + field_size.x + 50.0f;
    float top_bound = field_origin.y - 50.0f;
    float bottom_bound = field_origin.y + field_size.y + 50.0f;

    sf::Vector2f current_pos = GetPosition();

    if (current_pos.x < left_bound ||
        current_pos.x > right_bound ||
        current_pos.y < top_bound ||
        current_pos.y > bottom_bound)
    {
        Message* msg = new Message();
        msg->type = MessageType::Death;
        msg->death.death_object = this;
        Manager::GetExemplar()->SendMessage(msg);
    }
}

CollisionObject Projectile::GetType() const
{
    return CollisionObject::Projectile;
}

bool Projectile::IsCollision(Object* other) const
{
    if (other->GetType() != CollisionObject::Zombie)
        return false;

    return GetHitBox().intersects(other->GetHitBox());
}

void Projectile::SendMessage(Message* m)
{
    switch (m->type)
    {
    case MessageType::Collision:
        HandleCollisionMessage(m);
        break;

    default:break;
    }
}

void Projectile::HandleCollisionMessage(Message* m)
{
    if (m->collision.obj1 != this && m->collision.obj2 != this)
        return;

    Object* other = (m->collision.obj1 == this) ?
        m->collision.obj2 : m->collision.obj1;

    if (other->GetType() == CollisionObject::Zombie)
    {
        Message* damage_msg = new Message();
        damage_msg->type = MessageType::DealDamage;
        damage_msg->deal_damage.target = other;
        damage_msg->deal_damage.damage_amount = damage;
        damage_msg->deal_damage.attacker = this;
        Manager::GetExemplar()->SendMessage(damage_msg);

        if (shooter_plant)
        {
            shooter_plant->SetCanShoot(true);
            std::cout << " Would unlock plant here" << std::endl;
        }

        Message* death_msg = new Message();
        death_msg->type = MessageType::Death;
        death_msg->death.death_object = this;
        Manager::GetExemplar()->SendMessage(death_msg);


    }
}