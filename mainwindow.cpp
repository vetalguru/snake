#include "mainwindow.h"

#include <QAction>
#include <QApplication>
#include <QIcon>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>
#include <QStatusBar>

#include "snakewidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // Central Widget
    SnakeWidget *centralWidget = new SnakeWidget(this);
    setCentralWidget(centralWidget);

    initActions();

    // Connections
    connect(startGameAction, SIGNAL(triggered()), centralWidget, SLOT(startGame()));
    connect(pauseGameAction, SIGNAL(triggered()), centralWidget, SLOT(pauseGame()));
    connect(stopGameAction, SIGNAL(triggered()), centralWidget, SLOT(stopGame()));
    connect(exitAction, &QAction::triggered, qApp, QApplication::quit);
    connect(aboutQtAction, &QAction::triggered, qApp, QApplication::aboutQt);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutDialog);

    connect(centralWidget, SIGNAL(appleCounterChanged(int)), this, SLOT(changeAppleNumber(int)));
    connect(centralWidget, SIGNAL(snakeSizeChanged(int)), this, SLOT(changeSnakeLength(int)));

    // Main menu
    // File
    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(exitAction);

    QMenu *gameMenu = menuBar()->addMenu("&Game");
    gameMenu->addAction(startGameAction);
    gameMenu->addAction(pauseGameAction);
    gameMenu->addAction(stopGameAction);

    // About
    QMenu *aboutMenu = menuBar()->addMenu("&Help");
    aboutMenu->addAction(aboutQtAction);
    aboutMenu->addAction(aboutAction);

    // Toolbar
    QToolBar *toolBar = new QToolBar(this);
    toolBar->addAction(startGameAction);
    toolBar->addAction(pauseGameAction);
    toolBar->addAction(stopGameAction);
    toolBar->addAction(exitAction);
    toolBar->addAction(aboutAction);
    addToolBar(toolBar);

    initStatusBar();
}

MainWindow::~MainWindow() {
    deleteActions();
}

void MainWindow::aboutDialog() {
    QMessageBox msg;
    msg.setText("Snake");
    msg.exec();
}

void MainWindow::changeAppleNumber(int number) {
    m_appleCounterLabel->setText(QString::number(number));
}

void MainWindow::changeSnakeLength(int size) {
    m_snakeLengthLabel->setText(QString::number(size));
}

void MainWindow::initActions() {
    startGameAction = new QAction(QIcon::fromTheme("media-playback-start"), "&Start", this);
    pauseGameAction = new QAction(QIcon::fromTheme("media-playback-pause"), "&Pause", this);
    stopGameAction = new QAction(QIcon::fromTheme("media-playback-stop"), "S&top", this);
    exitAction = new QAction(QIcon::fromTheme("application-exit"), "&Exit", this);
    aboutQtAction = new QAction(QIcon::fromTheme("help-about"), "About &Qt ...", this);
    aboutAction = new QAction(QIcon::fromTheme("help-about"), "&About ...", this);
}

void MainWindow::deleteActions() {
    delete aboutAction;
    delete aboutQtAction;
    delete exitAction;
    delete stopGameAction;
    delete pauseGameAction;
    delete startGameAction;
}

void MainWindow::initStatusBar() {
    statusBar()->addPermanentWidget(new QLabel("Apple number: "));
    m_appleCounterLabel = new QLabel(QString::number(0));
    statusBar()->addPermanentWidget(m_appleCounterLabel);
    statusBar()->addPermanentWidget(new QLabel("| Snake size: "));
    m_snakeLengthLabel = new QLabel(QString::number(0));
    statusBar()->addPermanentWidget(m_snakeLengthLabel);
}
