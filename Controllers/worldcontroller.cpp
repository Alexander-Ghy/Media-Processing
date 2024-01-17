#include "worldcontroller.h"
#include "Controllers/enemycontroller.h"
#include "Controllers/healthpackcontroller.h"
#include "Controllers/protagonistcontroller.h"
#include <random>
#include <ctime>


WorldController * WorldController::instance = 0;
WorldController::WorldController()
{

}

WorldController *WorldController::getInstance()
{
    if(!instance) instance = new WorldController();
    return instance;
}

void WorldController::create()
{
    if(instance != 0)
        return;

    instance = new WorldController();
}

void WorldController::destroy()
{
    delete instance;
    instance = 0;
}

void WorldController::SetUp(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio)
{
    world = std::make_shared<World>();
    world->createWorld(filename, nrOfEnemies, nrOfHealthpacks, pRatio);

    //Delete the current tiles
    //tiles.clear(); //smart pointers deleting the object ?

    std::map<int,std::shared_ptr<Tile>> tilesTemp;
    //Get the tiles
    for (auto& tileInitial: world->getTiles())
    {
        auto xPos = tileInitial->getXPos();
        auto yPos = tileInitial->getYPos();
        auto keyValue = (yPos * world->getCols()) + xPos;
        std::shared_ptr<Tile> tile = std::move(tileInitial);
        tilesTemp.emplace(keyValue, tile);
    }
    tiles = tilesTemp;

    //Get  the enemies
    std::unordered_map<int,std::shared_ptr<Enemy>> enemies;
    for (auto& enemyInitial: world->getEnemies())
    {
        auto xPos = enemyInitial->getXPos();
        auto yPos = enemyInitial->getYPos();
        auto keyValue = (yPos * world->getCols()) + xPos;
        std::shared_ptr<Enemy> enemy = std::move(enemyInitial);
        enemies.emplace(keyValue, enemy);
    }


    //Get the healthpacks
    std::unordered_map<int,std::shared_ptr<Tile>> healthPacks;
    for (auto& healthPackInitial: world->getHealthPacks())
    {
        auto xPos = healthPackInitial->getXPos();
        auto yPos = healthPackInitial->getYPos();
        auto keyValue = (yPos * world->getCols()) + xPos;
        std::shared_ptr<Tile> healthpack = std::move(healthPackInitial);
        healthPacks.emplace(keyValue, healthpack);
    }
    HealthpackController::getInstance()->setHealthPacks(healthPacks);

    ProtagonistController::getInstance()->setProtagonist(world->getProtagonist());

    ProtagonistController::getInstance()->addVisitedTile(getTileByXY(ProtagonistController::getInstance()->getProtagonist()->getXPos(), ProtagonistController::getInstance()->getProtagonist()->getYPos()));

    //add XEnemies
    /*std::srand(std::time(nullptr));
    int amount = nrOfEnemies/4;
    for(int i = 0; i< amount; i++){
        auto xPos = std::rand()%world->getCols();
        auto yPos = std::rand()%world->getRows();
        auto key = (yPos * world->getCols()) + xPos;
        if (!enemies.count(key) && !healthPacks.count(key))
        {
            int k = key;
            int x = xPos;
            int y = yPos;


            std::unique_ptr<XEnemy> xenem = std::make_unique<XEnemy>(x, y, 20);
            auto & xe = xenem;
            std::shared_ptr<Enemy> e = std::move(xe);
            enemies.emplace(k, e);
        }
    }*/
    EnemyController::getInstance()->setEnemies(enemies);
}

std::shared_ptr<Tile> WorldController::getTileByXY(int x, int y)
{
    auto keyValue = (y * world->getCols()) + x;
    if (tiles.count(keyValue))
    {
        return tiles.find(keyValue)->second;
    }
    return nullptr;
}
