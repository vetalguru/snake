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

    // Actions
    QAction *startGameAction = new QAction(QIcon::fromTheme("media-playback-start"), "&Start", this);
    QAction *exitAction = new QAction(QIcon::fromTheme("application-exit"), "&Exit", this);
    QAction *aboutQtAction = new QAction(QIcon::fromTheme("help-about"), "About &Qt ...", this);
    QAction *aboutAction = new QAction(QIcon::fromTheme("help-about"), "&About ...", this);

    // Connections
    connect(startGameAction, SIGNAL(triggered()), centralWidget, SLOT(startGame()));
    connect(exitAction, &QAction::triggered, qApp, QApplication::quit);
    connect(aboutQtAction, &QAction::triggered, qApp, QApplication::aboutQt);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutDialog);

    // Main menu
    // File
    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(exitAction);

    QMenu *gameMenu = menuBar()->addMenu("&Game");
    gameMenu->addAction(startGameAction);

    // About
    QMenu *aboutMenu = menuBar()->addMenu("&Help");
    aboutMenu->addAction(aboutQtAction);
    aboutMenu->addAction(aboutAction);

    // Toolbar
    QToolBar *toolBar = new QToolBar(this);
    toolBar->addAction(startGameAction);
    toolBar->addAction(exitAction);
    toolBar->addAction(aboutAction);
    addToolBar(toolBar);

    // Statusbar
    statusBar()->addWidget(new QLabel());
}

void MainWindow::aboutDialog() {
    QMessageBox msg;
    msg.setText("Snake");
    msg.exec();
}
