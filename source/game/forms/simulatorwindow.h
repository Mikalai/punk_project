#ifndef SIMULATORWINDOW_H
#define SIMULATORWINDOW_H

#include <QMainWindow>
#include "../punk_engine.h"

class GameThread;

namespace Ui {
class SimulatorWindow;
}

class SimulatorWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SimulatorWindow(QWidget *parent = 0);
    ~SimulatorWindow();
    
public slots:

    void startNewGame();

private:
    Ui::SimulatorWindow *ui;

    GameThread* m_game_thread;

    Punk::Application* m_app;
};

#endif // SIMULATORWINDOW_H
