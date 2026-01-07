#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "TextureManager.h"
#include <string>
#include <iostream>
#include "GameField.h"
struct Message;
enum class CollisionObject {
	Plant, Zombie, LawnMower, Projectile, Other
};
enum class ObjectState{
	Alive, Dying, Dead
};
class Object
{
private:
	static int LastID;
protected:
	GameField* field;

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
	Object(sf::Vector2f position, const std::string& filename, const sf::IntRect& rect, sf::Vector2f physical_size,
	GameField* field);
	Object(const Object& other);
	bool isAlive = true;
	virtual ~Object();

	int GetID() const { return id; }
	virtual int Get_row() const { return -1; }
	GameField* Get_field() const { return field; }
	sf::Vector2f GetPosition() const { return position; }
	virtual CollisionObject GetType() const = 0;
	void Position(sf::Vector2f new_pos);
	

	void SetTexture(const std::string& texture_filename, const sf::IntRect& rect);
	static int GetNewID();
	static int GetLastID();
	sf::FloatRect GetHitBox() const { return sprite.getGlobalBounds(); }
	virtual bool IsCollision(Object* other) const = 0;
	virtual void Update(float t) = 0;
	virtual void SendMessage(Message* m) = 0;
	void Draw(sf::RenderWindow& window);
};

