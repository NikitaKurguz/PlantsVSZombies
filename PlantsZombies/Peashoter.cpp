#include "Peashoter.h"
#include "Manager.h"
#include "Projectile.h"
#include <iostream> 

Peashoter::Peashoter(int row, int col, sf::Vector2f pos, GameField* field) :
    Plant(row, col, pos, "textures\\plants\\Peashoter.png",
        100,                          
        field->get_field_size().x,   
        100,                         
        40,                         
        1.5f,                     
        true,                    
        { 0, 0, 442, 426 },            
        { 70, 71 },                
        field)
{
    std::cout << "Peashoter created at [" << row << "," << col
        << "] position: " << pos.x << "," << pos.y << std::endl;
}

Peashoter::~Peashoter()
{
}

void Peashoter::SendMessage(Message* m)
{
    Plant::SendMessage(m);
}

void Peashoter::Update(float t)
{
    Plant::Update(t); 
}

void Peashoter::CreateProjectile()
{
    std::cout << "Peashoter: Creating projectile!" << std::endl;

    sf::Vector2f shoot_position = GetPosition();
    shoot_position.x += 35.0f;  
    shoot_position.y -= 50.0f;  


    Projectile* pea = new Projectile(
        shoot_position,                     
        "textures\\plants\\pea2.png",   
        { 0, 0, 1152, 720 },                     
        { 80, 45 },                           
        Get_field(),                        
        GetDamage(),                        
        10.0f,                             
        800.0f                              
    );

    Message* create_msg = new Message();
    create_msg->type = MessageType::Create;
    create_msg->create.new_object = pea;

    Manager::GetExemplar()->SendMessage(create_msg);

    std::cout << "Pea projectile created at: "
        << shoot_position.x << ", " << shoot_position.y << std::endl;
}