#include "mainwindow.h"
#include <iostream>
#include <QApplication>
#include <algorithm/astar.h>
#include <Controllers/protagonistcontroller.h>
#include <Controllers/worldcontroller.h>
#include <Views/textbasedview.h>
#include "world_images/worldmaps.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto w = std::make_shared<MainWindow>();

    auto * logic_cntrl = LogicController::getInstance();

    //our load in world is WORLDMAP
    auto string = new QString(WORLDMAP);
    WorldController::getInstance()->setType(WorldTypes::MAP);
    logic_cntrl->setMainWindow(w);

    logic_cntrl->createWorld(*string,150,300,0.25f);
    logic_cntrl->initViews();
    w->show();

    return a.exec();

    //keep the next code, its the show pathfinder in the terminal
    /*
    auto algorithm = Astar();
    algorithm.setWeightUser(10);
    WorldController::getInstance()->SetUp(MAZE3,0,0,0);
    auto tilesMap = WorldController::getInstance()->getTilesUnorderedMap();
    algorithm.setUpInitial(tilesMap);
    Point start = Point();
    start.xPos = 0;
    start.yPos = 22;
    Point goal = Point();
    goal.xPos = 1200;
    goal.yPos = 1205;
    algorithm.Solve(&start,&goal);
    //algorithm.printSolution();

    return 0; */
}
