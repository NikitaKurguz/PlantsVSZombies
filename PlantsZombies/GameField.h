#pragma once
#include <SFML/Graphics.hpp>
#include  "TextureManager.h"
class Object;
class GameField
{
private:
	sf::Sprite background;
	int rows;
	int cols;
	sf::Vector2f field_size;
	sf::Vector2f field_origin;
	sf::Vector2f cell_size;

	struct Cell {
		Object* plant = nullptr;
		sf::Vector2f center;
	};

	std::vector<std::vector<Cell>> grid;

public:
	GameField();
	void Draw(sf::RenderWindow& window);

	sf::Vector2f get_cell_size() const { return cell_size; }
	sf::Vector2f get_field_origin() const { return field_origin; }
	sf::Vector2f get_field_size() const { return field_size; }


	sf::Vector2f GetCellCenter(int row, int col) const;
	bool IsCellFree(int row, int col) const;

	int get_rows() const { return rows; }
	int get_cols() const { return cols; }

	void SetPlant(int row, int col, Object* plant) {
		if (row >= 0 && row < rows && col >= 0 && col < cols)
			grid[row][col].plant = plant;
	}
	void ClearCell(int row, int col) {
		if (row >= 0 && row < rows && col >= 0 && col < cols)
			grid[row][col].plant = nullptr;
	}
};

