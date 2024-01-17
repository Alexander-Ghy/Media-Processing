#ifndef LEFTCOMMAND_H
#define LEFTCOMMAND_H

#include "commandlistener.h"

class LeftCommand : public CommandListener
{
public:
    LeftCommand();

    void executeCommand() override;
};

#endif // LEFTCOMMAND_H
