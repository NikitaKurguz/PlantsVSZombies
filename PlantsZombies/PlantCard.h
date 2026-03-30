#pragma once
#include <SFML/Graphics.hpp>
#include "Plant.h"
#include "GameField.h"
#include "SunManager.h"

enum class PlantType {
    Peashooter,
    Sunflower,
    Wallnut,
    PotatoMine,
    Cabbage,
    CherryBomb
};

class PlantCard {
private:
    sf::RectangleShape background;
    sf::Sprite icon;
    sf::Text cooldown_text;

    PlantType type;
    int cost;
    float cooldown_time;
    float current_cooldown = 0;
    bool is_available = true;

    sf::Vector2f position;
    bool is_hovered = false;

    sf::Color normal_color = sf::Color(100, 100, 100, 200);
    sf::Color hover_color = sf::Color(150, 150, 150, 220);
    sf::Color unavailable_color = sf::Color(80, 80, 80, 150);

public:
    PlantCard(PlantType type, int cost, float cooldown,
        const std::string& icon_path, const sf::Font& font);

    void Update(float dt, SunManager* sunManager);
    void Draw(sf::RenderWindow& window);
    void SetPosition(float x, float y);

    bool Contains(const sf::Vector2i& mousePos) const;
    void OnHover(bool hover);
    void OnClick(SunManager* sunManager);

    void StartCooldown();
    void UpdateCooldown(float dt);

    PlantType GetType() const { return type; }
    bool IsAvailable() const { return is_available && current_cooldown <= 0; }
    int GetCost() const { return cost; }
};