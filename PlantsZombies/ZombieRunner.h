#pragma once
#include "Zombie.h"

class ZombieRunner : public Zombie
{
private:
    float armor_hp;
    bool is_tex_ch1, is_tex_ch2;
    float max_armor_hp = 300;
    sf::Texture damaged_tex_1;
    sf::Texture damaged_tex_2;

    bool is_jumping = false;
    bool has_jumped = false;
    float jump_timer = 0;
    float jump_duration = 1.8;
    float jump_distance = 150;
    float jump_height = 60;
    float jump_start_x = 0;
    float jump_start_y = 0;

public:
    ZombieRunner(int row, sf::Vector2f position, GameField* field);
    void SendMessage(Message* m) override;
    void Update(float t) override;
    void TakeDmg(float dmg_amount) override;
    void IsDeath() override;
    void StartJump(int plant_id);
    void StopJump();
    bool IsCollision(Object* other) const override;
};