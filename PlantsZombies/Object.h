#pragma once
#include <SFML/Graphics.hpp>
class Message;
struct Object
{
private:
	static int LastID;
protected:
	int id;
	float scale_rad;
	sf::Vector2f position;
	sf::Sprite sprite;
	
public:
	Object(sf::Vector2f position, float size_rad, const sf::Texture& tex);
	Object(const Object& other);
	virtual ~Object();

	int GetID() const { return id; }
	sf::Vector2f GetPosition() const { return position; }
	void Position(sf::Vector2f new_pos);
	
	void SetTexture(const sf::Texture& tex);
	static int GetNewID();
	static int GetLastID();
	virtual void Update(float t) = 0;
	virtual void SendMessage(Message* m) = 0;
	void Draw(sf::RenderWindow& window);
};

