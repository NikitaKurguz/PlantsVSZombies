#include "WinScreen.h"
#include "TextureManager.h"
#include <iostream>

WinScreen::WinScreen()
{}

bool WinScreen::Initialize()
{
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        std::cerr << "Failed to load font for WinScreen!" << std::endl;
        return false;
    }

    overlay.setFillColor(sf::Color(0, 0, 0, 200));

    winText.setFont(font);
    winText.setString("YOU WIN!");
    winText.setCharacterSize(80);
    winText.setFillColor(sf::Color::Green);
    winText.setStyle(sf::Text::Bold);

    infoText.setFont(font);
    infoText.setString("Congratulations! You defeated all zombies!");
    infoText.setCharacterSize(25);
    infoText.setFillColor(sf::Color::Yellow);

    restartText.setFont(font);
    restartText.setString("Press ESC to exit");
    restartText.setCharacterSize(30);
    restartText.setFillColor(sf::Color::White);

    initialized = true;
    return true;
}

void WinScreen::SetWinImage(const std::string& imageFilePath)
{
    auto* tm = TextureManager::GetTextureInstance();

    if (tm->LoadTextureFromFile(imageFilePath))
    {
        const sf::Texture* texture = tm->GetTexturePointer(imageFilePath);
        if (texture)
        {
            winImage.setTexture(*texture);
            winImage.setScale(0.85, 0.85);
            hasImage = true;
            std::cout << "Win screen image loaded: " << imageFilePath << std::endl;
        }
    }
    else
    {
        std::cerr << "Failed to load win screen image: " << imageFilePath << std::endl;
        hasImage = false;
    }
}

void WinScreen::SetOverlayOpacity(int opacity)
{
    sf::Color color = overlay.getFillColor();
    color.a = opacity;
    overlay.setFillColor(color);
}

void WinScreen::SetTextColor(const sf::Color& color)
{
    winText.setFillColor(color);
}

void WinScreen::SetInfoColor(const sf::Color& color)
{
    infoText.setFillColor(color);
}

void WinScreen::Draw(sf::RenderWindow& window)
{
    if (!initialized) return;

    overlay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    window.draw(overlay);

    sf::FloatRect textBounds = winText.getLocalBounds();
    float centerX = window.getSize().x / 2.0;
    float centerY = window.getSize().y / 2.0 - 50;

    float textX = centerX - (textBounds.width / 2.0);
    if (hasImage)
    {
        textX = centerX - (textBounds.width / 2.0) - 40;
    }

    winText.setPosition(textX, centerY - textBounds.height / 2.0);

    if (hasImage)
    {
        sf::FloatRect imageBounds = winImage.getLocalBounds();
        float imageWidth = imageBounds.width * 0.85;
        float imageHeight = imageBounds.height * 0.85;
        float imageX = textX + textBounds.width + 20;
        float imageY = centerY - imageHeight / 2.0;
        winImage.setPosition(imageX, imageY);
        window.draw(winImage);
    }

    window.draw(winText);

    sf::FloatRect infoBounds = infoText.getLocalBounds();
    infoText.setOrigin(infoBounds.left + infoBounds.width / 2.0,
        infoBounds.top + infoBounds.height / 2.0);
    infoText.setPosition(window.getSize().x / 2.0, window.getSize().y / 2.0 - 120);

    sf::FloatRect restartBounds = restartText.getLocalBounds();
    restartText.setOrigin(restartBounds.left + restartBounds.width / 2.0,
        restartBounds.top + restartBounds.height / 2.0);
    restartText.setPosition(window.getSize().x / 2.0, window.getSize().y / 2.0 + 50);

    window.draw(infoText);
    window.draw(restartText);
}

void WinScreen::HandleInput(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
            window.close();
        
    }
}

void WinScreen::SetWinMessage(const std::string& message)
{
    infoText.setString(message);
}