#ifndef HEALTHPACKCONTROLLER_H
#define HEALTHPACKCONTROLLER_H

#include "world.h"
#include "logiccontroller.h"
#include <random>

class HealthpackController
{
public:
    HealthpackController();

    static HealthpackController * getInstance();
    static void create();
    static void destroy();

    std::unordered_map<int,std::shared_ptr<Tile>> * getHealthpacks(){return &healthpacks;};
    void setHealthPacks(std::unordered_map<int,std::shared_ptr<Tile>> healthPacksNew) {healthpacks = healthPacksNew;};
    bool isHealthpack(std::shared_ptr<Tile> tile);
    void deleteHealthPack(std::shared_ptr<Tile> tile);
    std::shared_ptr<Tile> findNearestHealthPack(int x, int y);

private:
    static HealthpackController* instance;
    std::unordered_map<int,std::shared_ptr<Tile>> healthpacks;
};

#endif // HEALTHPACKCONTROLLER_H
