#pragma once
#include <SFML/Graphics.hpp>
#include  "TextureManager.h"
#include "Object.h"
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
	std::vector<Object*> lawnMowers;

public:
	GameField();
	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetCellCenter(int row, int col) const;
	bool IsCellFree(int row, int col) const;
	void PlacePlant(Object* plant, int row, int col);

	sf::Vector2f GetMowerPosition(int row) const;
};

