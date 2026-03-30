#include "PlantCard.h"

PlantCard::PlantCard(PlantType type, int cost, float cooldown,
    const std::string& icon_path, const sf::Font& font)
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

    sf::FloatRect bgBounds = background.getLocalBounds();
    sf::FloatRect iconBounds = icon.getLocalBounds();
    icon.setPosition(x + bgBounds.width / 2, y + 40);

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

    if (current_cooldown > 0)
    {
        cooldown_text.setString(std::to_string((int)current_cooldown + 1));
        window.draw(cooldown_text);
    }
}

bool PlantCard::Contains(const sf::Vector2i& mousePos) const
{
    sf::Vector2f mouseF(static_cast<float>(mousePos.x),
        static_cast<float>(mousePos.y));
    return background.getGlobalBounds().contains(mouseF);
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
        // Сигнал о покупке будет обработан в интерфейсе
    }
}

void PlantCard::StartCooldown()
{
    current_cooldown = cooldown_time;
    is_available = false;
}

void PlantCard::UpdateCooldown(float dt)
{
    if (current_cooldown > 0)
    {
        current_cooldown -= dt;
        if (current_cooldown <= 0)
        {
            current_cooldown = 0;
            is_available = true;
        }
    }
}