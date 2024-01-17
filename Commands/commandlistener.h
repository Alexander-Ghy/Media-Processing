#ifndef COMMANDLISTENER_H
#define COMMANDLISTENER_H

#include "Controllers/logiccontroller.h"


class CommandListener
{
public:
    CommandListener();

    void virtual executeCommand() {};
};

#endif // COMMANDLISTENER_H
