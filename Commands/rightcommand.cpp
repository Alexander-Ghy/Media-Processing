#include "rightcommand.h"

#include <iostream>

RightCommand::RightCommand()
{

}

void RightCommand::executeCommand()
{
    LogicController::getInstance()->moveProtagonist(CommandList::Commandstest::right);
}
