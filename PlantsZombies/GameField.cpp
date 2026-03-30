#include "GameField.h"

GameField::GameField():
	rows(5), cols(9), field_size({740, 500}), field_origin({250, 75})

{
	auto* tm = TextureManager::GetTextureInstance();
	tm->LoadTextureFromFile("textures\\Fields\\Field_day_1.jpg");
	background.setTexture(*tm->GetTexturePointer("textures\\Fields\\Field_day_1.jpg"));
    
    cell_size = { field_size.x / cols, field_size.y / rows };
    grid.resize(rows, std::vector<Cell>(cols));
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < cols; ++c)
            grid[r][c].center = GetCellCenter(r, c);

}
void GameField::Draw(sf::RenderWindow& window)
{
    window.draw(background);


    //sf::RectangleShape cell(cell_size);
    //cell.setFillColor(sf::Color::Transparent);
    //cell.setOutlineThickness(1.f);
    //cell.setOutlineColor(sf::Color(255, 0, 0, 120));

    //for (int r = 0; r < rows; ++r)
    //    for (int c = 0; c < cols; ++c)
    //    {
    //        cell.setPosition(field_origin.x + c * cell_size.x,
    //            field_origin.y + r * cell_size.y);
    //        window.draw(cell);
    //    }
}

sf::Vector2f GameField::GetCellCenter(int row, int col) const
{
    return { field_origin.x + col * cell_size.x + cell_size.x * 0.5f,
        field_origin.y + row * cell_size.y + cell_size.y * 0.5f };
}

bool GameField::IsCellFree(int row, int col) const
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
        return false;
    return grid[row][col].plant == nullptr;
}





