#include "PlantingInterface.h"
#include "Peashooter.h"
#include "Sunflower.h"
#include "Wallnut.h"
#include "PotatoMine.h"  


PlantingInterface::PlantingInterface(GameField* field, SunManager* sunManager, LevelManager* levelManager)
    : field(field), sunManager(sunManager), levelManager(levelManager)
{
    interface_position = { 10, 100 }; 

    font.loadFromFile("fonts/arial.ttf");

    highlight_cell.setSize(field->get_cell_size());
    highlight_cell.setFillColor(sf::Color(255, 255, 0, 100));
    highlight_cell.setOutlineThickness(2);
    highlight_cell.setOutlineColor(sf::Color::Yellow);

    Initialize();
}

void PlantingInterface::Initialize()
{
    cards.push_back(std::make_unique<PlantCard>(
        PlantType::Peashooter, 100, 5,
        "textures/plants/Peashoter_icon.png", font));

    cards.push_back(std::make_unique<PlantCard>(
        PlantType::Sunflower, 50, 5,
        "textures/plants/Sunflower_icon.png", font));
    cards.push_back(std::make_unique<PlantCard>(
        PlantType::Wallnut, 50, 10, 
        "textures/plants/Wallnut_icon.jpg", font));
    cards.push_back(std::make_unique<PlantCard>(
        PlantType::PotatoMine, 25, 15,  // cost=25, перезарядка 15 секунд
        "textures/plants/PotatoMine_icon.jpg", font));

    float x = interface_position.x;
    float y = interface_position.y;

    for (size_t i = 0; i < cards.size(); ++i)
    {
        cards[i]->SetPosition(x, y + i * (CARD_HEIGHT + CARD_SPACING));
    }
}

void PlantingInterface::Update(float dt, const sf::RenderWindow& window)
{
    for (auto& card : cards)
    {
        card->Update(dt, sunManager);
    }

    if (is_planting_mode)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        if (worldPos.x >= field->get_field_origin().x &&
            worldPos.x <= field->get_field_origin().x + field->get_field_size().x &&
            worldPos.y >= field->get_field_origin().y &&
            worldPos.y <= field->get_field_origin().y + field->get_field_size().y)
        {
            hover_col = static_cast<int>((worldPos.x - field->get_field_origin().x) / field->get_cell_size().x);
            hover_row = static_cast<int>((worldPos.y - field->get_field_origin().y) / field->get_cell_size().y);

            highlight_cell.setPosition(
                field->get_field_origin().x + hover_col * field->get_cell_size().x,
                field->get_field_origin().y + hover_row * field->get_cell_size().y
            );
        }
        else
        {
            hover_row = -1;
            hover_col = -1;
        }
    }
}

void PlantingInterface::Draw(sf::RenderWindow& window)
{
    if (cards.empty()) return;

    float card_width = 80;
    float card_height = 100;
    float spacing = 130;
    float padding = 10;
    float bg_height = cards.size() * card_height +
        (cards.size() - 1) * spacing +padding * 2;

    float bg_width = card_width + padding * 2;

    sf::RectangleShape interface_bg(sf::Vector2f(bg_width, bg_height));
    interface_bg.setPosition(interface_position.x - padding, interface_position.y - padding);
    interface_bg.setFillColor(sf::Color(50, 50, 50, 200));
    interface_bg.setOutlineThickness(2);
    interface_bg.setOutlineColor(sf::Color::White);
    window.draw(interface_bg);

    for (auto& card : cards)
    {
        card->Draw(window);
    }

    if (is_planting_mode && hover_row >= 0 && hover_col >= 0)
    {
        if (field->IsCellFree(hover_row, hover_col))
        {
            highlight_cell.setFillColor(sf::Color(0, 255, 0, 100));
            highlight_cell.setOutlineColor(sf::Color::Green);
        }
        else
        {
            highlight_cell.setFillColor(sf::Color(255, 0, 0, 100));
            highlight_cell.setOutlineColor(sf::Color::Red);
        }
        window.draw(highlight_cell);
    }
}

void PlantingInterface::HandleMouseMove(const sf::Vector2i& mousePos)
{
    for (auto& card : cards)
    {
        bool hover = card->Contains(mousePos);
        card->OnHover(hover);
    }
}

void PlantingInterface::HandleMouseClick(const sf::Vector2i& mousePos, sf::RenderWindow& window)
{
    // Сначала проверяем клик по карточкам
    for (size_t i = 0; i < cards.size(); ++i)
    {
        if (cards[i]->Contains(mousePos))
        {
            // Просто входим в режим посадки, если карточка доступна
            if (cards[i]->IsAvailable() && sunManager->GetSunCount() >= cards[i]->GetCost())
            {
                EnterPlantingMode(cards[i]->GetType());
            }
            return;
        }
    }

    // Если в режиме посадки и клик по полю
    if (is_planting_mode)
    {
        sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

        if (worldPos.x >= field->get_field_origin().x &&
            worldPos.x <= field->get_field_origin().x + field->get_field_size().x &&
            worldPos.y >= field->get_field_origin().y &&
            worldPos.y <= field->get_field_origin().y + field->get_field_size().y)
        {
            int col = static_cast<int>((worldPos.x - field->get_field_origin().x) / field->get_cell_size().x);
            int row = static_cast<int>((worldPos.y - field->get_field_origin().y) / field->get_cell_size().y);

            TryPlacePlant(row, col);
        }
        else
        {
            ExitPlantingMode();
        }
    }
}

void PlantingInterface::EnterPlantingMode(PlantType type)
{
    is_planting_mode = true;
    selected_plant = type;
}

void PlantingInterface::ExitPlantingMode()
{
    is_planting_mode = false;
    hover_row = -1;
    hover_col = -1;
}

bool PlantingInterface::TryPlacePlant(int row, int col)
{
    if (!field->IsCellFree(row, col))
        return false;

    // Находим карточку выбранного растения
    for (auto& card : cards)
    {
        if (card->GetType() == selected_plant)
        {
            // Проверяем, хватает ли солнышек и доступна ли карточка
            if (card->IsAvailable() && sunManager->GetSunCount() >= card->GetCost())
            {
                Plant* new_plant = nullptr;
                sf::Vector2f plantPos = levelManager->GetPlantPosition(row, col);

                switch (selected_plant)
                {
                case PlantType::Peashooter:
                    new_plant = new Peashooter(row, col, plantPos, field);
                    break;
                case PlantType::Sunflower:
                    new_plant = new Sunflower(row, col, plantPos, field);
                    break;
                case PlantType::Wallnut:  
                    new_plant = new Wallnut(row, col, plantPos, field);
                    break;
                case PlantType::PotatoMine:  // <-- Добавляем картошку
                    new_plant = new PotatoMine(row, col, plantPos, field);
                    break;
                }

                if (new_plant)
                {
                    // ТРАТИМ СОЛНЫШКИ!
                    sunManager->SpendSun(card->GetCost());

                    field->SetPlant(row, col, new_plant);

                    // Создаем растение
                    Manager::GetExemplar()->SendCreateMsg(new_plant);

                    ExitPlantingMode();
                    return true;
                }
            }
            break;
        }
    }

    return false;
}