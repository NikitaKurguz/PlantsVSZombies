#pragma once
#include <SFML/Graphics.hpp>
class Message;
struct Object
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
	virtual void SendMessage(Message* m);
	void Draw();
};

