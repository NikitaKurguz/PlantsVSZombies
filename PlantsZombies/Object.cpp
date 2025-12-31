#include "Object.h"

int Object::LastID = 0;

Object::Object(sf::Vector2f position, float scale_rad, const std::string& filename, const sf::IntRect& rect) :
	position(position), scale_rad(scale_rad), rect(rect)
{
	id = GetNewID();
	SetTexture(filename, rect);
}

Object::Object(const Object& other)
	: position(other.position),
	scale_rad(other.scale_rad),
	rect(other.rect),
	textureFilename(other.textureFilename),
	id(GetNewID())
{
	if (const sf::Texture* tex = other.sprite.getTexture())
	{
		sprite.setTexture(*tex);
		sprite.setTextureRect(rect);
	}

	sprite.setOrigin(other.sprite.getOrigin());
	sprite.setScale(other.sprite.getScale());
	sprite.setRotation(other.sprite.getRotation());
}


Object::~Object()
{
	
}

void Object::SetTexture(const std::string& filename, const sf::IntRect& rect)
{
	textureFilename = filename;

	auto* tm = TextureManager::GetTextureInstance();

	if (!tm->LoadTextureFromFile(filename))
		return;

	sf::Texture* tex = tm->GetTexturePointer(filename);
	sprite.setTexture(*tex);
	sprite.setTextureRect(rect);

	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	if (scale_rad > 0)
	{
		float maxSide = std::max(bounds.width, bounds.height);
		if (maxSide > 0)
		{
			float scale = (scale_rad * 2.f) / maxSide;
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
