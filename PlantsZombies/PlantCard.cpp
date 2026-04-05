#include "PlantCard.h"

PlantCard::PlantCard(PlantType type, int cost, float cooldown,
    const std::string& icon_path)
    : type(type), cost(cost), cooldown_time(cooldown)
{
    background.setSize(sf::Vector2f(80, 80));
    background.setFillColor(normal_color);
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::Black);

    auto* tm = TextureManager::GetTextureInstance();
    tm->LoadTextureFromFile(icon_path);
    icon.setTexture(*tm->GetTexturePointer(icon_path));

    sf::FloatRect bounds = icon.getLocalBounds();
    float scale_x = 70.0f / bounds.width;
    float scale_y = 70.0f / bounds.height;
    icon.setScale(scale_x, scale_y);
    icon.setOrigin(bounds.width / 2, bounds.height / 2);
}

void PlantCard::SetPosition(float x, float y)
{
    position = { x, y };
    background.setPosition(x, y);
    icon.setPosition(x + 40, y + 40);

}

void PlantCard::Update(float dt, SunManager* sunManager)
{
    UpdateCooldown(dt);

    if (!IsAvailable() || (sunManager && sunManager->GetSunCount() < cost))
    {
        background.setFillColor(unavailable_color);
    }
    else if (is_hovered)
    {
        background.setFillColor(hover_color);
    }
    else
    {
        background.setFillColor(normal_color);
    }
}

void PlantCard::Draw(sf::RenderWindow& window)
{
    window.draw(background);
    window.draw(icon);
}

bool PlantCard::Contains(const sf::Vector2i& mousePos) const
{
    return background.getGlobalBounds().contains(
        float(mousePos.x),
        float(mousePos.y)
    );
}

void PlantCard::OnHover(bool hover)
{
    is_hovered = hover;
}

void PlantCard::OnClick(SunManager* sunManager)
{
    if (IsAvailable() && sunManager && sunManager->SpendSun(cost))
    {
        StartCooldown();
    }
}

void PlantCard::StartCooldown()
{
    current_cooldown = cooldown_time;
}

void PlantCard::UpdateCooldown(float dt)
{
    if (current_cooldown > 0)
    {
        current_cooldown -= dt;
        if (current_cooldown <= 0)
        {
            current_cooldown = 0;
        }
    }
}