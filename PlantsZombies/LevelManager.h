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

    int currentWave = 0;
    int totalWaves = 5;

    struct Wave
    {
        int zombiesCount;
        float spawnDelay;
        float waveDelay;
        std::vector<std::pair<int, std::string>> zombies;
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
    bool IsAllWavesComplete() const { return currentWave >= totalWaves; }
};