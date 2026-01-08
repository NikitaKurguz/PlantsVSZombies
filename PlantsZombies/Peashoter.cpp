#include "Peashoter.h"
#include "Manager.h"
#include "Projectile.h"
#include <iostream> // для отладки

Peashoter::Peashoter(int row, int col, sf::Vector2f pos, GameField* field) :
    Plant(row, col, pos,
        "textures\\plants\\Peashoter.png",
        100,                          // cost
        field->get_field_size().x,    // range (полная ширина поля)
        100,                          // hp
        50,                           // damage
        1.5f,                         // attack_cooldown (1.5 секунды между выстрелами)
        true,                         // is_attack_type (ДА, это стреляющее растение!)
        { 0, 0, 442, 446 },             // rect
        { 70, 71 },                     // physical_size
        field)
{
    std::cout << "Peashoter created at [" << row << "," << col
        << "] position: " << pos.x << "," << pos.y << std::endl;
}

Peashoter::~Peashoter()
{
}

void Peashoter::SendMessage(Message* m)
{
    Plant::SendMessage(m);
}

void Peashoter::Update(float t)
{
    Plant::Update(t); // Вызываем базовый Update (там уже будет стрельба)
}

void Peashoter::CreateProjectile()
{
    std::cout << "Peashoter: Creating projectile!" << std::endl;

    // 1. Вычисляем позицию для выстрела
    // У Peashoter "рот" находится немного правее и выше центра
    sf::Vector2f shoot_position = GetPosition();
    shoot_position.x += 35.0f;  // Смещение вправо
    shoot_position.y -= 15.0f;  // Смещение вверх (чтобы стрелял из "рта")

    // 2. Создаем снаряд (горох)
    Projectile* pea = new Projectile(
        shoot_position,                     // Позиция выстрела
        "textures\\plants\\pea.png",   // Текстура гороха
        { 0, 0, 32, 32 },                     // Область текстуры
        { 25, 25 },                           // Размер на экране (25x25 пикселей)
        Get_field(),                        // Указатель на игровое поле
        GetDamage(),                        // Урон (50 единиц)
        400.0f,                             // Скорость полета
        800.0f                              // Максимальная дистанция
    );

    // 3. Отправляем сообщение о создании снаряда
    Message* create_msg = new Message();
    create_msg->type = MessageType::Create;
    create_msg->create.new_object = pea;

    Manager::GetExemplar()->SendMessage(create_msg);

    std::cout << "Pea projectile created at: "
        << shoot_position.x << ", " << shoot_position.y << std::endl;
}