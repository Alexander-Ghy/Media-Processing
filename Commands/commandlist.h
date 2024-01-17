#include <qobject.h>

#ifndef COMMANDLIST_H
#define COMMANDLIST_H

class CommandList : public QObject
{
    Q_OBJECT
public:
    enum Commandstest
    {
        up,
        down,
        left,
        right,
        rigze,
        gotoXY,
        attackNearestEnemy,
        takeNearestHealthpack,
        help
    };
    Q_ENUM(Commandstest)
};

typedef enum
{
    MAP,
    MAZE,
    COLLIS
} WorldTypes;

#endif // COMMANDLIST_H
