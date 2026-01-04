#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <string>
#include <iostream>
struct Message;
class Object
{
private:
	static int LastID;
protected:
	int id;
	std::string textureFilename;
	sf::Vector2f position;

	sf::Sprite sprite;
	sf::IntRect rect;

	sf::Vector2f physical_size;
	bool AutoScalingEnabled = true;

	void CheckTex(const std::string& filename);
	void AutoScaling();
public:
	Object(sf::Vector2f position, const std::string& filename, const sf::IntRect& rect, sf::Vector2f physical_size);
	Object(const Object& other);
	virtual ~Object();

	int GetID() const { return id; }
	sf::Vector2f GetPosition() const { return position; }
	virtual CollisionObject GetType() const = 0;
	void Position(sf::Vector2f new_pos);
	
	void SetTexture(const std::string& texture_filename, const sf::IntRect& rect);
	static int GetNewID();
	static int GetLastID();
	sf::FloatRect GetHitBox() const { return sprite.getGlobalBounds(); }
	bool IsCollision(Object* other) const;
	virtual void Update(float t) = 0;
	virtual void SendMessage(Message* m) = 0;
	void Draw(sf::RenderWindow& window);
};

