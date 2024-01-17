#include "enemycontroller.h"
#include "Controllers/worldcontroller.h"
#include "xenemy.h"
#include <iostream>
#include <ostream>

EnemyController * EnemyController::instance = 0;
EnemyController::EnemyController()
{

}

EnemyController *EnemyController::getInstance()
{
    if(!instance) instance = new EnemyController();
    return instance;
}

void EnemyController::create()
{
    if(instance != 0)
        return;

    instance = new EnemyController();
}

void EnemyController::destroy()
{
    delete instance;
    instance = 0;
}


std::shared_ptr<Enemy> EnemyController::getEnemy(std::shared_ptr<Tile> tile)
{
    auto worldCols = WorldController::getInstance()->getWorld()->getCols();
    auto key = (tile->getYPos() * worldCols) + tile->getXPos();
    if (enemies.count(key))
    {
        return enemies.find(key)->second;
    }
    return nullptr;
}


std::shared_ptr<PEnemy> EnemyController::getPEnemy(std::shared_ptr<Tile> tile)
{
    auto enemy = getEnemy(tile);
    std::shared_ptr<PEnemy> Penemy = std::dynamic_pointer_cast<PEnemy>(enemy);
    if(Penemy!=nullptr){
        return Penemy;
    }
    return nullptr;
}

std::shared_ptr<XEnemy> EnemyController::getXEnemy(std::shared_ptr<Tile> tile)
{
    auto enemy = getEnemy(tile);
    std::shared_ptr<XEnemy> Xenemy = std::dynamic_pointer_cast<XEnemy>(enemy);
    if(Xenemy!=nullptr){
        return Xenemy;
    }
    return nullptr;
}

bool EnemyController::isPEnemy(std::shared_ptr<Enemy> enemy)
{
    std::shared_ptr<PEnemy> Penemy = std::dynamic_pointer_cast<PEnemy>(enemy);

    {
        if(Penemy!=nullptr){
            return true;
        }
    }
    return false;
}


bool EnemyController::isXEnemy(std::shared_ptr<Enemy> enemy)
{
    std::shared_ptr<XEnemy> Xenemy = std::dynamic_pointer_cast<XEnemy>(enemy);

    {
        if(Xenemy!=nullptr){
            return true;
        }
    }
    return false;
}

/*void EnemyController::deleteEnemy(std::shared_ptr<Tile> tile)
{
    auto worldCols = WorldController::getInstance()->getWorld()->getCols();
    auto key = (tile->getYPos() * worldCols) + tile->getXPos();
    if (enemies.count(key))
    {
        enemies.erase(key);
    }
}*/

std::shared_ptr<Enemy> EnemyController::findNearestEnemy(int x, int y)
{
    std::shared_ptr<Enemy> closestEnemy = std::nullptr_t();
    float distanceInitial = std::numeric_limits<float>::infinity();
    for(auto element: enemies)
    {
        auto enemy = element.second;
        if (enemy->getDefeated())
            continue;
        float distance = (float) sqrt(pow(enemy->getXPos() - x, 2) + pow(enemy->getYPos() - y, 2));
        if (distance < distanceInitial)
        {
            closestEnemy = enemy;
            distanceInitial = distance;
        }
    }
    return closestEnemy;
}

bool EnemyController::enemyOnTile(int x, int y)
{
    auto worldCols = WorldController::getInstance()->getWorld()->getCols();
    auto key = (y * worldCols) + x;
    if (enemies.count(key))
    {
        return true;
    }
    return false;
}

bool EnemyController::EnemyOnPath(std::vector<Tile *>* path)
{
    for (auto& tile: *path)
    {
        if (enemyOnTile(tile->getXPos(),tile->getYPos()))
        {
            return true;
        }
    }
    return false;
}


