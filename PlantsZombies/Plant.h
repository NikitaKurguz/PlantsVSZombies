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
    float attack_cooldown;
    float attack_timer;
    bool is_attack_type;

    int targetID = -1;
    bool isAttacking = false;
    bool projectile_active = false;
    float color_timer = 0;

    bool IsAttackReady() const { return attack_timer >= attack_cooldown; }
public:
    Plant(int row, int col, sf::Vector2f position, const std::string& file_name,
        int cost, int range, float hp, float damage, float attack_cooldown, bool is_attack_type,
        const sf::IntRect& rect, sf::Vector2f physical_size,
        GameField* field);

    virtual ~Plant();
    void OnProjectileDestroyed();
    int Get_row() const override { return row; }
    float GetHP() const { return hp; }
    float GetDamage() const { return damage; }

    CollisionObject GetType() const override { return CollisionObject::Plant; }
    bool IsCollision(Object* other) const override;

    virtual void TakeDmg(float dmg);
    virtual void SendMessage(Message* m);
    virtual void Update(float t) override;


    virtual void CreateProjectile(Object* target) = 0;
    virtual Object* FindTargetInRange() = 0;

    Object* GetTarget();
    void StopAttack();
};
