#include "Collector.h"
#include "Manager.h"

Collector::Collector(GameField* field) :
    Object({ 0, 0 }, "", { 0, 0, 1, 1 }, { 1, 1 }, field)
{}

void Collector::Update(float dt)
{}

void Collector::SendMessage(Message* m)
{}

bool Collector::IsCollision(Object* other) const
{
    return false; 
}

void Collector::UpdatePosition(const sf::RenderWindow& window)
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    Position(window.mapPixelToCoords(mouse_pos));
}