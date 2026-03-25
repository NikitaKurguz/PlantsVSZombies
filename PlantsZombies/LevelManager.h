#pragma once
#include "GameField.h"
#include "Zombie.h"
#include "ZombieBucket.h"
#include "ZombieRunner.h"
#include "ZombieDancer.h"
#include "Manager.h"
#include <vector>
#include <map>

class Plant;
class LevelManager
{
private:
    GameField* field;
    Manager* manager;

    // Система волн
    int currentWave = 0;
    int totalWaves = 3; // Всего 3 волны

    struct Wave
    {
        int zombiesCount;           // Количество зомби в волне
        float spawnDelay;           // Задержка между спавном зомби
        float waveDelay;            // Задержка перед следующей волной
        std::vector<std::pair<int, std::string>> zombies; // <ряд, тип зомби>
    };

    std::vector<Wave> waves;

    int zombiesSpawnedInWave = 0;
    float spawnTimer = 0;
    float waveTimer = 0;
    bool waveInProgress = false;
    bool waveDelayActive = false;

    void LoadWaves();
    void SpawnZombie(int row, const std::string& zombieType);

public:
    LevelManager(GameField* field, Manager* manager);
    void Update(float dt);
    ~LevelManager();

    sf::Vector2f GetZombieSpawnPosition(int row) const;
    sf::Vector2f GetLawnMowerPosition(int row) const;
    sf::Vector2f GetPlantPosition(int row, int col) const;

    int GetCurrentWave() const { return currentWave; }
    int GetTotalWaves() const { return totalWaves; }
};