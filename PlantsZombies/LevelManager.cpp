#include "LevelManager.h"
#include "LawnMower.h"
#include "Peashooter.h"
#include <random>

LevelManager::LevelManager(GameField* field, Manager* manager) :
    field(field), manager(manager)
{
    for (int row = 0; row < field->get_rows(); ++row)
    {
        sf::Vector2f pos = GetLawnMowerPosition(row);
        LawnMower* mower = new LawnMower(pos, row, field);

        Message* msg = new Message;
        msg->type = MessageType::Create;
        msg->create.new_object = mower;
        manager->SendMessage(msg);
    }
    LoadWaves();
}

void LevelManager::LoadWaves()
{
    waves.clear();
    Wave wave1;
    wave1.zombiesCount = 3;
    wave1.spawnDelay = 25;
    wave1.waveDelay = 40;
    wave1.zombies = {
        {0, "default"},
        {1, "default"},
        {4, "default"}
    };
    waves.push_back(wave1);

    Wave wave2;
    wave2.zombiesCount = 5;
    wave2.spawnDelay = 20;
    wave2.waveDelay = 30;
    wave2.zombies = {
        {0, "default"},
        {1, "bucket"},
        {1, "default"},
        {4, "default"},
        {2, "bucket"}
    };
    waves.push_back(wave2);

    Wave wave3;
    wave3.zombiesCount = 7;
    wave3.spawnDelay = 30;
    wave3.waveDelay = 30;
    wave3.zombies = {
        {0, "bucket"},
        {1, "runner"},
        {3, "default"},
        {4, "bucket"},
        {0, "default"},
        {2, "default"},
        {3, "runner"}
    };
    waves.push_back(wave3);

    Wave wave4;
    wave4.zombiesCount = 10;
    wave4.spawnDelay = 30;
    wave4.waveDelay = 30;
    wave4.zombies = {
        {0, "default"},
        {4, "bucket"},
        {0, "runner"},
        {3, "default"},
        {1, "runner"},
        {3, "bucket"},
        {2, "dancer"},
        {1, "default"},
        {2, "runner"},
        {4, "bucket"}
    };
    waves.push_back(wave4);

    Wave wave5;
    wave5.zombiesCount = 15;
    wave5.spawnDelay = 30;
    wave5.waveDelay = 30;
    wave5.zombies = {
        {3, "bucket"},
        {2, "bucket"},
        {3, "dancer"},
        {0, "default"},
        {1, "runner"},
        {2, "default"},
        {4, "runner"},
        {3, "bucket"},
        {0, "default"},
        {1, "default"},
        {2, "dancer" },
        {3, "runner"},
        {1, "default"},
        {4, "bucket"},
        {2, "bucket"}
    };
    waves.push_back(wave5);

    currentWave = 0;
    waveInProgress = true;
    waveDelayActive = false;
    zombiesSpawnedInWave = 0;
    spawnTimer = 0;
    waveTimer = 0;
}

void LevelManager::SpawnZombie(int row, const std::string& zombieType)
{
    sf::Vector2f spawnPos = GetZombieSpawnPosition(row);
    Zombie* zombie = nullptr;

    if (zombieType == "default")
    {
        zombie = new Zombie(row, spawnPos, field);
    }
    else if (zombieType == "bucket")
    {
        zombie = new ZombieBucket(row, spawnPos, field);
    }
    else if (zombieType == "runner")
    {
        zombie = new ZombieRunner(row, spawnPos, field);
    }
    else if (zombieType == "dancer")
    {
        zombie = new ZombieDancer(row, spawnPos, field);
    }

    if (zombie)
    {
        manager->SendCreateMsg(zombie);
    }
}

void LevelManager::Update(float dt)
{
    if (manager->IsGameStopped() || manager->IsGameWin()) return;

    if (currentWave >= totalWaves)
    {
        return;
    }

    if (currentWave >= waves.size())
    {
        return;
    }

    Wave& currentWaveData = waves[currentWave];

    if (waveDelayActive)
    {
        waveTimer += dt;
        if (waveTimer >= currentWaveData.waveDelay)
        {
            waveDelayActive = false;
            waveInProgress = true;
            zombiesSpawnedInWave = 0;
            spawnTimer = 0;
            waveTimer = 0;
        }
        return;
    }

    if (waveInProgress)
    {
        spawnTimer += dt;

        if (spawnTimer >= currentWaveData.spawnDelay &&
            zombiesSpawnedInWave < currentWaveData.zombiesCount)
        {
            spawnTimer = 0;

            if (zombiesSpawnedInWave < currentWaveData.zombies.size())
            {
                int row = currentWaveData.zombies[zombiesSpawnedInWave].first;
                std::string type = currentWaveData.zombies[zombiesSpawnedInWave].second;
                SpawnZombie(row, type);
            }
            else
            {
                int randomRow = rand() % field->get_rows();
                std::string types[] = { "default", "bucket", "runner", "dancer" };
                std::string randomType = types[rand() % 4];
                SpawnZombie(randomRow, randomType);
            }

            zombiesSpawnedInWave++;
        }

        if (zombiesSpawnedInWave >= currentWaveData.zombiesCount)
        {
            bool zombiesAlive = false;
            const std::vector<Object*>& objects = manager->GetObjects();
            for (size_t i = 0; i < objects.size(); ++i)
            {
                Object* obj = objects[i];
                if (obj && obj->isAlive && obj->GetType() == CollisionObject::Zombie)
                {
                    zombiesAlive = true;
                    break;
                }
            }

            if (!zombiesAlive)
            {
                waveInProgress = false;
                currentWave++;

                if (currentWave >= totalWaves || currentWave >= waves.size())
                {
                    return;
                }

                waveDelayActive = true;
                waveTimer = 0;
            }
        }
    }
}

LevelManager::~LevelManager()
{}

sf::Vector2f LevelManager::GetZombieSpawnPosition(int row) const
{
    return { 1100, field->GetCellCenter(row, 0).y + field->get_cell_size().y * 0.25f };
}

sf::Vector2f LevelManager::GetLawnMowerPosition(int row) const
{
    return {
        field->get_field_origin().x - field->get_cell_size().x * 0.5f,
        field->get_field_origin().y + row * field->get_cell_size().y + field->get_cell_size().y * 0.6f
    };
}

sf::Vector2f LevelManager::GetPlantPosition(int row, int col) const
{
    return { field->GetCellCenter(row, col).x,
             field->GetCellCenter(row, col).y + field->get_cell_size().y * 0.2f };
}