#include "Object.h"

int Object::LastID = 0;

Object::Object(sf::Vector2f position, float scale_rad, const std::string& filename):
	position(position), scale_rad(scale_rad)
{
	id = GetNewID();
	SetTexture(filename);
}

Object::Object(const Object& other):

	position(other.position), scale_rad(other.scale_rad)
{
	const sf::Texture* tex = other.sprite.getTexture();
	if (tex) 
		sprite.setTexture(*tex);

	sprite.setPosition(other.sprite.getPosition());
	sprite.setOrigin(other.sprite.getOrigin());
	sprite.setScale(other.sprite.getScale());
	sprite.setRotation(other.sprite.getRotation());
	id = GetNewID();
}

Object::~Object()
{
}

void Object::SetTexture(const std::string& texture_filename)
{
	sf::Texture* tex = TextureManager::GetTextureInstance()->GetTexturePointer(texture_filename);
	if (tex == nullptr) {
		if (!(TextureManager::GetTextureInstance()->LoadTextureFromFile(texture_filename)))
			return;
		tex = TextureManager::GetTextureInstance()->GetTexturePointer(texture_filename);
	}
	sprite.setTexture(*tex);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
	if (scale_rad > 0)
	{
		float maxSide = std::max(bounds.width, bounds.height);
		if (maxSide > 0)
		{
			float scale = (scale_rad * 2.0f) / maxSide;
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
