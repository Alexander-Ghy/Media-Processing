#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Controllers/logiccontroller.h"
#include "Controllers/protagonistcontroller.h"
#include "ui_mainwindow.h"
#include "world.h"
#include "Views/textbasedview.h"
#include "Controllers/logiccontroller.h"
#include "Controllers/worldcontroller.h"
#include "Commands/commandlist.h"
//#include "Controllers/graphicscontroller.h"
#include <QGraphicsScene>
#include <QFile>
#include <iostream>
#include <QDir>
#include "world_images/worldmaps.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QFile>
#include <iostream>
#include <QDir>
#include <QKeyEvent>
#include <QStringBuilder>
#include <QString>
#include <QLabel>
#include <QProgressBar>
#include <QString>
#include <QMetaEnum>

#include <Views/graphicsbasedworld.h>
#include <Views/textbasedview.h>

#include <Controllers/enemycontroller.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    installEventFilter(this);
    ui->pushButton_PushButton->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_GraphicalView->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_AutoPlay->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_PathfindTest->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_ZoomIn->setFocusPolicy(Qt::NoFocus);
    ui->pushButton_ZoomOut->setFocusPolicy(Qt::NoFocus);
    ui->commandView->setFocusPolicy(Qt::NoFocus);
    ui->commandInput->setFocusPolicy(Qt::NoFocus);
    ui->comboBox->setFocusPolicy(Qt::NoFocus);
    setFocus(); // focus for arrow keys

    ui->commandView->setVisible(false);
    ui->cmdViewLabel->setVisible(false);
    ui->commandInput->setVisible(false);
    //ui->text_algorithm->setVisible(false); // only set true when doing the pathfind test
    ui->cmdInputLabel->setVisible(false);
    ui->xLabel->setVisible(false);
    ui->yLabel->setVisible(false);
    ui->xInput->setVisible(false);
    ui->yInput->setVisible(false);

    ui->xInput->setValidator(new QIntValidator(0, 100, this));
    ui->yInput->setValidator(new QIntValidator(0, 100, this));

    QPalette pe = ui->energyBar->palette();
    QPalette ph = ui->healthBar->palette();
    pe.setColor(QPalette::Highlight, QColor(0, 255, 0, 127));
    ph.setColor(QPalette::Highlight, QColor(0, 255, 0, 127));
    ui->energyBar->setPalette(pe);
    ui->healthBar->setPalette(ph);

    cmds = QMetaEnum::fromType<CommandList::Commandstest>();
    for(int i = 0; i < cmds.keyCount(); i++)
    {
        CommandList::Commandstest cmd = (CommandList::Commandstest) cmds.value(i);
        cmdList.push_back(cmds.valueToKey(cmd));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete graphicsController;
}

void MainWindow::on_pushButton_GraphicalView_clicked()
{
    ui->commandView->setVisible(false);
    ui->cmdViewLabel->setVisible(false);
    ui->commandInput->setVisible(false);
    ui->cmdInputLabel->setVisible(false);
    ui->xLabel->setVisible(false);
    ui->yLabel->setVisible(false);
    ui->xInput->setVisible(false);
    ui->yInput->setVisible(false);
    ui->commandInput->setText("");
    //ui->text_algorithm->setVisible(false);
    //LogicController::getInstance()->setCurrView(nullptr);

    auto view = ui->mainGraphicsView;
    GraphicsBasedWorld::getInstance()->setView(view);
    GraphicsBasedWorld::getInstance()->setString(worldMapSelected);
    LogicController::getInstance()->setCurrView(LogicController::Curr::graphical);
    GraphicsBasedWorld::getInstance()->init();
    //if(LogicController::getInstance()->getCurrView().get() != GraphicsBasedWorld::getInstance()) LogicController::getInstance()->setCurrView(nullptr);
    GraphicsBasedWorld::getInstance()->createView();

    //GraphicsBasedWorld::getInstance()->drawWorld(view,*string);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(!ProtagonistController::getInstance()->isDead())
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent *ke = dynamic_cast<QKeyEvent *>(event);
            keyPressEvent(ke);
            return true;
        }
        return QObject::eventFilter(obj, event);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!ProtagonistController::getInstance()->isDead())
    {
        switch(event->key())
        {
        case Qt::Key_Up:
            up->executeCommand();
            break;
        case Qt::Key_Down:
            down->executeCommand();
            break;
        case Qt::Key_Left:
            left->executeCommand();
            break;
        case Qt::Key_Right:
            right->executeCommand();
            break;
        default:
            setFocus();
            checkInput(event->text());
            break;
        }
    }
}

