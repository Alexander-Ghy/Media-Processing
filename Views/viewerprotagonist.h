#ifndef VIEWERPROTAGONIST_H
#define VIEWERPROTAGONIST_H

#include <qpixmap.h>
#include <QGraphicsRectItem>
#include <iostream>
#include <QGraphicsPixmapItem>
#include "Views/viewers.h"


class ViewerProtagonist : public viewers
{
public:
    ViewerProtagonist(int X, int y, double sizeTileFinal);

    void die();
    void poisoned();
    void health();
    void moved();
    void attack();

private:
    bool action;
    bool state;




};

#endif // VIEWERPROTAGONIST_H
