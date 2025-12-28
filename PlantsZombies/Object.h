#pragma once
#include <SFML/Graphics.hpp>
class Object
{
private:
	int ID;
	sf::Vector2f position;
	
public:
	Object();
	Object(const Object&);
	virtual ~Object();

	int GetID() const { return ID; }
	sf::Vector2f GetPosition() const { return position; }

	virtual void Update(float t);
	void Draw();
};

