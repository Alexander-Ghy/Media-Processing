#include "healthpackcontroller.h"
#include "Controllers/worldcontroller.h"
#include <iostream>
#include <ostream>

HealthpackController * HealthpackController::instance = 0;
HealthpackController::HealthpackController()
{

}

HealthpackController *HealthpackController::getInstance()
{
    if(!instance) instance = new HealthpackController();
    return instance;
}

void HealthpackController::create()
{
    if(instance != 0)
        return;

    instance = new HealthpackController();
}

void HealthpackController::destroy()
{
    delete instance;
    instance = 0;
}

bool HealthpackController::isHealthpack(std::shared_ptr<Tile> tile)
{
    auto worldCols = WorldController::getInstance()->getWorld()->getCols();
    auto key = (tile->getYPos() * worldCols) + tile->getXPos();
    if (healthpacks.count(key))
    {
        return true;
    }
    return false;
}

void HealthpackController::deleteHealthPack(std::shared_ptr<Tile> tile)
{
    auto worldCols = WorldController::getInstance()->getWorld()->getCols();
    auto key = (tile->getYPos() * worldCols) + tile->getXPos();
    if (healthpacks.count(key))
    {
        healthpacks.erase(key);
    }
}

std::shared_ptr<Tile> HealthpackController::findNearestHealthPack(int x, int y)
{
    std::shared_ptr<Tile> closestHealthPack = std::nullptr_t();
    float distanceInitial = INFINITY;
    for(auto element: healthpacks)
    {
        auto healthpack = element.second;
        float distance = (float) sqrt(pow(healthpack->getXPos() - x, 2) + pow(healthpack->getYPos() - y, 2));
        if (distance < distanceInitial)
        {
            closestHealthPack = healthpack;
            distanceInitial = distance;
        }
    }
    return closestHealthPack;
}


