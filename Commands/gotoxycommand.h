#ifndef GOTOXYCOMMAND_H
#define GOTOXYCOMMAND_H

#include "commandlistener.h"

class GotoXYCommand
{
public:
    GotoXYCommand();

    void executeCommand(int x, int y);
};

#endif // GOTOXYCOMMAND_H
