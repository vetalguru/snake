#include "mainwindow.h"

#include <QAction>
#include "QApplication"
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // Actions
    QAction *exitAction = new QAction("&Exit", this);
    QAction *aboutQtAction = new QAction("About &Qt ...", this);
    QAction *aboutAction = new QAction("&About ...", this);

    // Main menu
    // File
    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(exitAction);
    connect(exitAction, &QAction::triggered, qApp, QApplication::quit);

    // About
    QMenu *aboutMenu = menuBar()->addMenu("&Help");
    aboutMenu->addAction(aboutQtAction);
    connect(aboutQtAction, &QAction::triggered, qApp, QApplication::aboutQt);

    aboutMenu->addAction(aboutAction);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutDialog);

    // Toolbar
    QToolBar *toolBar = new QToolBar(this);
    toolBar->addAction(exitAction);
    toolBar->addAction(aboutAction);
    addToolBar(toolBar);
}

MainWindow::~MainWindow() {
}

void MainWindow::aboutDialog() {
    QMessageBox msg;
    msg.setText("Snake");
    msg.exec();
}
