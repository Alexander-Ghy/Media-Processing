#ifndef VIEWS_H
#define VIEWS_H

#include <QObject>

class Views : public QObject
{
    Q_OBJECT

public:
    Views();
    virtual void createView(){};

public slots:
    virtual void on_position_changed(int , int ){};
    virtual void on_game_over(int , int ){};
    virtual void on_attack(){};
    virtual void on_healthpack(){};
    virtual void on_poisoned(){};
    virtual void on_XEnemy_changed(int , int ){};

signals:
    virtual void stopGame();

};

#endif // VIEWS_H