void MainWindow::checkInput(QString key)
{
    QVector<QString> vec;
    if(cmdInput.size() == 0) ui->commandInput->setText("");
    int initSize = cmdInput.size();
    cmdInput = cmdInput % key;
    int pos = 0;
    for(int i = 0; i < cmdList.size(); i++)
    {
        if((cmdList[i].size() > initSize))
        {
            if((cmdList[i].sliced(0, cmdInput.size()) == cmdInput))
            {
                ui->commandInput->setText(cmdInput);
                vec.push_back(cmdList[i]);
                pos = i;
            }
        }
    }
    if(vec.size() == 1)
    {
        cmdInput = "";
        cmdInput = vec[0];
        ui->commandInput->setText(cmdInput);
        cmdInput = "";
        CommandList::Commandstest cmd = (CommandList::Commandstest) cmds.value(pos);
        handleCommand(cmd);
    } else if(vec.size() == 0)
    {
        cmdInput = "";
        ui->commandInput->setText("");
    }
}

void MainWindow::handleCommand(CommandList::Commandstest cmd)
{
    ui->commandView->setText("");
    ui->commandView->setVisible(false);
    ui->cmdViewLabel->setVisible(false);
    ui->xLabel->setVisible(false);
    ui->yLabel->setVisible(false);
    ui->xInput->setVisible(false);
    ui->yInput->setVisible(false);

    switch(cmd)
    {
    case CommandList::Commandstest::up:
        up->executeCommand();
        break;
    case CommandList::Commandstest::down:
        down->executeCommand();
        break;
    case CommandList::Commandstest::left:
        left->executeCommand();
        break;
    case CommandList::Commandstest::right:
        right->executeCommand();
        break;
    case CommandList::Commandstest::gotoXY:
        ui->xLabel->setVisible(true);
        ui->yLabel->setVisible(true);
        ui->xInput->setVisible(true);
        ui->yInput->setVisible(true);
        ui->yInput->setDisabled(true);
        break;
    case CommandList::Commandstest::attackNearestEnemy:
        attack->executeCommand();
        break;
    case CommandList::Commandstest::takeNearestHealthpack:
        takeNearestHp->executeCommand();
        break;
    case CommandList::Commandstest::help:
    {
        QString cmdView = "";
        for(int i = 0; i < cmdList.size(); i++)
        {
            cmdView = cmdView % cmdList[i] % "\n";
        }
        ui->commandView->setVisible(true);
        ui->cmdViewLabel->setVisible(true);
        ui->commandView->setText(cmdView);
        break;
    }
    default:
        break;
    }
}

