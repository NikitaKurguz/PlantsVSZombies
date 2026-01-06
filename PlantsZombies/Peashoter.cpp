#include "Peashoter.h"
#include "Manager.h"

Peashoter::Peashoter(int row, int col, sf::Vector2f pos, GameField* field):
	Plant(row, col, pos, "textures\\plants\\Peashoter.png", 100,
		field->get_field_size().x, 100, 0, 1.5, true, {0, 0, 442, 446},
		{70, 71}, field)
{
}

Peashoter::~Peashoter()
{
}

void Peashoter::SendMessage(Message* m)
{

}

void Peashoter::Update(float t)
{
}

void Peashoter::CreateProjectile()
{
}
