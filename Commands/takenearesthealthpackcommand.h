#ifndef TAKENEARESTHEALTHPACKCOMMAND_H
#define TAKENEARESTHEALTHPACKCOMMAND_H

#include "commandlistener.h"

class TakeNearestHealthpackCommand : public CommandListener
{
public:
    TakeNearestHealthpackCommand();

    void executeCommand() override;
};

#endif // TAKENEARESTHEALTHPACKCOMMAND_H
