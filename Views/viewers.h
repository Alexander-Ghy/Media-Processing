#ifndef VIEWERS_H
#define VIEWERS_H

#include <qpixmap.h>
#include <QGraphicsRectItem>


class viewers: public QPixmap, public QGraphicsRectItem
{
public:

    viewers(int x, int y, double sizeTileFinal);
    int getXPos(){return XPos;}
    int getYPos(){return YPos;}

protected:
    int XPos;
    int YPos;
    std::vector<std::unique_ptr<QGraphicsPixmapItem>> images;
};


#endif // VIEWERS_H
