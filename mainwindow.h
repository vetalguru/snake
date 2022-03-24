#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void aboutDialog();
    void changeAppleNumber(int);
    void changeSnakeLength(int);

private:
    void initCenterWidget();
    void initActions();
    void initConnections();
    void initStatusBar();

    void deleteActions();

private:
    // Actions
    QAction *startGameAction;
    QAction *pauseGameAction;
    QAction *stopGameAction;
    QAction *exitAction;
    QAction *aboutQtAction;
    QAction *aboutAction;

    // StatusBar labels
    QLabel *m_appleCounterLabel;
    QLabel *m_snakeLengthLabel;
};

#endif // MAINWINDOW_H
