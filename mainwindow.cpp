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
    initCenterWidget();
    initActions();
    initConnections();
    initMainMenu();
    initToolBar();
    initStatusBar();
}

MainWindow::~MainWindow() {
    deleteActions();
}

void MainWindow::aboutDialog() {
    QMessageBox msg;
    msg.setText("The game involves controlling a single block or snakehead"
                "by turning only left or right by ninety degrees until you"
                "manage to eat an apple. When you get the apple, the Snake"
                "grows an extra block or body segment."
                "If, or rather when, the snake bumps into the edge of the"
                "screen or accidentally eats himself the game is over. The"
                "more apples the snake eats the higher the score.");
    msg.exec();
}

void MainWindow::changeAppleNumber(int number) {
    m_appleCounterLabel->setText(QString::number(number));
}

void MainWindow::changeSnakeLength(int size) {
    m_snakeLengthLabel->setText(QString::number(size));
}

void MainWindow::initCenterWidget() {
    SnakeWidget *centralWidget = new SnakeWidget(this);
    setCentralWidget(centralWidget);
}

void MainWindow::initActions() {
    startGameAction = new QAction(QIcon::fromTheme("media-playback-start"), "&Start", this);
    pauseGameAction = new QAction(QIcon::fromTheme("media-playback-pause"), "&Pause", this);
    stopGameAction = new QAction(QIcon::fromTheme("media-playback-stop"), "S&top", this);
    exitAction = new QAction(QIcon::fromTheme("application-exit"), "&Exit", this);
    aboutQtAction = new QAction(QIcon::fromTheme("help-about"), "About &Qt ...", this);
    aboutAction = new QAction(QIcon::fromTheme("help-about"), "&About ...", this);
}

void MainWindow::initConnections() {
    connect(startGameAction, SIGNAL(triggered()), centralWidget(), SLOT(startGame()));
    connect(pauseGameAction, SIGNAL(triggered()), centralWidget(), SLOT(pauseGame()));
    connect(stopGameAction, SIGNAL(triggered()), centralWidget(), SLOT(stopGame()));
    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutDialog()));

    connect(centralWidget(), SIGNAL(appleCounterChanged(int)), this, SLOT(changeAppleNumber(int)));
    connect(centralWidget(), SIGNAL(snakeSizeChanged(int)), this, SLOT(changeSnakeLength(int)));
}

void MainWindow::initMainMenu() {
    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(exitAction);

    QMenu *gameMenu = menuBar()->addMenu("&Game");
    gameMenu->addAction(startGameAction);
    gameMenu->addAction(pauseGameAction);
    gameMenu->addAction(stopGameAction);

    QMenu *aboutMenu = menuBar()->addMenu("&Help");
    aboutMenu->addAction(aboutQtAction);
    aboutMenu->addAction(aboutAction);
}

void MainWindow::initToolBar() {
    QToolBar *toolBar = new QToolBar(this);
    toolBar->addAction(startGameAction);
    toolBar->addAction(pauseGameAction);
    toolBar->addAction(stopGameAction);
    toolBar->addAction(exitAction);
    toolBar->addAction(aboutAction);
    toolBar->setMovable(false);
    addToolBar(toolBar);
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
