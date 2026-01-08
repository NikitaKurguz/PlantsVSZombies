#include "Projectile.h"
#include "Manager.h"
#include "Zombie.h"
#include <cmath>

// Вспомогательная функция для нормализации вектора
sf::Vector2f Normalize(const sf::Vector2f& v)
{
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    if (length > 0.001f)
        return sf::Vector2f(v.x / length, v.y / length);
    return sf::Vector2f(1.0f, 0.0f); // По умолчанию вправо
}

// Конструктор
Projectile::Projectile(sf::Vector2f position,
    const std::string& texture_file,
    const sf::IntRect& texture_rect,
    sf::Vector2f size,
    GameField* field,
    float damage,
    float speed,
    float max_distance)
    // Вызываем конструктор базового класса Object
    : Object(position, texture_file, texture_rect, size, field),
    damage(damage),
    speed(speed),
    max_distance(max_distance),
    traveled_distance(0.0f),
    direction(1.0f, 0.0f) // По умолчанию летим вправо
{
    // Для снарядов центр спрайта обычно в середине
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);

    // Можно настроить автоскейлинг
    AutoScalingEnabled = true;
}

// Конструктор копирования
Projectile::Projectile(const Projectile& other)
    : Object(other), // Копируем базовую часть
    damage(other.damage),
    speed(other.speed),
    max_distance(other.max_distance),
    traveled_distance(other.traveled_distance),
    direction(other.direction)
{
    // Все поля уже скопированы в списке инициализации
}

// Деструктор
Projectile::~Projectile()
{
    // Деструктор Object вызовется автоматически
}

// Основной метод обновления
void Projectile::Update(float dt)
{
    // 1. Двигаем снаряд
    // Сохраняем старую позицию для расчета пройденной дистанции
    sf::Vector2f old_position = GetPosition();

    // Обновляем позицию: позиция = позиция + направление * скорость * время
    Position(GetPosition() + direction * speed * dt);

    // Вычисляем и добавляем пройденную дистанцию
    sf::Vector2f movement = GetPosition() - old_position;
    traveled_distance += std::sqrt(movement.x * movement.x + movement.y * movement.y);

    // 2. Проверяем, не превысили ли максимальную дистанцию
    if (HasReachedMaxDistance())
    {
        // Отправляем сообщение об уничтожении
        Message* msg = new Message();
        msg->type = MessageType::Death;
        msg->death.death_object = this;
        Manager::GetExemplar()->SendMessage(msg);
        return;
    }

    // 3. Проверяем, не вылетел ли за границы поля
    CheckFieldBounds();
}

// Проверка выхода за границы поля
void Projectile::CheckFieldBounds()
{
    GameField* field = Get_field();
    if (!field) return;

    sf::Vector2f field_origin = field->get_field_origin();
    sf::Vector2f field_size = field->get_field_size();

    // Границы поля с небольшим запасом
    float left_bound = field_origin.x - 50.0f;
    float right_bound = field_origin.x + field_size.x + 50.0f;
    float top_bound = field_origin.y - 50.0f;
    float bottom_bound = field_origin.y + field_size.y + 50.0f;

    // Текущая позиция снаряда
    sf::Vector2f current_pos = GetPosition();

    // Если снаряд вышел за границы - уничтожаем
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

// Возвращает тип объекта (снаряд)
CollisionObject Projectile::GetType() const
{
    return CollisionObject::Projectile;
}

// Проверка столкновения с другим объектом
bool Projectile::IsCollision(Object* other) const
{
    // Снаряд сталкивается только с зомби
    if (other->GetType() != CollisionObject::Zombie)
        return false;

    // Проверяем пересечение хитбоксов
    return GetHitBox().intersects(other->GetHitBox());
}

// Обработка входящих сообщений
void Projectile::SendMessage(Message* m)
{
    switch (m->type)
    {
    case MessageType::Collision:
        HandleCollisionMessage(m);
        break;

    default:
        // Игнорируем другие типы сообщений
        break;
    }
}

// Обработка сообщения о столкновении
void Projectile::HandleCollisionMessage(Message* m)
{
    // Проверяем, участвуем ли мы в этом столкновении
    if (m->collision.obj1 != this && m->collision.obj2 != this)
        return;

    // Определяем, с кем столкнулись
    Object* other = (m->collision.obj1 == this) ?
        m->collision.obj2 : m->collision.obj1;

    // Если столкнулись с зомби
    if (other->GetType() == CollisionObject::Zombie)
    {
        // 1. Наносим урон зомби
        Message* damage_msg = new Message();
        damage_msg->type = MessageType::DealDamage;
        damage_msg->deal_damage.target = other;
        damage_msg->deal_damage.damage_amount = damage;
        damage_msg->deal_damage.attacker = this;
        Manager::GetExemplar()->SendMessage(damage_msg);

        // 2. Уничтожаем снаряд
        Message* death_msg = new Message();
        death_msg->type = MessageType::Death;
        death_msg->death.death_object = this;
        Manager::GetExemplar()->SendMessage(death_msg);
    }
}