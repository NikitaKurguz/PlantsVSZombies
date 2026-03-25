#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameOverWin
{
private:
    sf::RectangleShape overlay;
    sf::Sprite gameOverImage;
    sf::Text gameOverText;
    sf::Text infoText;
    sf::Text restartText;

    sf::Font font;
    bool initialized = false;
    bool hasImage = false;

public:
    GameOverWin();
    bool Initialize();

    void SetGameOverImage(const std::string& imageFilePath);
    void Draw(sf::RenderWindow& window);
    void HandleInput(const sf::Event& event, sf::RenderWindow& window);
    void SetGameOverReason(const std::string& reason);

    void SetOverlayOpacity(int opacity);
    void SetTextColor(const sf::Color& color);
};