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
	void CheckTex(const std::string& filename);
	
public:
	Object(sf::Vector2f position, const std::string& filename, const sf::IntRect& rect);
	Object(const Object& other);
	virtual ~Object();

	int GetID() const { return id; }
	sf::Vector2f GetPosition() const { return position; }
	void Position(sf::Vector2f new_pos);
	
	void SetTexture(const std::string& texture_filename, const sf::IntRect& rect);
	static int GetNewID();
	static int GetLastID();
	virtual void Update(float t) = 0;
	virtual void SendMessage(Message* m) = 0;
	void Draw(sf::RenderWindow& window);
};

