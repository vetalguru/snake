#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void aboutDialog();
    void changeAppleNumber(int);
    void changeSnakeLength(int);

private:
    QLabel *m_appleCounterLabel;
    QLabel *m_snakeLengthLabel;
};

#endif // MAINWINDOW_H
