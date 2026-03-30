#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "PlantCard.h"
#include "GameField.h"
#include "SunManager.h"
#include "LevelManager.h"

class PlantingInterface {
private:
    std::vector<std::unique_ptr<PlantCard>> cards;
    sf::Font font;
    GameField* field;
    SunManager* sunManager;
    LevelManager* levelManager;

    bool is_planting_mode = false;
    PlantType selected_plant;
    sf::RectangleShape highlight_cell;
    int hover_row = -1;
    int hover_col = -1;

    sf::Vector2f interface_position;
    const float CARD_WIDTH = 80;
    const float CARD_HEIGHT = 100;
    const float CARD_SPACING = -20;

public:
    PlantingInterface(GameField* field, SunManager* sunManager, LevelManager* levelManager);
    ~PlantingInterface() = default;

    void Initialize();  
    void Update(float dt, const sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);

    void HandleMouseMove(const sf::Vector2i& mousePos);
    void HandleMouseClick(const sf::Vector2i& mousePos, sf::RenderWindow& window);

    void EnterPlantingMode(PlantType type);
    void ExitPlantingMode();
    bool TryPlacePlant(int row, int col);

    sf::Vector2f GetInterfacePosition() const { return interface_position; }
};