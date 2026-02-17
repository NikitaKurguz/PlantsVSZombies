#include "SunManager.h"
#include "Manager.h"
#include "Sun.h"
#include <iostream>

SunManager::SunManager(GameField* field) : field(field), font_loaded(false)
{
    // Пытаемся загрузить шрифт
    font_loaded = font.loadFromFile("fonts/arial.ttf");
    if (font_loaded)
    {
        sun_text.setFont(font);
        sun_text.setCharacterSize(24);
        sun_text.setFillColor(sf::Color::Black);
        sun_text.setPosition(40, 10);
    }
}

SunManager::~SunManager()
{
}

void SunManager::Update(float dt)
{
    natural_spawn_timer += dt;
    if (natural_spawn_timer >= natural_spawn_delay)
    {
        SpawnNaturalSun();
        natural_spawn_timer = 0;
        natural_spawn_delay = 8.0f + (rand() % 5);
    }
}

void SunManager::Draw(sf::RenderWindow& window)
{
    // Иконка солнышка
    sf::CircleShape sun_icon(15);
    sun_icon.setFillColor(sf::Color::Yellow);
    sun_icon.setPosition(10, 10);
    window.draw(sun_icon);

    // Текст с количеством
    if (font_loaded)
    {
        sun_text.setString(std::to_string(sun_count));
        window.draw(sun_text);
    }
}

bool SunManager::SpendSun(int amount)
{
    if (sun_count >= amount)
    {
        sun_count -= amount;
        return true;
    }
    return false;
}

void SunManager::AddSun(int amount)
{
    sun_count += amount;
}

void SunManager::SpawnNaturalSun()
{
    if (!field) return;

    int row = rand() % field->get_rows();
    float x = field->get_field_origin().x +
        (rand() % static_cast<int>(field->get_field_size().x));

    sf::Vector2f pos(x, field->get_field_origin().y - 50);

    Sun* sun = new Sun(pos, field, 25, true);
    sun->SetTargetRow(row);

    Manager::GetExemplar()->SendCreateMsg(sun);
}