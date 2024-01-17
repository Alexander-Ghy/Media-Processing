#include "downcommand.h"
#include "commandlist.h"

#include <iostream>

DownCommand::DownCommand()
{

}

void DownCommand::executeCommand()
{
    LogicController::getInstance()->moveProtagonist(CommandList::Commandstest::down);
}
