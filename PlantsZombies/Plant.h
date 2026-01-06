#pragma once
#include "Object.h"

class Plant : public Object
{
protected:
    int row; 
    int col;
    int cost;
    int range;
    float hp;          
    float damage;      
    float attackSpeed; 
    float attackTimer; 
public:
    Plant(int row, sf::Vector2f position, const std::string& file_name,
        int cost, int range, float hp, float damage, float attackSpeed, float attackTimer,
        const sf::IntRect& rect, sf::Vector2f physical_size,
        GameField* field);

    virtual ~Plant();

    int Get_row() const override { return row; }
    float GetHP() const { return hp; }
    float GetDamage() const { return damage; }
    int GetCost() const { return cost; }
    void SetDamage(float newDamage) { damage = newDamage; }


    CollisionObject GetType() const override { return CollisionObject::Plant; }
    bool IsCollision(Object* other) const override;
    void IsDeath();
    virtual void SendMessage(Message* m);
    virtual void Update(float t) override;

private:
    void CreateProjectile();
};
