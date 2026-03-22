#include "CherryBomb.h"
#include "Manager.h"
#include <cmath>

CherryBomb::CherryBomb(int row, int col, sf::Vector2f pos, GameField* field) :
    Plant(row, col, pos, "textures/plants/CherryBomb.png",
        150, 0, 100, 150, 0, false,  // cost=150, damage=150
        { 0, 0, 512, 512 }, { 80, 80 }, field)
{
    CheckTex("textures/plants/CherryBomb.png");
    std::cout << "Вишневая бомба посажена! Взорвется через " << explosion_delay << " сек" << std::endl;
}

CherryBomb::~CherryBomb()
{
}

void CherryBomb::Update(float dt)
{
    Plant::Update(dt);

    if (!exploded)
    {
        timer += dt;

        // Эффект мигания перед взрывом
        if (timer >= explosion_delay - 0.5f)
        {
            // Мигаем красным
            int alpha = (int)(255 * (1.0f - (timer - (explosion_delay - 0.5f)) / 0.5f));
            sprite.setColor(sf::Color(255, 100, 100, 255));
        }

        if (timer >= explosion_delay)
        {
            Explode();
        }
    }
}

void CherryBomb::SendMessage(Message* m)
{
    Plant::SendMessage(m);
}

void CherryBomb::Explode()
{
    if (exploded) return;
    exploded = true;

    std::cout << "*** БА-БАХ! Вишневая бомба взорвалась! ***" << std::endl;

    Manager* mgr = Manager::GetExemplar();
    if (!mgr) return;

    const auto& objects = mgr->GetObjects();
    int zombies_hit = 0;

    for (Object* obj : objects)
    {
        if (!obj || !obj->isAlive) continue;
        if (obj->GetType() != CollisionObject::Zombie) continue;

        // Проверяем расстояние до зомби
        float dx = std::abs(obj->GetPosition().x - GetPosition().x);
        float dy = std::abs(obj->GetPosition().y - GetPosition().y);
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance <= explosion_radius)
        {
            std::cout << "  Зомби уничтожен! Расстояние: " << distance << std::endl;
            mgr->SendAttackMsg(this, obj, damage);
            zombies_hit++;
        }
    }

    std::cout << "Уничтожено зомби: " << zombies_hit << std::endl;

    // Очищаем клетку в поле
    if (field)
        field->ClearCell(row, col);

    // Самоуничтожаемся после взрыва
    mgr->SendDeathMsg(this);
}