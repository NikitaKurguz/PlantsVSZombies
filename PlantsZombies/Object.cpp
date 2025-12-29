#include "Object.h"

int Object::LastID = 0;

Object::Object()
{

}

Object::Object(const Object&)
{
}

Object::~Object()
{
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

void Object::Draw()
{
}
