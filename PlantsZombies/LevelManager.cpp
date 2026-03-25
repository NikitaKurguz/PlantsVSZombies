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
    Wave wave1;
    wave1.zombiesCount = 3;
    wave1.spawnDelay = 3.0;
    wave1.waveDelay = 3.0;
    wave1.zombies = {
        {3, "dancer"},
        {2, "bucket"},
        {4, "runner"}
    };
    waves.push_back(wave1);

    Wave wave2;
    wave2.zombiesCount = 5;
    wave2.spawnDelay = 2.5f;
    wave2.waveDelay = 3.0f;
    wave2.zombies = {
        {3, "default"},
        {2, "bucket"},
        {1, "default"},
        {4, "default"},
        {3, "runner"}
    };
    waves.push_back(wave2);

    Wave wave3;
    wave3.zombiesCount = 7;
    wave3.spawnDelay = 2.0f;
    wave3.waveDelay = 3.0f;
    wave3.zombies = {
        {3, "bucket"},
        {2, "runner"},
        {1, "default"},
        {4, "bucket"},
        {3, "default"},
        {2, "dancer"},
        {4, "runner"}
    };
    waves.push_back(wave3);

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
    if (manager->IsGameStopped()) return;

    if (currentWave >= totalWaves)
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

                if (currentWave < totalWaves)
                {
                    waveDelayActive = true;
                    waveTimer = 0;
                }
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