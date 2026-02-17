#pragma once
#include <SFML/Graphics.hpp>
#include "GameField.h"

class SunManager
{
private:
    int sun_count = 150;
    float natural_spawn_timer = 0.0f;
    float natural_spawn_delay = 10.0f;
    GameField* field;

    // Добавьте эти поля для отображения
    sf::Font font;
    sf::Text sun_text;
    bool font_loaded;

public:
    SunManager(GameField* field);
    ~SunManager();

    void Update(float dt);
    void Draw(sf::RenderWindow& window);

    bool SpendSun(int amount);
    void AddSun(int amount);
    int GetSunCount() const { return sun_count; }

    void SpawnNaturalSun();
};