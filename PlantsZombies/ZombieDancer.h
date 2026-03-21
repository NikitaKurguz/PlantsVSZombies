#pragma once
#include "Zombie.h"
class ZombieDancer : public Zombie
{
private:
    bool has_summoned = false;
    float start_x;
    float summon_distance = 300;
    float Get_x_pos(sf::Vector2f pos) const;

public:
    ZombieDancer(int row, sf::Vector2f position, GameField* field);
    void SendMessage(Message* m) override;
    void Update(float t) override;
    void TakeDmg(float dmg_amount) override;
    void IsDeath() override;
    void SummonZombies();
    
};
