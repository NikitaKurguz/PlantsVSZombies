#include "GameOverWin.h"
#include "TextureManager.h"
#include <iostream>

GameOverWin::GameOverWin()
{}

bool GameOverWin::Initialize()
{
    if (!font.loadFromFile("fonts/arial.ttf"))
    {
        std::cerr << "Failed to load font for GameOverScreen!" << std::endl;
        return false;
    }

    overlay.setFillColor(sf::Color(0, 0, 0, 200));

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(80);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);

    restartText.setFont(font);
    restartText.setString("Press ESC to exit");
    restartText.setCharacterSize(30);
    restartText.setFillColor(sf::Color::White);

    initialized = true;
    return true;
}

void GameOverWin::SetGameOverImage(const std::string& imageFilePath)
{
    auto* tm = TextureManager::GetTextureInstance();

    if (tm->LoadTextureFromFile(imageFilePath))
    {
        const sf::Texture* texture = tm->GetTexturePointer(imageFilePath);
        if (texture)
        {
            gameOverImage.setTexture(*texture);
            gameOverImage.setScale(0.85f, 0.85f);
            hasImage = true;
        }
    }
    else
    {
        hasImage = false;
    }
}

void GameOverWin::SetOverlayOpacity(int opacity)
{
    sf::Color color = overlay.getFillColor();
    color.a = opacity;
    overlay.setFillColor(color);
}

void GameOverWin::SetTextColor(const sf::Color& color)
{
    gameOverText.setFillColor(color);
}

void GameOverWin::Draw(sf::RenderWindow& window)
{
    if (!initialized) return;

    overlay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    window.draw(overlay);

    sf::FloatRect textBounds = gameOverText.getLocalBounds();
    float centerX = window.getSize().x / 2.0;
    float centerY = window.getSize().y / 2.0 - 50;

    float textX = centerX - (textBounds.width / 2.0);
    if (hasImage)
    {
        textX = centerX - (textBounds.width / 2.0) - 40;
    }

    gameOverText.setPosition(textX, centerY - textBounds.height / 2.0);

    if (hasImage)
    {
        sf::FloatRect imageBounds = gameOverImage.getLocalBounds();
        float imageWidth = imageBounds.width * 0.85;
        float imageHeight = imageBounds.height * 0.85;
        float imageX = textX + textBounds.width + 20;
        float imageY = centerY - imageHeight / 2.0;
        gameOverImage.setPosition(imageX, imageY);
        window.draw(gameOverImage);
    }

    window.draw(gameOverText);

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

void GameOverWin::HandleInput(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            window.close();
        }
    }
}

void GameOverWin::SetGameOverReason(const std::string& reason)
{
    infoText.setString(reason);
}