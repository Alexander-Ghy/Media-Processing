#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include "Commands/attacknearestenemycommand.h"
#include "Commands/gotoxycommand.h"
#include "Commands/takenearesthealthpackcommand.h"
#include "Views/graphicsbasedworld.h"
#include "Controllers/worldcontroller.h"
#include "qmetaobject.h"
#include "world.h"
#include "Commands/upcommand.h"
#include "Commands/downcommand.h"
#include "Commands/leftcommand.h"
#include "Commands/rightcommand.h"
#include "Commands/commandlist.h"
#include "world_images/worldmaps.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow * getMainWindow() {return ui;};
    void checkInput(QString key);
    MainWindow * getMain() {return this;};
    void handleCommand(CommandList::Commandstest cmd);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void on_pushButton_PushButton_clicked();
    void on_pushButton_GraphicalView_clicked();

    void on_MainWindow_iconSizeChanged(const QSize &iconSize);

    void on_pushButton_PathfindTest_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_horizontalScrollBar_sliderMoved(int position);

    void on_pushButton_AutoPlay_clicked();

    void on_horizontalScrollBar_2_valueChanged(int value);

    void on_yInput_returnPressed();

    void on_xInput_returnPressed();

    void on_pushButton_ZoomIn_clicked();

    void on_pushButton_ZoomOut_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

public slots:
    void on_energy_changed(int e);
    void on_health_changed(int h);
    void on_enemy_dead();
    void on_stop_game();

signals:
    void executeCommand(CommandList::Commandstest cmd);



private:
    Ui::MainWindow *ui;
    GraphicsBasedWorld* graphicsController;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::shared_ptr<World> world;
    UpCommand *up = new UpCommand();
    DownCommand *down = new DownCommand();
    LeftCommand *left = new LeftCommand();
    RightCommand *right = new RightCommand();
    GotoXYCommand *gotoXY = new GotoXYCommand();
    AttackNearestEnemyCommand *attack = new AttackNearestEnemyCommand();
    TakeNearestHealthpackCommand * takeNearestHp = new TakeNearestHealthpackCommand();
    QString cmdInput;
    QVector<QString> cmdList;
    QMetaEnum cmds;
    QString worldMapSelected = WORLDMAP;
};
#endif // MAINWINDOW_H
