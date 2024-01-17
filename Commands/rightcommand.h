#ifndef RIGHTCOMMAND_H
#define RIGHTCOMMAND_H

#include "commandlistener.h"

class RightCommand : public CommandListener
{
public:
    RightCommand();

    void executeCommand() override;
};

#endif // RIGHTCOMMAND_H
