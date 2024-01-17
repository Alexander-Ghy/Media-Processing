#ifndef WORLDCONTROLLER_H
#define WORLDCONTROLLER_H

#include <iostream>

#include "Views/graphicsbasedworld.h"
#include "world.h"
#include "Commands/commandlist.h"

class WorldController
{
public:
    WorldController();

    static WorldController * getInstance();
    static void create();
    static void destroy();

    void SetUp(QString filename, unsigned int nrOfEnemies, unsigned int nrOfHealthpacks, float pRatio = 0.25f);
    std::map<int,std::shared_ptr<Tile>> * getTilesUnorderedMap(){return &tiles;};
    std::shared_ptr<World> getWorld(){return world;};
    std::shared_ptr<Tile> getTileByXY(int x, int y);
    void setType(WorldTypes t){type = t;};
    WorldTypes getType(){return type;};

private:
    static WorldController* instance;
    std::map<int,std::shared_ptr<Tile>> tiles;
    std::shared_ptr<World> world;
    WorldTypes type;
};

#endif // WORLDCONTROLLER_H
