#ifndef UPCOMMAND_H
#define UPCOMMAND_H

#include "commandlistener.h"

class UpCommand : public CommandListener
{
public:
    UpCommand();

    void executeCommand() override;
};

#endif // UPCOMMAND_H
