#include "takenearesthealthpackcommand.h"

#include "Controllers/healthpackcontroller.h"

#include <Controllers/protagonistcontroller.h>


TakeNearestHealthpackCommand::TakeNearestHealthpackCommand()
{

}

void TakeNearestHealthpackCommand::executeCommand()
{
    auto protagonist = ProtagonistController::getInstance()->getProtagonist();
    Point pointProtagonist = Point();
    pointProtagonist.xPos = protagonist->getXPos();
    pointProtagonist.yPos = protagonist->getYPos();
    auto healthPack = HealthpackController::getInstance()->findNearestHealthPack(pointProtagonist.xPos, pointProtagonist.yPos);
    Point pointHealthPack = Point();
    pointHealthPack.xPos = healthPack->getXPos();
    pointHealthPack.yPos = healthPack->getYPos();
    auto algorithm = LogicController::getInstance()->getAlgorithm();
    algorithm->setUpNewRun();
    algorithm->Solve(&pointProtagonist, &pointHealthPack);
    auto solution = algorithm->getSolution();
    LogicController::getInstance()->FollowPath(&solution);
}
