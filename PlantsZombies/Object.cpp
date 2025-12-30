#include "Object.h"

int Object::LastID = 0;

Object::Object(sf::Vector2f position, float size_rad, const sf::Texture& tex):
	position(position), size_rad(size_rad)
{
	id = GetNewID();
	SetTexture(tex);
}

Object::Object(const Object& other)
{

}

Object::~Object()
{
}

void Object::SetTexture(const sf::Texture& tex)
{
	sprite.setTexture(tex);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	if (size_rad > 0)
	{
		float maxSide = std::max(bounds.width, bounds.height);
		if (maxSide > 0)
		{
			float scale = (size_rad * 2.0f) / maxSide;
			sprite.setScale(scale, scale);
		}
	}

}
void Object::Position(sf::Vector2f new_pos)
{
	position = new_pos;
}

int Object::GetNewID()
{
	return ++LastID;
}

int Object::GetLastID()
{
	return LastID;
}

void Object::Update(float t)
{
}

void Object::SendMessage(Message* m)
{
}

void Object::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(position);
	window.draw(sprite);
}
