#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class WinScreen
{
private:
    sf::RectangleShape overlay;
    sf::Sprite winImage;
    sf::Text winText;
    sf::Text infoText;
    sf::Text restartText;

    sf::Font font;
    bool initialized = false;
    bool hasImage = false;

public:
    WinScreen();
    bool Initialize();

    void SetWinImage(const std::string& imageFilePath);
    void Draw(sf::RenderWindow& window);
    void HandleInput(const sf::Event& event, sf::RenderWindow& window);
    void SetWinMessage(const std::string& message);

    void SetOverlayOpacity(int opacity);
    void SetTextColor(const sf::Color& color);
    void SetInfoColor(const sf::Color& color);
};