void MainWindow::on_pushButton_PushButton_clicked()
{
    ui->mainGraphicsView->setScene(TextBasedView::getInstance()->getScene()); // for TextView
    QRect rect=ui->mainGraphicsView->viewport()->rect();
    if(WorldController::getInstance()->getType() == WorldTypes::MAP)
    {
        TextBasedView::getInstance()->getScene()->setSceneRect(QRectF(-50,-50,0,0));
    }
    else
    {
        TextBasedView::getInstance()->getScene()->setSceneRect(QRectF(-50,-50,rect.width(),rect.height()));
    }
    ui->commandView->setVisible(false);
    ui->cmdViewLabel->setVisible(false);
    ui->commandInput->setVisible(true);
    ui->cmdInputLabel->setVisible(true);

    if(!TextBasedView::getInstance()->getInitialized())TextBasedView::getInstance()->replaceGridValue(ProtagonistController::getInstance()->getProtagonist()->getXPos(),ProtagonistController::getInstance()->getProtagonist()->getXPos(), (char*) "P");
    LogicController::getInstance()->setCurrView(LogicController::Curr::text);
    TextBasedView::getInstance()->createView();
    TextBasedView::getInstance()->setInitialized(true);
}

void MainWindow::on_MainWindow_iconSizeChanged(const QSize &iconSize)
{
}

void MainWindow::on_energy_changed(int e)
{
    QPalette p = ui->energyBar->palette();
    ui->energyBar->setValue(e);
    if(ui->energyBar->value() < 50)
    {
        p.setColor(QPalette::Highlight, QColor(255, 0, 0, 127));
    } else
    {
        p.setColor(QPalette::Highlight, QColor(0, 255, 0, 127));
    }
    ui->energyBar->setPalette(p);
}

void MainWindow::on_health_changed(int h)
{
    QPalette p = ui->healthBar->palette();
    ui->healthBar->setValue(h);
    if(ui->healthBar->value() < 50)
    {
        p.setColor(QPalette::Highlight, QColor(255, 0, 0, 127));
    } else
    {
        p.setColor(QPalette::Highlight, QColor(0, 255, 0, 127));
    }
    ui->healthBar->setPalette(p);
}

void MainWindow::on_enemy_dead()
{
    ui->energyBar->setValue(100.0f);
}


void MainWindow::on_stop_game()
{
    ui->energyBar->setDisabled(true);
    ui->healthBar->setDisabled(true);
}


