#ifndef ATTACKNEARESTENEMYCOMMAND_H
#define ATTACKNEARESTENEMYCOMMAND_H

#include "commandlistener.h"

class AttackNearestEnemyCommand : public CommandListener
{
public:
    AttackNearestEnemyCommand();

    void executeCommand() override;
};

#endif // ATTACKNEARESTENEMYCOMMAND_H
