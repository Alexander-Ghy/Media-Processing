#ifndef VIEWERENEMY_H
#define VIEWERENEMY_H

#include <qpixmap.h>
#include <QGraphicsRectItem>
#include "Views/viewers.h"


class ViewerEnemy :public viewers
{
public:
    ViewerEnemy(int x, int y, double sizeTileFinal);
    void dead();

};

#endif // VIEWERENEMY_H
