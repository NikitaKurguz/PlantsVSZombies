
#include "GameField.h"

GameField::GameField():
	rows(5), cols(9), field_size({740, 500}), field_origin({245, 75})

{
	auto* tm = TextureManager::GetTextureInstance();
	tm->LoadTextureFromFile("textures\\Fields\\Field_day_1.jpg");
	background.setTexture(*tm->GetTexturePointer("textures\\Fields\\Field_day_1.jpg"));
    
    cell_size = { field_size.x / cols, field_size.y / rows };
    grid.resize(rows, std::vector<Cell>(cols));
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            grid[r][c].center = GetCellCenter(r, c);

    lawnMowers.resize(rows, nullptr);
}
void GameField::Draw(sf::RenderWindow& window)
{
    window.draw(background);

    sf::CircleShape center(3.f);
    center.setFillColor(sf::Color::Blue);
    center.setOrigin(3.f, 3.f);

    sf::Vector2f pos = GetMowerPosition(0);
    center.setPosition(pos);

    sf::RectangleShape cell(cell_size);
    cell.setFillColor(sf::Color::Transparent);
    cell.setOutlineThickness(1.f);
    cell.setOutlineColor(sf::Color(255, 0, 0, 120));

    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
        {
            cell.setPosition(
                field_origin.x + c * cell_size.x,
                field_origin.y + r * cell_size.y
            );
            window.draw(cell);
            window.draw(center);
        }
}

sf::Vector2f GameField::GetCellCenter(int row, int col) const
{
    return { field_origin.x + col * cell_size.x + cell_size.x * 0.5f,
        field_origin.y + row * cell_size.y + cell_size.y * 0.5f };
}

bool GameField::IsCellFree(int row, int col) const
{
    return grid[row][col].plant == nullptr;
}

void GameField::PlacePlant(Object* plant, int row, int col)
{
    if (!IsCellFree(row, col))
        return;

    grid[row][col].plant = plant;
    plant->Position(grid[row][col].center);
}

sf::Vector2f GameField::GetMowerPosition(int row) const
{
    return { field_origin.x - (cell_size.x * 0.3f),
        field_origin.y + row * cell_size.y + cell_size.y * 0.5f };
}

