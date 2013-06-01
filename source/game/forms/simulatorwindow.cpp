#include "gamethread.h"
#include "simulatorwindow.h"
#include "ui_simulatorwindow.h"

SimulatorWindow::SimulatorWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SimulatorWindow)
{
    ui->setupUi(this);
    m_game_thread = nullptr;
}

SimulatorWindow::~SimulatorWindow()
{
    delete ui;
    delete m_game_thread;
    delete m_app;
}

void SimulatorWindow::startNewGame()
{
    if (m_game_thread)
    {
        m_game_thread->quit();
        delete m_game_thread;
        delete m_app;
    }
    m_game_thread = new GameThread;
    m_game_thread->start();

    Punk::Config config;
    config.gpu_config.m_hwnd = (HWND)winId();

    m_app = new Punk::Application;
    m_app->Init(config);

    m_app->Run();
}
