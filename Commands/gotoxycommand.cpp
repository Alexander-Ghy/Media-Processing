#include "gotoxycommand.h"
#include <iostream>
#include <Controllers/protagonistcontroller.h>

GotoXYCommand::GotoXYCommand()
{

}

void GotoXYCommand::executeCommand(int x, int y)
{
    auto protagonist = ProtagonistController::getInstance()->getProtagonist();
    Point pointProtagonist = Point();
    pointProtagonist.xPos = protagonist->getXPos();
    pointProtagonist.yPos = protagonist->getYPos();
    Point goal = Point();
    goal.xPos = x;
    goal.yPos = y;
    auto algorithm = LogicController::getInstance()->getAlgorithm();
    algorithm->setUpNewRun();
    algorithm->Solve(&pointProtagonist, &goal);
    auto solution = algorithm->getSolution();
    LogicController::getInstance()->FollowPath(&solution);
}
