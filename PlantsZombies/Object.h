#pragma once
#include <SFML/Graphics.hpp>
class Message;
struct Object
{
private:
	static int LastID;
protected:
	int ID;
	sf::Vector2f position;
	
public:
	Object();
	Object(const Object& other);
	virtual ~Object();

	int GetID() const { return ID; }
	sf::Vector2f GetPosition() const { return position; }

	static int GetNewID();
	static int GetLastID();
	virtual void Update(float t) = 0;
	virtual void SendMessage(Message* m) = 0;
	void Draw();
};

