#ifndef DOWNCOMMAND_H
#define DOWNCOMMAND_H

#include "commandlistener.h"

class DownCommand : public CommandListener
{
public:
    DownCommand();

    void executeCommand() override;
};

#endif // DOWNCOMMAND_H
