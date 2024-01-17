#include "leftcommand.h"

#include <iostream>

LeftCommand::LeftCommand()
{

}

void LeftCommand::executeCommand()
{
    LogicController::getInstance()->moveProtagonist(CommandList::Commandstest::left);
}
