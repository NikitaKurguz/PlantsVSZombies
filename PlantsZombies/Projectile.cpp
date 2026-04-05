#include "Projectile.h"
#include "Manager.h"

Projectile::Projectile(sf::Vector2f position,
    const std::string& texture_file,
    const sf::IntRect& texture_rect,
    sf::Vector2f size,
    GameField* field,
    float damage,
    float speed,
    float max_distance)
    : Object(position, texture_file, texture_rect, size, field),
    damage(damage),
    speed(speed),
    max_distance(max_distance),
    traveled_distance(0.0f),
    direction(1.f, 0.f)
{
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Projectile::Update(float dt)
{
    sf::Vector2f old_pos = position;
    Position(position + direction * speed * dt);

    sf::Vector2f delta = position - old_pos;
    traveled_distance += std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (traveled_distance >= max_distance)
    {
        Manager::GetExemplar()->SendDeathMsg(this);
        return;
    }

    CheckFieldBounds();
}

void Projectile::CheckFieldBounds()
{
    auto* field = Get_field();
    if (!field) return;

    auto pos = GetPosition();
    auto origin = field->get_field_origin();
    auto size = field->get_field_size();

    if (pos.x < origin.x - 50 ||
        pos.x > origin.x + size.x + 50)
    {
        Manager::GetExemplar()->SendDeathMsg(this);
    }
}

CollisionObject Projectile::GetType() const
{
    return CollisionObject::Projectile;
}

bool Projectile::IsCollision(Object* other) const
{
    return other->GetType() == CollisionObject::Zombie &&
        GetHitBox().intersects(other->GetHitBox());
}

void Projectile::SendMessage(Message* m)
{
    if (m->type != MessageType::Collision) return;
    if (m->collision.obj1 != this && m->collision.obj2 != this) return;

    Object* other = (m->collision.obj1 == this)
        ? m->collision.obj2 : m->collision.obj1;

    OnHit(other);
}
