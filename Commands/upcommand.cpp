#include "upcommand.h"

#include <iostream>

UpCommand::UpCommand()
{

}

void UpCommand::executeCommand()
{
    LogicController::getInstance()->moveProtagonist(CommandList::Commandstest::up);
}