void MainWindow::on_pushButton_PathfindTest_clicked()
{
    ui->commandView->setVisible(false);
    ui->commandInput->setVisible(false);
    ui->text_algorithm->setVisible(true); //make this visible
    ui->commandInput->setText("");

    LogicController::getInstance()->setCurrView(LogicController::Curr::graphical);
    auto string = new QString(worldMapSelected);

    auto view = ui->mainGraphicsView;

    if(GraphicsBasedWorld::getInstance()->drawPathfindingTest(view, *string))
    {
        ui->text_algorithm->setVisible(false);
        return;
    }
    auto executionTime = LogicController::getInstance()->getAlgorithm()->getExecutionTime(); // /1000000;
    //QString executionTimeString = QString::number(executionTime);
    std::string executionTimeString = std::to_string(executionTime);
    QString text = QString::fromStdString(executionTimeString);
    ui->text_algorithm->setText("Execution time in microseconds: " + text);
    std::cout <<"Time of execution algorithm:" << std::endl;
    std::cout <<"\tmicroseconds: " << executionTimeString << std::endl;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    TextBasedView::getInstance()->setInitialized(false);
    std::cout<<"index is currently: " << index << std::endl;
    int amountOfEnemies = 0;
    int amountOfHealthpacks = 0;
    switch(index)
    {
    case 0:
        worldMapSelected = WORLDMAP;
        amountOfEnemies = 150;
        amountOfHealthpacks = 300;
        WorldController::getInstance()->setType(WorldTypes::MAP);
        break;
    case 1:
        worldMapSelected = WORLDMAP4;
        amountOfEnemies = 30;
        amountOfHealthpacks = 50;
        WorldController::getInstance()->setType(WorldTypes::MAP);
        break;
    case 2:
        worldMapSelected = MAZE1;
        amountOfEnemies = 30;
        amountOfHealthpacks = 50;
        WorldController::getInstance()->setType(WorldTypes::MAZE);
        break;
    case 3:
        worldMapSelected = MAZE2;
        amountOfEnemies = 30;
        amountOfHealthpacks = 50;
        WorldController::getInstance()->setType(WorldTypes::MAZE);
        break;
    case 4:
        worldMapSelected = MAZE3;
        WorldController::getInstance()->setType(WorldTypes::MAZE);
        break;
    case 5:
        worldMapSelected = COLLIS0;
        WorldController::getInstance()->setType(WorldTypes::COLLIS);
        break;
    case 6:
        worldMapSelected = COLLIS1;
        WorldController::getInstance()->setType(WorldTypes::COLLIS);
        break;
    case 7:
        worldMapSelected = COLLIS2;
        WorldController::getInstance()->setType(WorldTypes::COLLIS);
        break;
    case 8:
        worldMapSelected = COLLIS3;
        WorldController::getInstance()->setType(WorldTypes::COLLIS);
        break;
    case 9:
        worldMapSelected = COLLIS4;
        WorldController::getInstance()->setType(WorldTypes::COLLIS);
        break;
    default:
        break;
    }
    LogicController::getInstance()->createWorld(worldMapSelected,amountOfEnemies,amountOfHealthpacks,0.25f);
    //refresh the view to our 2D view
    LogicController::getInstance()->initViews();
    if(LogicController::getInstance()->getCurrView() == TextBasedView::getInstance())
    {
        //LogicController::getInstance()->initViews();
        on_pushButton_PushButton_clicked();
    }
    else
    {
        on_pushButton_GraphicalView_clicked();
    }

    connect(LogicController::getInstance(), &LogicController::healthpack, LogicController::getInstance()->getCurrView(), &Views::on_healthpack);
    connect(LogicController::getInstance(), &LogicController::gameOver, LogicController::getInstance()->getCurrView(), &Views::on_game_over);
    connect(LogicController::getInstance(), &LogicController::attack, LogicController::getInstance()->getCurrView(), &Views::on_attack);
    connect(ProtagonistController::getInstance()->getProtagonist().get(), &Protagonist::posChanged, LogicController::getInstance()->getCurrView(), &Views::on_position_changed);
    connect(ProtagonistController::getInstance()->getProtagonist().get(), &Protagonist::energyChanged, this, &MainWindow::on_energy_changed);
    connect(ProtagonistController::getInstance()->getProtagonist().get(), &Protagonist::healthChanged, this, &MainWindow::on_health_changed);
    connect(LogicController::getInstance()->getCurrView(), &Views::stopGame, this, &MainWindow::on_stop_game);
}

void MainWindow::on_horizontalScrollBar_sliderMoved(int position)
{
    LogicController::getInstance()->getAlgorithm()->setWeightUser(position);
}

void MainWindow::on_pushButton_AutoPlay_clicked()
{
    LogicController::getInstance()->autoPlay();
}


void MainWindow::on_horizontalScrollBar_2_valueChanged(int value)
{
    LogicController::getInstance()->changeGraphicsDelay(value);
}
void MainWindow::on_yInput_returnPressed()
{
    gotoXY->executeCommand((ui->xInput->text()).toInt(), (ui->yInput->text()).toInt());
    ui->xLabel->setVisible(false);
    ui->yLabel->setVisible(false);
    ui->xInput->setVisible(false);
    ui->yInput->setVisible(false);
}


void MainWindow::on_xInput_returnPressed()
{
    ui->yInput->setDisabled(false);
}


void MainWindow::on_pushButton_ZoomIn_clicked()
{
    GraphicsBasedWorld::getInstance()->zoomIn();
}


void MainWindow::on_pushButton_ZoomOut_clicked()
{
    GraphicsBasedWorld::getInstance()->zoomOut();
}


void MainWindow::on_pushButton_clicked()
{
    LogicController::getInstance()->buttonAstar();
}


void MainWindow::on_pushButton_2_clicked()
{
    LogicController::getInstance()->buttonAstarBest();
}

