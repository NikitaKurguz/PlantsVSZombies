#include "Collector.h"
#include "Manager.h"

Collector::Collector(GameField* field) :
    Object({ 0, 0 }, "", { 0, 0, 1, 1 }, { 1, 1 }, field)
{
    // Невидимый объект для сбора
}

void Collector::Update(float dt)
{
    // Обновляем позицию каждый кадр из main
}

void Collector::SendMessage(Message* m)
{
    // Collector не обрабатывает сообщения
}

bool Collector::IsCollision(Object* other) const
{
    return false;  // Коллизии проверяются отдельно по клику мыши
}

void Collector::UpdatePosition(const sf::RenderWindow& window)
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    Position(window.mapPixelToCoords(mouse_pos));
}